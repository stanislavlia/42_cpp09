#include "RPN.hpp"
#include <iostream>
#include <exception>


// ALGORITHM EXPLANATION
// If charcter is number, we push this number onto stack.
// If character is an operator, we pop two numbers from the top of the stack and apply operator. 
// Push result back to the stack.
// If RNP experssion was valid, at the end of the processing input, we have stack with single number which is RESULT
//


int main(int argc, char **argv) {
    try {
        if (argc == 2) {
            RPN rpn(argv[1]);
            std::cout << rpn << std::endl;
        } else {
            throw std::exception();
        }
    } catch (std::exception &e) {
        std::cerr << "Error" << std::endl;
    }
    return 0;
}
