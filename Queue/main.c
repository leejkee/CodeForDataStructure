// 队列的实现，元素从队尾入队，从队头出队
// 使用数组实现顺序栈
// 使队头和队尾指针到达数组端点可以回到开始处，形成环
// 为了避免在rear=front时无法区分队满还是队空，少使用一个存储空间，队头指的位置不存储元素，使得（rear+1）% size = front 时判断为队满
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 20
#define INCREMENT 10

typedef int ElemType;// 存储的数据类型
typedef struct QNode *PtrToQNode; // 指向节点的指针
struct QNode{
    ElemType *data;// 存储数据的数组
    int front, rear;// 头指针，尾指针
    int MaxSize;// 队列的最大容量
};
typedef PtrToQNode Queue;

// 初始化一个队列，并为存储元素的数组分配MAXSIZE大小存储空间，队头队尾指针初始值为0
Queue initQueue()
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->data = (ElemType *)malloc(MAXSIZE * sizeof(ElemType));
    Q->MaxSize = MAXSIZE;
    Q->front = Q->rear = 0;
    return Q;
}
// 删除队列，释放存储空间，先释放数组的空间，再释放队列的空间
void delQueue(Queue Q)
{
    if (Q == NULL)
    {
        return ;
    }
    if (Q->data != NULL)
    {
        free(Q->data);
    }
    free(Q);
}
// 入队
bool inQueue(Queue Q, ElemType e)
{
    if (((Q->rear) + 1) % Q->MaxSize == Q->front)
    {
        // 队满
        printf("Queue is full\n");
        return false;
    }
    else
    {
        Q->rear = (Q->rear + 1) % Q->MaxSize;
        Q->data[Q->rear] = e;
        return true;
    }
}
// 出队
bool outQueue(Queue Q, ElemType *e)
{
    if (Q->front == Q->rear)
    {
        // 队空
        printf("Queue is empty!\n");
        return false;
    }
    else{
        *e = Q->data[Q->front + 1];
        Q->front = (Q->front + 1) % Q->MaxSize;
    }
}
int main(void)
{
    Queue queue_seq = initQueue();
    ElemType e;
    inQueue(queue_seq, 12);
    inQueue(queue_seq, -5);
    outQueue(queue_seq, &e);
    printf("out queue:%d\n", e);
    outQueue(queue_seq, &e);
    printf("out queue:%d\n", e);
    delQueue(queue_seq);
    return 0;
}