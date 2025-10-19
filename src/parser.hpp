#pragma once
#include "Tokenizer.hpp"
#include <vector>
#include <stack>
#include <stdexcept>

class Parser {
public:
    std::vector<Token> toRPN(const std::vector<Token>& tokens);

private:
    int precedence(const std::string& op);
    bool rightAssociative(const std::string& op);
};
