#include "pch.h"
#include "../calculator/src/IFunctionPlugin.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>

class CosPlugin : public IFunctionPlugin {
public:
    std::string name() const override { return "cos"; }

    double evaluate(const std::vector<double>& args) override {
        if (args.size() != 1)
            throw std::runtime_error("cos requires 1 argument");
        return std::cos(args[0]); 
    }

    size_t argCount() const override { return 1; }
};

extern "C" __declspec(dllexport) IFunctionPlugin * createPlugin() {
    return new CosPlugin();
}

extern "C" __declspec(dllexport) void destroyPlugin(IFunctionPlugin * p) {
    delete p;
}
