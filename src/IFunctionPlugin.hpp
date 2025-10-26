#pragma once
#include <vector>
#include <string>

class IFunctionPlugin {
public:
    virtual ~IFunctionPlugin() = default;

    virtual std::string name() const = 0;
    virtual double evaluate(const std::vector<double>& args) = 0;
    virtual size_t argCount() const = 0;
};
