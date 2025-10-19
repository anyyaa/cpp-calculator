#include "Tokenizer.hpp"
#include <cctype>
#include <stdexcept>

std::vector<Token> Tokenizer::tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    size_t i = 0;

    while (i < expression.size()) {
        char c = expression[i];

        if (std::isspace(c)) {
            ++i;
            continue;
        }

        if (std::isdigit(c) || c == '.') {
            size_t start = i;
            while (i < expression.size() && (std::isdigit(expression[i]) || expression[i] == '.'))
                ++i;

            std::string numStr = expression.substr(start, i - start);
            tokens.push_back({ TokenType::Number, numStr, std::stod(numStr) });
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            tokens.push_back({ TokenType::Operator, std::string(1, c) });
            ++i;
            continue;
        }

        if (c == '(') {
            tokens.push_back({ TokenType::LeftParen, "(" });
            ++i;
            continue;
        }

        if (c == ')') {
            tokens.push_back({ TokenType::RightParen, ")" });
            ++i;
            continue;
        }

        throw std::runtime_error(std::string("Unexpected character: ") + c);
    }

    return tokens;
}
