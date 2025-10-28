#include "Parser.hpp"

int Parser::precedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

bool Parser::rightAssociative(const std::string& op) {
    return op == "^";
}

std::vector<Token> Parser::toRPN(const std::vector<Token>& tokens) {
    std::vector<Token> output;
    std::stack<Token> ops;

    for (const auto& t : tokens) {
        switch (t.type) {
        case TokenType::Number:
            output.push_back(t);
            break;

        case TokenType::Function:
            ops.push(t);
            break;

        case TokenType::Comma:
            while (!ops.empty() && ops.top().type != TokenType::LeftParen)
            {
                output.push_back(ops.top());
                ops.pop();
            }
            if (ops.empty())
                throw std::runtime_error("Misplaced comma or mismatched parentheses");
            break;

        case TokenType::Operator:
            while (!ops.empty() && ops.top().type == TokenType::Operator) {
                std::string top = ops.top().text;
                if ((!rightAssociative(t.text) && precedence(t.text) <= precedence(top)) ||
                    (rightAssociative(t.text) && precedence(t.text) < precedence(top))) {
                    output.push_back(ops.top());
                    ops.pop();
                }
                else break;
            }
            ops.push(t);
            break;

        case TokenType::LeftParen:
            ops.push(t);
            break;

        case TokenType::RightParen:
            while (!ops.empty() && ops.top().type != TokenType::LeftParen) {
                output.push_back(ops.top());
                ops.pop();
            }
            if (ops.empty())
                throw std::runtime_error("Mismatched parentheses");
            ops.pop(); 
            if (!ops.empty() && ops.top().type == TokenType::Function) {
                output.push_back(ops.top());
                ops.pop();
            }
            break;
        }
    }

    while (!ops.empty()) {
        if (ops.top().type == TokenType::LeftParen || ops.top().type == TokenType::RightParen)
            throw std::runtime_error("Mismatched parentheses");
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}
