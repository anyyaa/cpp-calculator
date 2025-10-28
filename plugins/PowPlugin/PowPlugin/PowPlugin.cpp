#include "pch.h"
#include "../calculator/src/IFunctionPlugin.hpp"
#include <cmath>
#include <stdexcept>


class PowPlugin : public IFunctionPlugin {
public:
    std::string name() const override { return "pow"; }

    double evaluate(const std::vector<double>& args) override {
        if (args.size() != 2)
            throw std::runtime_error("pow requires 2 arguments");
        return std::pow(args[0], args[1]);
    }

    size_t argCount() const override { return 2; }
};  

extern "C" __declspec(dllexport) IFunctionPlugin * createPlugin() {
    return new PowPlugin();
}

extern "C" __declspec(dllexport) void destroyPlugin(IFunctionPlugin * p) {
    delete p;
}