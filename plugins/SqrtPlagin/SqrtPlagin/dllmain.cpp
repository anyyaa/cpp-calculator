#include "pch.h"
#include "../calculator/src/IFunctionPlugin.hpp"
#include <cmath>
#include <stdexcept>


class SqrtPlugin : public IFunctionPlugin {
public:
    std::string name() const override {
        return "sqrt";
    }

    double evaluate(const std::vector<double>& args) override {
        if (args.size() != 1)
            throw std::runtime_error("sqrt requires 1 argument");

        double x = args[0];
        if (x < 0)
            throw std::runtime_error("sqrt is undefined for negative values");

        return std::sqrt(x);
    }

    size_t argCount() const override {
        return 1;
    }
};

extern "C" __declspec(dllexport) IFunctionPlugin * createPlugin() {
    return new SqrtPlugin();
}

extern "C" __declspec(dllexport) void destroyPlugin(IFunctionPlugin * plugin) {
    delete plugin;
}
