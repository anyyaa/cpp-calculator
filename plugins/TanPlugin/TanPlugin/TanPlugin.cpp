#include "pch.h"
#include "../calculator/src/IFunctionPlugin.hpp"
#include <cmath>
#include <stdexcept>
#include <vector>
#include <string>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class TanPlugin : public IFunctionPlugin {
public:
    std::string name() const override { return "tan"; }

    double evaluate(const std::vector<double>& args) override {
        if (args.size() != 1)
            throw std::runtime_error("tan requires 1 argument");

        double rad = args[0]; 
        double mod = std::fmod(rad, M_PI);
        if (std::abs(mod - M_PI / 2) < 1e-10)
            throw std::runtime_error("tan is undefined at this angle");

        return std::tan(rad);
    }

    size_t argCount() const override { return 1; }
};

// Экспорт для DLL
extern "C" __declspec(dllexport) IFunctionPlugin * createPlugin() {
    return new TanPlugin();
}

extern "C" __declspec(dllexport) void destroyPlugin(IFunctionPlugin * p) {
    delete p;
}