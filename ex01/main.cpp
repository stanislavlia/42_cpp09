#include "RPN.hpp"
#include <iostream>
#include <exception>

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
