// 先写main函数的大框架，再去根据需要写函数。
// 多项式的存储结构
#include <stdio.h>
#include <stdlib.h>
typedef struct term *polynomial;
struct term
{
    float coef;
    int exp;
    polynomial next;
};
// 用于存储测试数据的数组
typedef struct num {
    float *coef;
    int *exp;
    int length;
}Num;

// 测试数据：
// 多项式1:  3.1x^(-2) + 2.0x^1    + 1.0x^2 - 2.5x^4 + 3.0x^5
// 多项式2:  2.0x^(-3) - 1.0x^(-1) + 4.0    + 1.0x^1 - 1.0x^2 + 1.5x^4 + 1.0x^5
int main()
{
    // 函数声明
    void initPoly(polynomial L, Num num);
    void printPoly(polynomial poly);
    void insertTerm(float coef, int exp, polynomial L);
    void delPoly(polynomial L);
    polynomial sumPoly(polynomial L1, polynomial L2);
    polynomial multPoly(polynomial L1, polynomial L2);
    // 编写测试数据
    Num number_1, number_2;
    // float coef_1[5] = {3.1, 2.0, 1.0, -2.5, 3.0};
    // int expo_1[5] = {-2, 1, 2, 4, 5};
    // float coef_2[7] = {2.0, -1.0, 4.0, 1.0, -1.0, 1.5, 1.0};
    // int expo_2[7] = {-3, -1, 0, 1, 2, 4, 5};
    float coef_1[1] = {0};
    int expo_1[1] = {0};
    float coef_2[1] = {0};
    int expo_2[1] = {0};
    number_1.coef = coef_1;
    number_1.exp = expo_1;
    number_1.length = 1;
    number_2.coef = coef_2;
    number_2.exp = expo_2;
    number_2.length = 1;
    // 多项式定义
    polynomial poly_1 = (polynomial)malloc(sizeof(struct term));
    polynomial poly_2 = (polynomial)malloc(sizeof(struct term));
    polynomial poly_sum, poly_mult;
    // 多项式初始化
    initPoly(poly_1, number_1);
    initPoly(poly_2, number_2);
    insertTerm(0,0,poly_1);
    // 输出
    printPoly(poly_1);
    printPoly(poly_2);
    // 多项式相加
    printf("相加结果 \n");
    poly_sum = sumPoly(poly_1, poly_2);
    printPoly(poly_sum);
    printf("相乘结果 \n");
    poly_mult = multPoly(poly_1, poly_2);
    printPoly(poly_mult);
    delPoly(poly_1);
    delPoly(poly_2);
    delPoly(poly_mult);
    delPoly(poly_sum);
    return 0;
}
// 使用给定的数值，导入多项式的各项
void initPoly(polynomial L, Num num)
{
    void insertTerm(float coef, int exp, polynomial L);
    // 头节点不存储数据
    L->coef = 0;
    L->exp = 0;
    L->next = NULL;
    for (int i = 0; i < num.length; ++i)
    {
        insertTerm(num.coef[i], num.exp[i], L);
    }
}
// 向多项式中插入新项，并按照插入项的指数和多项式中项指数大小关系作插入，合并或者合并系数为0作删除
void insertTerm(float coef, int exp, polynomial L)
{
    // 系数为0的项插入无意义，直接退出
    if (coef == 0)
    {
        return;
    }
    polynomial pnew = (polynomial)malloc(sizeof(struct term));
    // p作遍历指针，front作p前面的指针，用于删除操作
    polynomial p = L->next, front = L;
    pnew->coef = coef;
    pnew->exp = exp;
    pnew->next = NULL;
    // L为空，直接插入表尾
    if (L->next == NULL)
    {
        L->next = pnew;
    }
    else // L不为空，说明表内有元素，需要将pnew的指数和多项式中各项指数比较，确定插入的位置，如果找到有指数相等的项，还要进行合并操作
    {
        while (p != NULL)
        {
            if (p->exp < pnew->exp) // p指向节点的指数较小，说明任需要向后确认pnew的插入位置
            {
                p = p->next;
                front = front->next;
            }
            else if (p->exp == pnew->exp) // p指向节点的指数和pnew指向节点的指数相等，进行合并操作
            {
                p->coef += pnew->coef;
                // 系数和为0需要删去原节点，不为0则不用，不过最终都需要释放pnew指向内存
                if (p->coef == 0)
                {
                    front->next = p->next;
                    free(p);
                    free(pnew);
                }
                else
                {
                    free(pnew);
                }
                return;
            }
            else if (p->exp > pnew->exp) // p指向节点指数已经大于pnew指数，说明插入位置就是p指向节点前面
            {
                pnew->next = p;
                front->next = pnew;
                return;
            }
        }
        front->next = pnew; // 如果没有return结束，说明上面的while循环自然结束，也就是说至始至终p指向的节点指数都比pnew指向节点指数小，需要在结尾插入
    }
}

// 输出多项式
void printPoly(polynomial L)
{
    printf("Polynomial:\n");
    if (L->next == NULL)// 为空则输出单个0即可
    {
        printf("0\n");
        return;
    }
    polynomial p = L->next;
    while (p != NULL)
    {
        printf("(%.1f)x^(%d)", p->coef, p->exp);
        p = p->next;
        if (p == NULL)
        {
            break;
        }
        printf(" + ");
    }
    printf("\n");
}

// 相加，返回指向结果多项式头节点的指针
polynomial sumPoly(polynomial L1, polynomial L2)
{
    polynomial p1 = L1->next, p2 = L2->next;
    polynomial Lsum = (polynomial)malloc(sizeof(struct term));
    Lsum->coef = 0;
    Lsum->exp = 0;
    Lsum->next = NULL;
    // 指数小的项插入L3，插入项的多项式遍历指针后移
    while(p1 && p2)
    {
        if (p1->exp <= p2->exp)
        {
            insertTerm(p1->coef, p1->exp, Lsum);
            p1 = p1->next;
        }
        else if (p1->exp > p2->exp)
        {
            insertTerm(p2->coef, p2->exp, Lsum);
            p2 = p2->next;
        }
    }
    while (p1 != NULL)
    {
        insertTerm(p1->coef, p1->exp, Lsum);
        p1 = p1->next;
    }
    while (p2 != NULL)
    {
        insertTerm(p2->coef, p2->exp, Lsum);
        p2 = p2->next;
    }
    return Lsum;
}

// 多项式相乘，并返回结果多项式的头节点指针
polynomial multPoly(polynomial L1, polynomial L2)
{
    polynomial p1 = L1->next, p2 = L2->next;
    polynomial Lm = (polynomial)malloc(sizeof(struct term));
    Lm->coef = 0;
    Lm->exp = 0;
    Lm->next = NULL;
    if (L1 == NULL || L2 == NULL)
    {
        return Lm;
    }
    else{
        for (; p1 != NULL; p1 = p1->next)
        {
            for (p2 = L2->next; p2 != NULL; p2 = p2->next)
            {
                insertTerm(p1->coef * p2->coef, p1->exp+p2->exp, Lm);
            }
        }
    }
    return Lm;
}

void delPoly(polynomial L)
{
    polynomial p = L, tmp = NULL;
    while (p != NULL)
    {
        tmp = p;
        p = p->next;
        free(tmp);
    }
}