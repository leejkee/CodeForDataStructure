/* 线性表的链式表示 */
/*
链表为带头结点的单链表，所有的数值为整形（int类型）
1）链表的初始化
2）通过插入结点生成一个单链表，并在这个链表中完成基本操作
3）查找一个数值为e的结点
4）删除第i个结点
*/
/* 线性表的应用 */
/*
完成两个有序表的合并
定义两个单链表la，lb，表内元素按非递减排序，合并后lc中元素也按非递减排序
以la，lb其中一个链表的头结点作为新表头结点，然后依次合并到新头结点后面，最后释放另一个头结点的空间即可
定义用于遍历的移动指针pa，pb，pc完成合并操作
合并过程实际上是通过比较la和lb第一个结点元素大小来进行合并，被合并的一方将该结点从原链表中移动到新链表中，同时遍历指针后移一位
由于非递减排序，结点元素小的被合并，较大的则继续同被合并链表下一个结点元素比较
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义结点
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

// 生成一个空链表，带头结点的空表，返回指向该线性表的指针
linearList *initEmpty()
{
    // 只需要创建一个头结点即可，头结点不存储数值
    linearList *L = (linearList *)malloc(sizeof(linearList));
    L->length = 0;
    L->head = (Node *)malloc(sizeof(Node));
    L->head->data = 0;
    L->head->next = NULL;
    // 初始尾指针指向头结点
    L->tail = L->head;
    return L;
}

// 依次输出链表数值
void printList(linearList list)
{
    // 定义一个指针指向第一个存储元素的结点，并依次后移完成遍历
    Node *p = list.head->next;
    printf("表中有%d个元素\n", list.length);
    for (int i = 0; p != NULL; p = p->next)
    {
        printf("%d:|%d|", ++i, p->data);
        if (!p->next)
        {
            break;
        }
        printf("-->");
    }
    printf("\n");
}

// 头插法，每次插入将新结点插入到头结点后面位置，新结点的值为e，尾指针保持默认不操作（指向头结点）
void insertHead(linearList *L, int e)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = L->head->next;
    L->head->next = newNode;
    L->length++;
}

// 尾插法，每次将新结点插入到表尾，然后尾指针指向新插入的结点（需要额外定义一个尾指针）
void insertTail(linearList *L, int e)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = e;
    newNode->next = NULL;
    // 利用尾指针进行结点插入，先将新的结点连接到尾结点，再将尾指针后移
    L->tail->next = newNode;
    L->tail = newNode;
    L->length++;
}

// 查找数据为e的结点(假设存在为e的结点只有一个），查找到则返回指向该结点的指针，查找失败返回NULL
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

// 删除数据为e的结点（假设存在的话数据为e的结点只有一个），删除成功返回true，删除失败（无该结点）返回false
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
            L->length--;
            return true;
        }
        p = p->next;
    }
    return false;
}

// 完成两个有序链表的合并（非递减排序）
void mergeList(linearList *la, linearList *lb)
{
    // pa, pb直接指向第一个存储元素的结点
    Node *pa = la->head->next;
    Node *pb = lb->head->next;
    Node *pc = la->head; // 以la的头结点作为新表头结点
    // 开始合并
    la->length = la->length + lb->length;
    while (pa && pb)
    {
        // 较小的元素合并到la，同时两个表由pa，pb指针接管
        if (pa->data <= pb->data)
        {
            pc->next = pa;
            pc = pa; // pc = pc->next
            pa = pa->next;
        }
        else
        {
            pc->next = pb;
            pc = pb; // pc = pc->next
            pb = pb->next;
        }
    }
    // 两表之一已经全部合并，现在连接未完全合并的链表的剩余结点到la
    pc->next = pa ? pa : pb;
    la->tail = pa ? la->tail : lb->tail;
    free(lb->head);
    free(lb);
}

// 一个简单的实例让上面的函数执行结果可视化
int main()
{
    linearList *listEg_1 = initEmpty();
    linearList *listEg_2 = initEmpty();
    linearList *listEg_3 = initEmpty();
    // 对一个只有头结点的空表进行插入以生成一个链表，对eg1使用头插法，对eg2，eg3使用尾插法
    for (int i = 1; i <= 10; i++)
    {
        insertHead(listEg_1, i);
    }
    for (int i = 1; i <= 10; i++)
    {
        insertTail(listEg_2, i);
    }
    for (int i = -9; i <= 9; i += 2)
    {
        insertTail(listEg_3, i);
    }
    // 输出初始化的链表元素
    printf("头插法创建链表1:\n");
    printList(*listEg_1);
    printf("尾插法创建链表2:\n");
    printList(*listEg_2);
    printf("尾插法创建链表3:\n");
    printList(*listEg_3);
    // 在表1中查找元素，在表2中删除元素
    // 查找存在的元素 5
    if (findElem(*listEg_1, 5) != NULL)
    {
        printf("\n链表1中存在元素5, 下一个结点元素(verify)为 %d \n", findElem(*listEg_1, 5)->next->data);
    }
    else
    {
        printf("\n查找失败, 链表1中不存在元素5\n");
    }
    // 查找不存在的元素15
    if (findElem(*listEg_1, 15) != NULL)
    {
        printf("链表1中存在元素15, 下一个结点元素(verify)为 %d \n", findElem(*listEg_1, 15)->next->data);
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

    printf("\n处理后链表1无变化:\n");
    printList(*listEg_1);
    printf("链表2中元素5被删去:\n");
    printList(*listEg_2);
    // 尾插法创建表3，并和表2合并
    mergeList(listEg_2, listEg_3);
    printf("合并后链表2:\n");
    printList(*listEg_2);

    return 0;
}