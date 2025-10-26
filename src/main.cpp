#include <iostream>
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Evaluator.hpp"
#include "PluginManager.hpp"

int main() {
    try {
        PluginManager pm;
        pm.loadPlugins("./plugins");

        std::cout << "Enter expression: ";
        std::string input;
        std::getline(std::cin, input);

        Tokenizer tokenizer;
        auto tokens = tokenizer.tokenize(input);

        Parser parser;
        auto rpn = parser.toRPN(tokens);

        Evaluator evaluator(pm);
        double result = evaluator.evalRPN(rpn);

        std::cout << "Result: " << result << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error." << std::endl;
        return 1;
    }

    return 0;
}
