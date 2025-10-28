#include "pch.h"
#include "../calculator/src/IFunctionPlugin.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class CotPlugin : public IFunctionPlugin {
public:
    std::string name() const override { return "cot"; }

    double evaluate(const std::vector<double>& args) override {
        if (args.size() != 1)
            throw std::runtime_error("cot requires 1 argument");

        double rad = args[0];

        double t = std::tan(rad);
        if (std::abs(t) < 1e-10)
            throw std::runtime_error("cot is undefined at this angle");

        return 1.0 / t;
    }

    size_t argCount() const override { return 1; }
};


extern "C" __declspec(dllexport) IFunctionPlugin * createPlugin() {
    return new CotPlugin();
}

extern "C" __declspec(dllexport) void destroyPlugin(IFunctionPlugin * p) {
    delete p;
}
