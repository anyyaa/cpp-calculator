#include "pch.h"
#include "../calculator/src/IFunctionPlugin.hpp"
#include <cmath>
#include <stdexcept>



class ExpPlugin : public IFunctionPlugin {
public:
    std::string name() const override { return "exp"; }

    double evaluate(const std::vector<double>& args) override {
        if (args.size() != 1)
            throw std::runtime_error("exp requires exactly 1 argument");

        double x = args[0];
        return std::exp(x);
    }

    size_t argCount() const override { return 1; }
};

extern "C" __declspec(dllexport) IFunctionPlugin * createPlugin() {
    return new ExpPlugin();
}

extern "C" __declspec(dllexport) void destroyPlugin(IFunctionPlugin * plugin) {
    delete plugin;
}
