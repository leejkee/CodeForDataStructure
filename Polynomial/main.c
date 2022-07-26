/* 一元多项式的相加和相乘运算 */
// 定义结构->初始化操作->free操作->基本操作->问题解决

#include <stdio.h>
#include <stdlib.h>

// 定义多项式节点
typedef struct node
{
    float coef; // 系数
    int expo;   // 指数
    struct node *next;
} Term;
// 定义多项式，包含一个指向头节点的指针，一个指向尾节点的指针
typedef struct
{
    Term *head;
    Term *tail;
} polynomial;

// 生成一个带头节点的空多项式，其中头节点不存储项，系数设置为0，指数设置为-1，尾指针初始指向头节点
polynomial *initPoly()
{
    polynomial *L = (polynomial *)malloc(sizeof(polynomial));
    L->head = (Term *)malloc(sizeof(Term));
    L->head->coef = 0;
    L->head->expo = -1;
    L->head->next = NULL;
    L->tail = L->head;
    return L;
}
// 初始化项，返回指向系数为coef，指数为expo的项的指针
Term *initTerm(float coef, int expo)
{
    Term *newNode = (Term *)malloc(sizeof(Term));
    newNode->coef = coef;
    newNode->expo = expo;
    newNode->next = NULL;
    return newNode;
}

// 释放节点的内存
void delTerm(Term *Node)
{
    if (Node == NULL)
    {
        return;
    }
    free(Node);
}

// 释放多项式的内存，由于在初始化时申请了头节点，所以释放要从头节点开始释放，先释放全部节点的空间，再释放多项式本身的内存
void delPoly(polynomial *L)
{
    if (L == NULL)
    {
        return;
    }
    Term *p = L->head, *q = NULL;
    while (p != NULL)
    {
        q = p->next;
        delTerm(p);
        p = q;
    }
    free(L);
}

// 向多项式中新增一个项
void insertTerm(polynomial *L, float coef, int expo)
{
    Term *q = initTerm(coef, expo);
    // 为了保证是按照指数从小到大排序，采用尾插法进行插入新节点
    L->tail->next = q;
    L->tail = q;
}

// 数组存储测试数据导入多项式
void insertPoly(polynomial *L, float *coef, int *expo, int num)
{
    float *p = coef;
    int *q = expo;
    while (num--)
    {
        insertTerm(L, *p, *q);
        p++;
        q++;
    }
}

// 输出多项式
void printPoly(polynomial poly)
{
    Term *p = poly.head->next;
    printf("\nPolynomial:\n");
    while (p != NULL)
    {
        printf("(%.1f)x^(%d)", p->coef, p->expo);
        p = p->next;
        if (!p)
        {
            break;
        }
        printf(" + ");
    }
    printf("\n");
}

// 两个多项式相加
// 思路：对应比较项指数大小，三种情况：
// 1）1式大于2式，取2式项先导入，同时2式遍历指针后移与1式继续比较指数
// 2）1式小于2式，则取1式。。。
// 3）两式项指数相等，则合并，系数相加，并删去一个节点，若系数和为0则同时后移遍历指针的同时释放节点
// 测试数据：
// 多项式1:  3.1       + 2.0x^1    + 1.0x^2 - 2.5x^4 + 3.0x^6
// 多项式2:  2.0x^(-3) - 1.0x^(-1) + 4.0    + 1.0x^1 - 1.0x^2 + 1.5x^4 + 1.0x^5
void sumPoly(polynomial *L1, polynomial *L2)
{
    // 最终多项式合并到1式，结束后free(L2)
    int compare(int a, int b);
    Term *p1 = L1->head->next, *p2 = L2->head->next, *pNew = L1->head, *pTemp = NULL;
    while (p1 && p2)
    {
        switch (compare(p1->expo, p2->expo))
        {
        case 1:
        { // p1>p2
            pNew->next = p2;
            pNew = p2;
            p2 = p2->next;
            break;
        }
        case -1:
        { // p1<p2
            pNew->next = p1;
            pNew = p1;
            p1 = p1->next;
            break;
        }
        case 0:
        { // p1=p2
            if (0 == p1->coef + p2->coef)
            {
                pTemp = p1;
                p1 = p1->next;
                delTerm(pTemp);
                pTemp = p2;
                p2 = p2->next;
                delTerm(pTemp);
            }
            else
            {
                p1->coef = p1->coef + p2->coef;
                pNew->next = p1;
                pNew = p1;
                p1 = p1->next;
                pTemp = p2;
                p2 = p2->next;
                delTerm(pTemp);
            }
            break;
        }
        default:
            break;
        }
    }
    pNew->next = p1 ? p1 : p2;
    L2->head->next = NULL;
    delPoly(L2);
}

int compare(int a, int b)
{
    if (a > b)
    {
        return 1;
    }
    else if (a < b)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
// 测试数据：
// 多项式1:  3.1       + 2.0x^1    + 1.0x^2 - 2.5x^4 + 3.0x^6
// 多项式2:  2.0x^(-3) - 1.0x^(-1) + 4.0    + 1.0x^1 - 1.0x^2 + 1.5x^4 + 1.0x^5
int main()
{
    float coef_1[5] = {3.1, 2.0, 1.0, -2.5, 3.0};
    int expo_1[5] = {0, 1, 2, 4, 6};
    float coef_2[7] = {2.0, -1.0, 4.0, 1.0, -1.0, 1.5, 1.0};
    int expo_2[7] = {-3, -1, 0, 1, 2, 4, 5};

    polynomial *polyEg_1 = initPoly();
    polynomial *polyEg_2 = initPoly();
    insertPoly(polyEg_1, coef_1, expo_1, 5);
    insertPoly(polyEg_2, coef_2, expo_2, 7);
    printPoly(*polyEg_1);
    printPoly(*polyEg_2);
    sumPoly(polyEg_1, polyEg_2);
    printPoly(*polyEg_1);
    delPoly(polyEg_1);
    // delPoly(polyEg_2); 在sumPoly()已经free L2
    return 0;
}

// 输入数值，测试太麻烦
// void addTerm(polynomial *L)
// {
//     int count = 0;
//     float coef = 0;
//     int expo = 0;
//     printf("The number of Terms for this polynomial:");
//     scanf(" %d", &count);
//     printf("Init for Terms starts.\n");
//     for (int i = 1; i <= count; i++)
//     {
//         printf("Term%d:\n", i);
//         printf("coef: ");
//         scanf(" %f", &coef);
//         printf("expo: ");
//         scanf(" %d", &expo);
//         insertOrder(L, coef, expo);
//     }
// }