#ifndef RPN_HPP
#define RPN_HPP

#include <string>
#include <iostream>
#include <exception>
#include <stack>
#include <algorithm>
#include <sstream>

class RPN {
    private:
        std::stack<int> Stack;

    public:
        bool empty(void);
        size_t size(void);
        int pop();
        RPN();
        ~RPN();
        RPN &operator=(RPN &rpn);
        RPN(RPN &rpn);
        RPN(std::string args);


};

#endif