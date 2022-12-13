#include <stdio.h>
#include <stdlib.h>

typedef struct Stack {
    int maxsize;
    int top;
    int *listArray;
} Stack;

Stack createStack() {
    Stack stemp;
    stemp.maxsize = 8;
    stemp.top = 0;
    stemp.listArray = (int*) calloc(8, sizeof(int));
    return stemp;
}

void clearStack(Stack *stack) {
    free(stack->listArray);
    stack->maxsize = 0;
}

void pushElem(int elem, Stack *stack) {
    if(stack->top == stack->maxsize) printf("A pilha esta cheia\n");
    else {
        stack->listArray[stack->top] = elem;
        (stack->top)++;
    }
}

int popElem(Stack *stack) {
    int elem;
    if(stack->top == 0) {
        printf("A pilha esta vazia\n");
        return 0;
    }
    else {
        elem = stack->listArray[(stack->top)-1];
        (stack->top)--;
        return elem;
    }
}