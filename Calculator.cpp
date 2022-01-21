//============================================================================
// Name        : Calculator.cpp
// Author      : Alexander Diop
// Created     : February 2, 2020
// Version     :
// Copyright   : No Copyright
// Description : Main class using a the stack class to create a representation of a calculator 
// uses the stack functions to allow calculator to compute user input
//============================================================================

#include <cstdlib>
#include <iostream>
#include <sstream>
#include "Calculator.h"

using namespace std;

Calculator::Calculator(){
    operationStack = new Stack();
    undoStack = new Stack();
}

int Calculator::add(Stack *stack, char operation, int lhs, int rhs){
    int value;
    switch (operation){
        case '+':
            value = lhs + rhs;
        break;
        case '-':
            value = lhs - rhs;
        break;
        case '*':
            value = lhs * rhs;
        break;
        case '/':
            value = lhs / rhs;
        break;
        case '%':
            value = lhs % rhs;
        break;
    }

    stack->push(operation,lhs,rhs);
    return value;
}

void Calculator::clear(Stack *stack, int lhs){
    stack->push('*',lhs,0);
}

int Calculator::undo(Stack *operationStack, Stack *undoStack){
    int currentValue = operationStack->peek()->lhs;
    undoStack->push(operationStack->pop()->character,operationStack->pop()->lhs,operationStack->pop()->rhs);
    return currentValue;
}

void Calculator::redo(Stack *operationStack, Stack *undoStack, int currentValue){
    switch (undoStack->peek()->character){//value may be null here
        case '+': add(operationStack,'-',currentValue,undoStack->peek()->rhs);
                  undoStack->pop();
            break;
        case '-': add(operationStack,'+',currentValue,undoStack->peek()->rhs);
                  undoStack->pop();
            break;
        case '*': if(undoStack->peek()->rhs == 0){
                        currentValue = undoStack->peek()->lhs;
                        add(operationStack, undoStack->peek()->character, undoStack->peek()->lhs, undoStack->peek()->rhs);
                        undoStack->pop();
                    }
                    else{
                        add(operationStack,'/',currentValue,undoStack->peek()->rhs);
                        undoStack->pop();
                    }
            break;
        case '/': add(operationStack,'*',currentValue,undoStack->peek()->rhs);
                  undoStack->pop();
            break;
        case '%': // code to be executed if operation to undo is %;
            break;
        default: cout<<"No operations to redo"; //if operation doesn't match any cases
    }
}

void Calculator::quit(){
    operationStack->destroy();
    undoStack->destroy();
}

int main() {

    Calculator *calculator = new Calculator();
    calculator->currentValue = 0;

    cout<<"====================================================="<<endl;
    cout<<"         Commands: \"+,-,*,/, or %\""<<endl;
    cout<<"          Numbers:  Must be integer numbers"<<endl;
    cout<<"            Clear:  \"C\" or \"c\""<<endl;
    cout<<"             Undo:  \"U\" or \"u\""<<endl;
    cout<<"             Redo:  \"R\" or \"r\""<<endl;
    cout<<"             Quit:  \"Q\" or \"q\""<<endl;
    cout<<"Enter a command followed by a number (Example: +300)"<<endl;
    cout<<"====================================================="<<endl;


    char operation;
    int lhs;
    int rhs;
    string phrase;

    while(operation != 'Q' or 'q'){
        
        cin>>phrase;
        switch (phrase[0]){
            case '+':
                operation = '+';
            break;
            case '-':
                operation = '-';
            break;
            case '*':
                operation = '*';
            break;
            case '/':
                operation = '/';
            break;
            case '%':
                operation = '%';
            break;
            case 'C':
                operation = 'C';
                calculator->clear(calculator->operationStack, calculator->currentValue);
            break;
            case 'U':
                operation = 'U';
                calculator->currentValue = calculator->undo(calculator->operationStack, calculator->undoStack);
            break;
            case 'R':
                operation = 'R';
                calculator->redo(calculator->operationStack, calculator->undoStack, calculator->currentValue);
            break;
            case 'Q':
                operation = 'Q';
            break;
        }

        if(phrase[1] == ' '){//might be a null pointer
            string numberString = phrase.substr(2);//get the number after the space
            std::istringstream iss (numberString);
            iss >> rhs;
            if (iss.fail()) {
                cout<<"Error in trying to convert a noninteger";
            }
            calculator->currentValue = calculator->add(calculator->operationStack, operation, calculator->currentValue, rhs);

        }
        else if (operation != 'C' && operation != 'U' && operation != 'R' && operation != 'Q'){
            string numberString = phrase.substr (1);//get the number after the space
            std::istringstream iss (numberString);
            iss >> rhs;
            if (iss.fail()){
                cout<<"Error in trying to convert a noninteger";
            }
            calculator->currentValue = calculator->add(calculator->operationStack, operation, calculator->currentValue, rhs);
        }
        else{
            string numberString = phrase.substr(1);//get the number after the operator
            std::istringstream iss (numberString);
            iss >> rhs;
            if (iss.fail()) {
                cout<<"Error in trying to convert a noninteger";
            }
            calculator->currentValue = calculator->add(calculator->operationStack, operation, calculator->currentValue, rhs);

        }
    }

    calculator->quit();
    return 0;
}

