#include "pch.h"
#include "../../src/IFunctionPlugin.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>


class SinPlugin : public IFunctionPlugin {
public:
    std::string name() const override {
        return "sin";
    }

    double evaluate(const std::vector<double>& args) override {
        if (args.size() != 1)
            throw std::runtime_error("sin requires 1 argument");
        return std::sin(args[0]); 
    }

    size_t argCount() const override {
        return 1;
    }
};

extern "C" __declspec(dllexport) IFunctionPlugin * createPlugin() {
    return new SinPlugin();
}

extern "C" __declspec(dllexport) void destroyPlugin(IFunctionPlugin * p) {
    delete p;
}