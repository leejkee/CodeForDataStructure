// 栈的链式存储实现
// 定义节点-push操作-pop操作
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Position;
typedef int ElemType;
typedef struct node *PtrToNode;
struct node{
    ElemType data;
    PtrToNode next;
};
typedef PtrToNode Stack;

// 定义一个带头节点的链栈，由于单链表的操作受限，所以必须选可以插入和删除的表头作为栈顶，栈顶指针top指向链表的头指针
Stack initStack()
{
    Stack S = (Stack)malloc(sizeof(struct node));
    S->data = 0;
    S->next = NULL;
    return S;
}

void delStack(Stack S)
{
    if (S == NULL)
    {
        return ;
    }
    Stack p = S, q = NULL;
    while (p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

// push操作，新建一个节点，将该节点插入到头节点之后
void Push(Stack S, ElemType e)
{
    PtrToNode snew = (PtrToNode)malloc(sizeof(struct node));
    snew->data = e;
    snew->next = S->next;
    S->next = snew;
}
// pop操作，栈可能为空，栈空报错，栈不为空则返回栈顶（头节点下一个节点的元素）元素，并删掉这个节点
bool Pop(Stack S, ElemType *e)
{
    if (S->next == NULL)
    {
        return false;
    }
    PtrToNode topNode = S->next;
    *e = S->next->data;
    S->next = topNode->next;
    free(topNode);
    return true;
}
int main(void)
{
    Stack list_stack = initStack();
    ElemType data;
    Push(list_stack, 10);
    // 不同ElemType可以写不同的测试数据
    Pop(list_stack, &data);
    printf("pop:%d\n", data);

    return 0;
}