#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include "IFunctionPlugin.hpp"

class PluginManager {
public:
    void loadPlugins(const std::string& directory);

    const std::vector<IFunctionPlugin*>& getPlugins() const {
        return plugins;
    }

    ~PluginManager();

private:
    struct PluginHandle {
        HMODULE handle;
        IFunctionPlugin* instance;
    };

    std::vector<IFunctionPlugin*> plugins;   
    std::vector<PluginHandle> handles;       
};
