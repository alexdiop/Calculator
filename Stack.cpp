//============================================================================
// Name        : Stack.cpp
// Author      : Alexander Diop
// Created     : February 2, 2020
// Version     :
// Copyright   : No Copyright
// Description : Stack class using a singly linked list representation and struct of operator, lhs, and rhs for data
//============================================================================

#include "Stack.h"
#include <iostream>

//creating a new node
Node::Node(char character, int lhs, int rhs){
    this->character = character;
    this->lhs = lhs;
    this->rhs = rhs;
}

void Node::setNext(Node* newNext){
    if(newNext == NULL)
        next = NULL;
    else
        next = newNext;
}

class Stack{
    public:
        Node *head;

        //creates and empty list
        Stack(){
            head = nullptr;
        }

        ~Stack() {
            destroy();
        }

        void push(char operation, int lhs, int rhs){

            Node *node = new Node(operation,lhs,rhs);
            //if the list is empty, make this node the head and tail
            if (head == NULL){
                head = node;
            }
            else{//make it the new head of the list
                head->setNext(node);
                head = node;
            }
        }

        //removes head node from list and returns it
        Node* pop(){
            Node* top = head;
            delete head;
            head = peek();
            return top;
        }

        //returns the node at the head of the list even if its empty
        Node* peek(){
            return head;
        }

        //empty the list
        void destroy(){

            Node *walk = head;
            while (walk){
                Node *node = walk;
                walk = walk->next;
                delete node;
            }
            head = nullptr;
        }

        Stack(const Stack& other){
            
        };
        Stack& operator=(const Stack& other){
            if(this != & other){
                destroy();
                //copy
            }
            return *this;
        };

};
