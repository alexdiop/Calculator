#pragma once

class Node {
    public:
        Node* next;
        char character;
        int lhs;
        int rhs;
        Node(char character, int lhs, int rhs);
        Node();
        void setNext(Node* newNext);
};

class Stack{
    public:
        Node *head;
        Stack();
        ~Stack();
        void push(char operation, int lhs, int rhs);
        Node* pop();
        Node* peek();
        void destroy();
        Stack(const Stack& other);
        Stack& operator=(const Stack& other);
};
