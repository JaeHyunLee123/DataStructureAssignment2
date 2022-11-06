#include <iostream>
#include <string>
#include "deque.h"
#include "dlist.h"
#include "evaluator.h"

int main(){

    std::string sample = evaluator::read_expression();

    std::cout<<sample<<std::endl;

    std::string sample2 = evaluator::convert_to_postfix(sample);

    std::cout<<sample2<<std::endl;

    std::cout<<evaluator::evaluate_postfix(sample2)<<std::endl;

    // std::string sample = "3x+7-8Y";

    // std::cout<<sample<<std::endl;

    // sample = evaluator::put_multiple(sample);
    // sample = evaluator::manage_unknown(sample);

    // std::cout<<sample<<std::endl;


    
    return 0;
}   