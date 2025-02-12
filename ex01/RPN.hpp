#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <stdexcept>
#include <stack>

class RPN {
    private:
        std::stack<int> Stack;

    public:
        RPN();
        RPN(std::string args);
        RPN(RPN &rpn);
        RPN &operator=(RPN &rpn);
        ~RPN();

        bool empty(void);
        size_t size(void);
        int pop();

        std::pair<int, int> popTwoOperands();
        int performCalculation(int leftOperand, int rightOperand, char op);
        void applyOperator(char op);
        bool input_check(std::string &inp);

        friend std::ostream &operator<<(std::ostream &os, RPN &rpn);
};

#endif
