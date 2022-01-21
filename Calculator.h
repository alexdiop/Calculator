#include "Stack.h"

class Calculator{
    public:
        int currentValue;
        Stack *operationStack;
        Stack *undoStack;
        Calculator();
        int add(Stack *stack, char operation, int lhs, int rhs);
        void clear(Stack *stack, int lhs);
        int undo(Stack *operationStack, Stack *undoStack);
        void redo(Stack *operationStack, Stack *undoStack, int currentValue);
        void quit();
};