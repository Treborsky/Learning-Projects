/*
 *  Project: ScientificCalculator 
 *
 *  File: main.cc
 *
 *  Date: 12.09.2023  
 *  
 */
#include <iostream>

class ScientificCalculator {
public:
    static float Addition(float val1, float val2) {
        return val1 + val2;
    }

    static float Subtraction(float val1, float val2) {
        return val1 - val2;
    }

    static float Multiplication(float val1, float val2) {
        return val1 * val2;
    }

    static float Division(float val1, float val2) {
        return val1 / val2;
    }

    // static float Modulo(float val1, float val2) {
    //     return val1 % val2;
    // }
};

int main() {
    std::cout << "Scientific calculator.\n"
              << "Supported operations: \n"
              << " - addition '+',\n"
              << " - subtraction '-',\n"
              << " - multiplication '*',\n"
              << " - division '/',\n"
            //   << " - modulo '%'.\n"
              << "Equations are to be typed in using the infix notation: 'op(val1,val2)' "
              << "and confirmed with [Enter]. Note there is no space between " << std::endl;

    char operation = '\0';
    float val1 = 0.0;
    float val2 = 0.0;
    

    std::string equation;

    std::cout << "Enter your equation: " << std::endl;
    std::cin >> equation;

    std::cout << "Equation: " << equation << std::endl;

    for (int i = 0; i < equation.length(); ++i) {
        std::cout << "[" << i << "] = " << equation[i] << ", ";
    } std::cout << std::endl;

    try {
        operation = equation[0];
        val1 = std::stof(equation.substr(2, 5));
        val2 = std::stof(equation.substr(6, 9));
    } catch (...) {
        std::cout << "Parsing error. I don't feel like implementing proper input checks because screw that -.-" << std::endl;
        return 0;
    }

    std::cout << "Operation: " << operation << std::endl;
    std::cout << "Val1: " << val1 << std::endl;
    std::cout << "Val2: " << val2 << std::endl;

    float result = 0.0;
    switch (operation) {
        case '+': {
            result = ScientificCalculator::Addition(val1, val2);
            break;
        }
        case '-': {
            result = ScientificCalculator::Subtraction(val1, val2);
            break;
        }
        case '*': {
            result = ScientificCalculator::Multiplication(val1, val2);
            break;
        }
        case '/': {
            result = ScientificCalculator::Division(val1, val2);
            break;
        }
        default: {
            std::cout << "Unknown operation." << std::endl;
            return 0;
        }
    }
    std::cout << "Result: " << result << std::endl;
}