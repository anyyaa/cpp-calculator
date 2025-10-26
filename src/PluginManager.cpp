#include "PluginManager.hpp"
#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace fs = std::filesystem;

void PluginManager::loadPlugins(const std::string& directory) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() != ".dll") continue;

        std::cout << "Trying to load: " << entry.path() << "\n";

        HMODULE lib = LoadLibraryA(entry.path().string().c_str());
        if (!lib) {
            std::cerr << "ERROR: Cannot load library " << entry.path() << "\n";
            continue;
        }

        auto create = (IFunctionPlugin * (*)())GetProcAddress(lib, "createPlugin");
        auto destroy = (void(*)(IFunctionPlugin*))GetProcAddress(lib, "destroyPlugin");

        if (!create || !destroy) {
            std::cerr << "ERROR: createPlugin or destroyPlugin not found in " << entry.path() << "\n";
            FreeLibrary(lib);
            continue;
        }

        IFunctionPlugin* plugin = nullptr;
        try {
            plugin = create();
        }
        catch (const std::exception& e) {
            std::cerr << "ERROR: exception during createPlugin(): " << e.what() << "\n";
            FreeLibrary(lib);
            continue;
        }
        catch (...) {
            std::cerr << "ERROR: unknown exception during createPlugin()\n";
            FreeLibrary(lib);
            continue;
        }

        plugins.push_back(plugin);
        handles.push_back({ lib, plugin });

        std::cout << "Loaded plugin: " << plugin->name() << "\n";
    }

    if (plugins.empty()) {
        std::cerr << "Warning: no plugins found in " << directory << "\n";
    }
}

PluginManager::~PluginManager() {
    for (auto& h : handles) {
        auto destroy = (void(*)(IFunctionPlugin*))GetProcAddress(h.handle, "destroyPlugin");
        if (destroy && h.instance)
            destroy(h.instance);   
        if (h.handle)
            FreeLibrary(h.handle);
    }
}
