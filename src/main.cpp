#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Evaluator.hpp"
#include <iostream>

int main() {
    Tokenizer tokenizer;
    Parser parser;
    Evaluator evaluator;

    std::cout << "Calculator ready (basic operations only)\n";
    std::cout << "Type 'exit' to quit\n";

    std::string line;
    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, line)) break;
        if (line == "exit" || line == "quit") break;

        try {
            auto tokens = tokenizer.tokenize(line);
            auto rpn = parser.toRPN(tokens);
            double result = evaluator.evalRPN(rpn);
            std::cout << "= " << result << "\n";
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}
