#include <iostream>
#include <string>
#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "Evaluator.hpp"
#include "PluginManager.hpp"

int main() {
    try {
        PluginManager pm;
        pm.loadPlugins("./plugins");

        const auto& plugins = pm.getPlugins();
        

        Evaluator evaluator(pm);
        Tokenizer tokenizer;
        Parser parser;

        std::string input;
        while (true) {
            std::cout << "\nEnter expression (or 'exit' to quit): ";
            if (!std::getline(std::cin, input)) break;

            if (input == "exit" || input == "quit") break;
            if (input.empty()) continue;

            try {
                auto tokens = tokenizer.tokenize(input);
                auto rpn = parser.toRPN(tokens);
                double result = evaluator.evalRPN(rpn);
                std::cout << "Result: " << result << std::endl;
            }
            catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            catch (...) {
                std::cerr << "Unknown error occurred." << std::endl;
            }
        }

        std::cout << "Goodbye!" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Critical error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error." << std::endl;
        return 1;
    }

    return 0;
}
