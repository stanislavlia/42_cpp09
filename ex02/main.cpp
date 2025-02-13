#include "PmergeMe.hpp"


//https://dev.to/emuminov/human-explanation-and-step-by-step-visualisation-of-the-ford-johnson-algorithm-5g91

int main(int ac , char **av){
    try{
        if(ac > 2){
            PmergeMe<std::deque<int> >   Deque(av);  
            PmergeMe<std::vector<int> >  Vector(av);

            std::cout << "Before: " << Deque << std::endl;
            Deque.sort();
            Vector.sort();
            std::cout << "After: " << Deque << std::endl;
            
            Deque.sort_time();
            Vector.sort_time();

        }else 
            throw "Error";
    }catch(...){
        std::cerr << "Error" << std::endl;
    }
    return 0;
}