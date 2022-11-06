#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <string>
#include <cctype>
#include <cstring>
#include <unistd.h>
#include "deque.h"

class evaluator{
public:

    //수식을 입력받고 적절한 수식인지 검사 후 그 수식을 문자열로 리턴
    //빈칸도 비 허용
    //적절하지 않은 수식일 경우 빈 문자열 리턴
    static std::string read_expression();
    //인픽스를 포스트 픽스 형식으로 변경
    //연산자와 피연산자들은 반칸으로 구분 
    //ex) 55+5  -> 55 5 +
    static std::string convert_to_postfix(std::string s);
    //포스트 픽스된 수식을 계산
    //미지수가 있을 시, 사용자로부터 미지수를 입력받음
    static double evaluate_postfix(std::string s);


    //미지수와 숫자사이에  *  넣는 함수
    //ex) 3x+8 -> 3*x+8
    static std::string put_multiple(std::string& s);
 
    //미지수에 수 대입시키는 함수t
    static std::string manage_unknown(std::string& s);

};

std::string evaluator::read_expression(){
    //사용자로부터 수식을 입력 받음
    std::string expression;
    std::cin >> expression;

    //괄호를 저장하는 데큐
    deque<char> parenthensis;
    //연산자와 피연산자를 저장하는 데큐
    deque<char> oper;

    expression = evaluator::put_multiple(expression);

    
    for(int i=0; i<expression.length(); i++){
        //알파벳이거나 숫자이거나 '.'인 경우, oper 데큐에 저장
        if(isalnum(expression[i]) || expression[i] == '.'){
            oper.push_back(expression[i]);
        }
        //연산자인 경우
        else if(strchr("+-*/",expression[i])!=NULL){
            //연산자가 수식의 첫번째로 오거나, 연산자가 연속으로 나오면 적절하지 않은 수식으로 처리
            if(i==0 || strchr("+-*/",expression[i-1])!=NULL){
                std::cout<<"Incorrect expression."<<std::endl;
                std::cout<<"Operator must be next to operand."<<std::endl;
                return "";
            }else{
                //oper 데큐에 저장
                oper.push_back(expression[i]);
            }
        }
        //완쪽 괄호가 나오면 parenthesis 데큐에 저장
        else if(expression[i] == '('){
            parenthensis.push_back(expression[i]);
        }
        //오른쪽 괄호인 경우
        else if(expression[i] == ')'){
            //parenthensis 데큐가 비어 있으면, 적절하지 않은 수식으로 처리
            if(parenthensis.is_empty()){
                std::cout<<"Incorrect expression."<<std::endl;
                std::cout<<"Parenthesis have to be paired up."<<std::endl;
                return "";
            }else{
                //parenthensis 데큐 pop_back
                parenthensis.pop_back();
            }
        }
        else{
            //적절하지 않은 표현(괄호, 연산자, 피연산자가 아닌 경우)
            std::cout<<"Incorrect expression."<<std::endl;
            return "";
        }
    }

    //parenthensis 데큐가 비어 있지 않으면 적절하지 않은 수식
    //오른쪽 괄호와 왼쪽 괄호가 같은 개수로 있으면 데큐가 비어있어야함
    if(!parenthensis.is_empty()){
        std::cout<<"Incorrect expression."<<std::endl;
        std::cout<<"Parenthesis have to be paired up."<<std::endl;
        return "";
    }
    
    //oper 데큐의 마지막 원소가 연산자면 적절하지 않은 수식
    //연산자 뒤에는 피연산자가 무조건 있으야 하기 때문
    if(strchr("+-*/",oper.back())!=NULL){
        std::cout<<"Incorrect expression."<<std::endl;
        std::cout<<"Operand must be next to operator."<<std::endl;
        return "";
    }

    //필요 없는 데큐 소멸
    parenthensis.~deque();
    oper.~deque();

    //위 모든 조건을 통과한 수식을 리턴
    return expression;
}

std::string evaluator::convert_to_postfix(std::string s){
    std::string result;

    deque<char> temp;

    for(int i=0; i<s.length(); i++){
        if(s[i] == '('){
            temp.push_back(s[i]);
        }
        else if (strchr("+-*/",s[i])!=NULL){
            while(!temp.is_empty()){
                
                //왼쪽 괄호이거나, 더 낮은 우선순위의 연산자일경우 break
                if(temp.back() == '(') break;
                if(strchr("+-",temp.back())!=NULL && strchr("*/",s[i])!=NULL) break;
                result.push_back(temp.back());
                result.push_back(' ');
                temp.pop_back();
            }
            temp.push_back(s[i]);
        }
        else if(isalnum(s[i])) {
            result.push_back(s[i]);
            if(i+1==s.length()){result.push_back(' ');}
            if(i+1<s.length() && s[i+1] != '.' && !isalnum(s[i+1])) {result.push_back(' ');}

        }else if(s[i]=='.'){
            result.push_back('.');
            if(i+1<s.length() && !isalnum(s[i+1])) {result.push_back(' ');}
            
        }
        else if(s[i] == ')'){
            while(temp.back()!='('){
                result.push_back(temp.back());
                result.push_back(' ');
                temp.pop_back();
            }
            temp.pop_back();
        }
    }

    while(!temp.is_empty()){
        result.push_back(temp.back());
        if(temp.size()>1) result.push_back(' ');    
        temp.pop_back();   
    }

    temp.~deque();

    return result;
}

double evaluator::evaluate_postfix(std::string s){
    s = evaluator::manage_unknown(s);

    double operand1;
    double operand2;
    char oper;

    deque<double> operand;
    std::string number="";

    for(int i=0; i<s.length(); i++){
        if(isdigit(s[i]) || s[i] == '.'){
            number.push_back(s[i]);
        }else if (strchr("+-*/",s[i])!=NULL){
            operand1 = operand.back();
            operand.pop_back();
            operand2 = operand.back();
            operand.pop_back();
            switch(s[i]){
                case '+':
                    operand.push_back(operand2 + operand1);
                    break;
                case '-':
                    operand.push_back(operand2 - operand1);
                    break;
                case '*':
                    operand.push_back(operand2 * operand1);
                    break;
                case '/':
                    operand.push_back(operand2 / operand1);
                    break;
            }
        }else if(s[i] == ' '){
            if(isdigit(s[i-1])){
                operand.push_back(std:: stod(number));
                number.clear();
            }
        }

    }

    return operand.back();
}

std::string evaluator::put_multiple(std::string& s){

    for(int i=0; i<s.length(); i++){
        if(i+1<=s.length() && isdigit(s[i]) && isalpha(s[i+1])){
            s.insert(i+1,"*");
        }
    }

    return s;
}

std::string evaluator::manage_unknown(std::string& s){
    
    for(int i=0; i<s.length(); i++){
        if(isalpha(s[i])){
            std::string number;
            std::cout<<"Insert number for "<<s[i]<<":";
            std::cin >> number;

            for(int j=i; j<s.length(); j++){
                if(s[j]==s[i]){
                    s.erase(j,1);
                    s.insert(j,number);
                }
            }
        }
    }

    return s;
}



#endif