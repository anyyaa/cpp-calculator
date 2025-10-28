#pragma once
#include "Tokenizer.hpp"
#include "PluginManager.hpp"
#include <vector>

class Evaluator {
public:
    Evaluator(PluginManager& pm) : pluginManager(pm) {}
    double evalRPN(const std::vector<Token>& rpn);

private:
    PluginManager& pluginManager;
};
