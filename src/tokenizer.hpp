#pragma once
#include <string>
#include <vector>

enum class TokenType {
    Number,
    Operator,
    LeftParen,
    RightParen,
    Function,
    Comma
};

struct Token {
    TokenType type;
    std::string text;
    double value = 0.0;
};

class Tokenizer {
public:
    std::vector<Token> tokenize(const std::string& expression);
};
