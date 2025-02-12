#include "RPN.hpp"

RPN::RPN()
{
}

RPN::RPN(std::string args) {
    if (!input_check(args))
        throw std::exception();
}

RPN::RPN(RPN &rpn) {
    this->Stack = rpn.Stack;
}

RPN &RPN::operator=(RPN &rpn) {
    if (this != &rpn)
        this->Stack = rpn.Stack;
    return *this;
}

RPN::~RPN()
{
}


bool check_token(const std::string &token) {
    if (!std::isdigit(token[0]) && token != "-" && token != "+" && token != "/" && token != "*")
        return false;
    return true;
}

std::pair<int, int> RPN::popTwoOperands() {
    if (Stack.empty())
        throw std::exception();
    int rightOperand = Stack.top();
    Stack.pop();
    if (Stack.empty())
        throw std::exception();
    int leftOperand = Stack.top();
    Stack.pop();
    return std::make_pair(leftOperand, rightOperand);
}

int RPN::performCalculation(int leftOperand, int rightOperand, char op) {
    switch (op) {
        case '*':
            return leftOperand * rightOperand;
        case '+':
            return leftOperand + rightOperand;
        case '-':
            return leftOperand - rightOperand;
        case '/':
            if (rightOperand == 0) {
                std::cerr << "Division by zero is not allowed: " 
                          << leftOperand << " / " << rightOperand << std::endl;
                throw std::exception();
            }
            return leftOperand / rightOperand;
        default:
            throw std::exception();
    }
}

void RPN::applyOperator(char op) {
    std::pair<int, int> operands = popTwoOperands();
    int result = performCalculation(operands.first, operands.second, op);
    Stack.push(result);
}

bool RPN::input_check(std::string &inp) {
    if (inp.empty())
        return false;
    char *cstr = new char[inp.size() + 1];
    std::strcpy(cstr, inp.c_str());
    char *token = std::strtok(cstr, " ");
    
    while (token) {
        std::string tmp = token;
        if (!check_token(tmp)) {
            delete[] cstr;
            return false;
        } else {
            char op = token[0];
            if (op == '-' || op == '+' || op == '/' || op == '*') {
                applyOperator(op);
            } else {
                Stack.push(std::atoi(token));
            }
        }
        token = std::strtok(NULL, " ");
    }
    
    delete [] cstr;
    return true;
}

int RPN::pop(void) {
    return Stack.top();
}

bool RPN::empty(void) {
    return Stack.empty();
}

size_t RPN::size(void) {
    return Stack.size();
}

std::ostream &operator<<(std::ostream &os, RPN &rpn) {
    if (rpn.size() != 1)
        throw std::exception();
    os << rpn.pop();
    return os;
}

