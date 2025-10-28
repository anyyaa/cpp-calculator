#include "pch.h"
#include <cmath>
#include <stdexcept>
#include "../calculator/src/IFunctionPlugin.hpp"

class LnPlugin : public IFunctionPlugin {
public:
    std::string name() const override {
        return "ln";
    }

    double evaluate(const std::vector<double>& args) override {
        if (args.size() != 1)
            throw std::runtime_error("ln requires 1 argument");

        double x = args[0];
        if (x <= 0)
            throw std::runtime_error("ln is undefined for non-positive values");

        return std::log(x);
    }

    size_t argCount() const override {
        return 1;
    }
};

extern "C" __declspec(dllexport) IFunctionPlugin * createPlugin() {
    return new LnPlugin();
}

extern "C" __declspec(dllexport) void destroyPlugin(IFunctionPlugin * plugin) {
    delete plugin;
}
