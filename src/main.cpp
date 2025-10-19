#include "Tokenizer.hpp"
#include <iostream>

int main() {
    Tokenizer tokenizer;
    std::string line;

    std::cout << "Tokenizer test. Type an expression:\n> ";
    std::getline(std::cin, line);

    try {
        auto tokens = tokenizer.tokenize(line);
        std::cout << "Tokens:\n";
        for (auto& t : tokens)
            std::cout << t.text << " ";
        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
