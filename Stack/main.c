#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_MAXSIZE 100
#define STACK_INCREMENT 10
#define OK true
#define ERROR false

typedef int ElemType;
typedef bool Status;
typedef struct
{
    ElemType *base;// 栈底指针
    ElemType *top;// 栈顶指针，栈顶指针指向栈顶元素的下一块空间，top-1指向栈顶元素
    int maxsize;
}SStack;

int main()
{
    Status initStack(SStack *S);
    void delStack(SStack *S);
    Status Push(SStack *S, ElemType e);
    Status Pop(SStack *S, ElemType *e);
    
    SStack *stack = (SStack *)malloc(sizeof(SStack));
    int e = 0;// 存放出栈元素
    if (initStack(stack) == ERROR)
    {
        exit(-1);
    }
    for (int i = 0; i <= 10; i++)
    {
        Push(stack, i);
    }
    for (int i = 0; i <= 10; i++)
    {
        Pop(stack, &e);
        printf("Element %d pop!\n", e);
    }

    delStack(stack);
    return 0;
}
// 初始化栈，并分配MAXSIZE个空间，返回指向栈的地址
Status initStack(SStack *S)
{
    S->base = (ElemType *)malloc(sizeof(ElemType) * STACK_MAXSIZE);
    if (S->base == NULL)
    {
        printf("initStack ERROR!\n");
        return ERROR;
    }
    S->top = S->base;
    S->maxsize = STACK_MAXSIZE;
    return OK; 
}
// free内存
void delStack(SStack *S)
{
    if (S == NULL)
    {
        return;
    }
    free(S->base);
    free(S);
}
// 返回栈顶元素
Status getTop(SStack *S, ElemType *e)
{
    if (S->base == S->top)
    {
        printf("Stack is empty\n");
        return ERROR;
    }
    *e = *(S->top - 1);
    return OK;
}
// 入栈，若栈满需要重新分配空间
Status Push(SStack *S, ElemType e)
{
    if (S->top - S->base >= S->maxsize)
    {
        S->base = (ElemType *)realloc(S->base, (S->maxsize + STACK_INCREMENT) * sizeof(ElemType));
        if (S->base == NULL)
        {
            return ERROR;
        }
        S->top = S->base + S->maxsize;
        S->maxsize += STACK_INCREMENT;
    }
    *S->top = e;
    S->top++;
    return OK;
}
// 出栈，使用e返回栈顶元素
Status Pop(SStack *S, ElemType *e)
{
    if (S->base == S->top)
    {
        return ERROR;
    }
    *e = *(S->top - 1);
    S->top--;
    return OK;
}