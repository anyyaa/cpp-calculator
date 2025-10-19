#pragma once
#include "Tokenizer.hpp"
#include <vector>
#include <stack>
#include <stdexcept>
#include <cmath>

class Evaluator {
public:
    double evalRPN(const std::vector<Token>& rpn);
};
