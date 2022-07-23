/* 线性表的链式表示 */
// 链表为带头节点的单链表，所有的数值为整形（int类型）
/*
1）链表的初始化
2）通过插入节点生成一个单链表，并在这个链表中完成基本操作
3）查找一个数值为e的节点
4）删除第i个节点

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义节点
typedef struct node Node; // 单纯为了下面写Node *next这句在前面写一个定义

struct node
{
    int data;
    Node *next;
};

// define the linear list
typedef struct
{
    Node *head, *tail; // the head node and tail node of list
    int length;        // the number of nodes
} linearList;

// 生成一个空链表，带头节点的空表，返回指向该线性表的指针
linearList *initEmpty()
{
    // 只需要创建一个头节点即可，头节点不存储数值，也可以用来存储节点个数
    linearList *L = (linearList *)malloc(sizeof(linearList));
    L->length = 0;
    L->head = (Node *)malloc(sizeof(Node));
    L->head->data = 0;
    L->head->next = NULL;
    // 初始尾指针指向头节点
    L->tail = L->head;
    return L;
}

// 依次输出链表数值
void printList(linearList list)
{
    // 定义一个指针指向第一个存储元素的节点，并依次后移完成遍历
    Node *p = list.head->next;
    for (int i = 0; p != NULL; p = p->next)
    {
        printf("Node %d equals %d.\n", ++i, p->data);
    }
}

// 头插法，每次插入将新节点插入到头节点后面位置，新节点的值为e，尾指针保持默认不操作（指向头节点）
void insertHead(linearList *L, int e)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = L->head->next;
    L->head->next = newNode;
}

// 尾插法，每次将新节点插入到表尾，然后尾指针指向新插入的节点（需要额外定义一个尾指针）
void insertTail(linearList *L, int e)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = NULL;
    // 利用尾指针进行节点插入，先将新的节点连接到尾节点，再将尾指针后移
    L->tail->next = newNode;
    L->tail = newNode;
}

// 查找数据为e的节点(假设存在为e的节点只有一个），查找到则返回指向该节点的指针，查找失败返回NULL
Node *findElem(linearList list, int e)
{
    Node *p = list.head->next;
    while (p != NULL)
    {
        if (e == p->data)
        {
            return p;
        }
        p = p->next;
    }
    return NULL;
}

// 删除数据为e的节点（假设存在的话数据为e的节点只有一个），删除成功返回true，删除失败（无该节点）返回false
bool deleteNode(linearList *L, int e)
{
    Node *dNode = NULL;
    Node *p = L->head;
    while (p->next != NULL)
    {
        if (e == p->next->data)
        {
            dNode = p->next;
            p->next = p->next->next;
            free(dNode);
            return true;
        }
        p = p->next;
    }
    return false;
}

// 一个简单的实例让上面的函数执行结果可视化
#include <stdio.h>
int main()
{
    linearList *listEg_1 = initEmpty();
    linearList *listEg_2 = initEmpty();
    // 对一个只有头节点的空表进行插入以生成一个链表，对eg1使用头插法，对eg2使用尾插法
    for (int i = 1; i <= 10; i++)
    {
        insertHead(listEg_1, i);
    }

    for (int i = 1; i <= 10; i++)
    {
        insertTail(listEg_2, i);
    }
    // 输出初始化的链表元素
    printf("头插法创建链表1:\n");
    printList(*listEg_1);
    printf("\n尾插法创建链表2:\n");
    printList(*listEg_2);

    // 在表1中查找元素，在表2中删除元素
    // 查找存在的元素 5
    if (findElem(*listEg_1, 5) != NULL)
    {
        printf("链表1中存在元素5, 下一个节点元素(verify)为 %d \n", findElem(*listEg_1, 5)->next->data);
    }
    else
    {
        printf("查找失败, 链表1中不存在元素5\n");
    }
    // 查找不存在的元素15
    if (findElem(*listEg_1, 15) != NULL)
    {
        printf("链表1中存在元素15, 下一个节点元素(verify)为 %d \n", findElem(*listEg_1, 15)->next->data);
    }
    else
    {
        printf("查找失败, 链表1中不存在元素15\n");
    }
    // 删除元素5
    if (deleteNode(listEg_2, 5))
    {
        printf("表2中删除元素5\n");
    }
    else
    {
        printf("表2中删除元素5失败, 元素不存在\n");
    }
    // 删除元素15
    if (deleteNode(listEg_2, 15))
    {
        printf("表2中删除元素15\n");
    }
    else
    {
        printf("表2中删除元素15失败, 元素不存在\n");
    }

    printf("处理后链表1无变化:\n");
    printList(*listEg_1);
    printf("\n链表2中元素被删去:\n");
    printList(*listEg_2);
    return 0;
}