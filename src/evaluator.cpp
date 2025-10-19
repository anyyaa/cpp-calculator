#include "Evaluator.hpp"

double Evaluator::evalRPN(const std::vector<Token>& rpn) {
    std::stack<double> st;

    for (const auto& t : rpn) {
        if (t.type == TokenType::Number) {
            st.push(t.value);
        }
        else if (t.type == TokenType::Operator) {
            if (st.size() < 2)
                throw std::runtime_error("Not enough operands");
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
            st.push(r);
        }
    }

    if (st.size() != 1)
        throw std::runtime_error("Invalid expression");
    return st.top();
}
