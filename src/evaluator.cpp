#include "Evaluator.hpp"
#include <stack>
#include <cmath>
#include <stdexcept>
#include <iostream>

double Evaluator::evalRPN(const std::vector<Token>& rpn) {
    std::stack<double> st;

    try {
        for (const auto& t : rpn) {
            if (t.type == TokenType::Number) {
                st.push(t.value);
            }
            else if (t.type == TokenType::Operator) {
                if (st.size() < 2)
                    throw std::runtime_error("Not enough operands for operator " + t.text);

                double b = st.top(); st.pop();
                double a = st.top(); st.pop();
                double r = 0;

                if (t.text == "+") r = a + b;
                else if (t.text == "-") r = a - b;
                else if (t.text == "*") r = a * b;
                else if (t.text == "/") {
                    if (b == 0) throw std::runtime_error("Division by zero");
                    r = a / b;
                }
                else if (t.text == "^") r = std::pow(a, b);
                else throw std::runtime_error("Unknown operator: " + t.text);

                st.push(r);
            }
            else if (t.type == TokenType::Function) {
               
                IFunctionPlugin* plugin = nullptr;
                for (auto p : pluginManager.getPlugins()) { 
                    if (p->name() == t.text) {
                        plugin = p;
                        break;
                    }
                }

                if (!plugin)
                    throw std::runtime_error("Unknown function: " + t.text);

                size_t expectedArgs = plugin->argCount();
                if (st.size() < expectedArgs)
                    throw std::runtime_error(t.text + " requires " + std::to_string(expectedArgs) + " arguments");

               
                std::vector<double> args(expectedArgs);
                for (size_t i = 0; i < expectedArgs; ++i) {
                    args[expectedArgs - i - 1] = st.top();
                    st.pop();
                }

                try {
                    double res = plugin->evaluate(args);
                    st.push(res);
                }
                catch (const std::exception& e) {
                    std::cerr << "Error in function " << t.text << ": " << e.what() << std::endl;
                    return 0;
                }
                catch (...) {
                    std::cerr << "Unknown error in function " << t.text << std::endl;
                    return 0;
                }
            }
        }

        if (st.size() != 1)
            throw std::runtime_error("Invalid expression");

        return st.top();
    }
    catch (const std::exception& e) {
        std::cerr << "Evaluation error: " << e.what() << std::endl;
        return 0;
    }
    catch (...) {
        std::cerr << "Unknown error during evaluation." << std::endl;
        return 0;
    }
}
