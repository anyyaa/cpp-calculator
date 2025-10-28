#include "Tokenizer.hpp"
#include <cctype>
#include <stdexcept>

std::vector<Token> Tokenizer::tokenize(const std::string& expression) {
    std::vector<Token> tokens;
    size_t i = 0;
    
    TokenType prevType = TokenType::LeftParen;

    while (i < expression.size()) {
        char c = expression[i];

        if (std::isspace(static_cast<unsigned char>(c))) {
            ++i;
            continue;
        }

        auto canBeSign = [&prevType]() {
            
            return !(prevType == TokenType::Number || prevType == TokenType::RightParen);
            };

        
        if ((c == '-' || c == '+') && canBeSign()) {
            if (i + 1 < expression.size() && (std::isdigit(static_cast<unsigned char>(expression[i + 1])) || expression[i + 1] == '.')) {
                
                size_t start = i;
                ++i; 
                while (i < expression.size() && (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.'))
                    ++i;
                std::string numStr = expression.substr(start, i - start);
                tokens.push_back({ TokenType::Number, numStr, std::stod(numStr) });
                prevType = TokenType::Number;
                continue;
            }
            
        }

        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            size_t start = i;
            while (i < expression.size() && (std::isdigit(static_cast<unsigned char>(expression[i])) || expression[i] == '.'))
                ++i;
            std::string numStr = expression.substr(start, i - start);
            tokens.push_back({ TokenType::Number, numStr, std::stod(numStr) });
            prevType = TokenType::Number;
            continue;
        }

        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            tokens.push_back({ TokenType::Operator, std::string(1, c) });
            ++i;
            prevType = TokenType::Operator;
            continue;
        }

        if (c == '(') {
            tokens.push_back({ TokenType::LeftParen, "(" });
            ++i;
            prevType = TokenType::LeftParen;
            continue;
        }
        if (c == ')') {
            tokens.push_back({ TokenType::RightParen, ")" });
            ++i;
            prevType = TokenType::RightParen;
            continue;
        }

        if (c == ',') {
            tokens.push_back({ TokenType::Comma, "," });
            ++i;
            prevType = TokenType::Comma;
            continue;
        }

        if (std::isalpha(static_cast<unsigned char>(c))) {
            size_t start = i;
            while (i < expression.size() && std::isalpha(static_cast<unsigned char>(expression[i])))
                ++i;
            std::string name = expression.substr(start, i - start);
            tokens.push_back({ TokenType::Function, name });
            prevType = TokenType::Function;
            continue;
        }

        throw std::runtime_error(std::string("Unexpected character: ") + c);
    }

    return tokens;
}
