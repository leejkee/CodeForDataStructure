/*
 * @Author: leejkee
 * @FilePath: \linklist\main.c
 * @Date: 2022-05-28 19:38:38
 * @LastEditTime: 2022-05-29 17:11:52
 * @Description: 顺序表
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXSIZE 100
typedef struct sequence
{
    int *data;
    int length;
} Sequence;

// initialization
// 初始化一个空表，长度设置为0，data指向MAXSIZE大的空间基址
Sequence *init()
{
    Sequence *p = (Sequence *)malloc(sizeof(Sequence));
    p->data = (int *)malloc(sizeof(int) * MAXSIZE);
    p->length = 0;
    return p;
}

// get the ith data
// 找出第i个数，i不合法则返回false，数值存储到数组result中
bool getElem(Sequence sq, int i, int *pe)
{
    if (i < 1 || i > sq.length)
    {
        return false;
    }
    *pe = sq.data[i-1];
    return true;
}
// get a data equaling e
// 在顺序表中找一个等于e的data，找到了返回1，找不到返回0
bool locateElem(Sequence sq, int e, int *num)
{
    for (int i = 0; i < sq.length; ++i)
    {
        if (e == sq.data[i])
        {
            *num = i+1;
            return true;
        }
    }
    return false;
}

// insert
// 在第i位置之前插入元素e，插入失败返回false
bool insertElem(Sequence *sq, int i, int e)
{
    if (i < 1 || i > sq->length || sq->length == MAXSIZE)
    {
        return false;
    }
    // 顺序表插入需要后移元素，所以从表尾巴开始移动，data[i-1]到data[j]都需要移动
    for (int j = sq->length-1 ; j >= i-1; j--)
    {
        sq->data[j+1] = sq->data[j];
    }
    sq->data[i-1] = e;
    // 插入成功别忘记增加表长
    sq->length++;
    return true;
}

// delete
// 删除第i个元素，删去data[i-1]，则data[i-1]=data[i]依次操作到data[length-2]=data[length-1]，最终length减一
bool deleteElem(Sequence *sq, int i)
{
    if (sq == NULL || i < 1 || i > sq->length)
    {
        return false;
    }
    for (int j = i - 1; j < sq->length - 1; j++)
    {
        sq->data[j] = sq->data[j+1];
    }
    sq->length--;
    return true;
}

void printTable(Sequence sq)
{
    for (int i = 0; i < sq.length; i++)
    {
        printf("data[%d] = %d\n", i, sq.data[i]);
    }

}

int main()
{
    void initialize(Sequence *sp, int n);
    Sequence *table = init();
    // r[0]存储提取的第i个数值，r[1]存储数值为e的元素序号
    int r[2] = {0};
    initialize(table, 20);
    printf("insert 20 numbers to the table.\n");

    printTable(*table);
    // 如果查找不到会输出提示语，查找不到不输出查询结果需要将查询结果加到else中，这里略去
    if (getElem(*table, 5, r) == false)
    {
        printf("read the %dth number failed.\n", 5);
    }
    if (locateElem(*table, 8, r+1) == false)
    {
        printf("can't find the data equaling %d.\n", 8);
    }
    printf("the %dth number is %d, the %dth number equals %d.\n", 5, r[0], r[1], 8);
    // insert
    printf("insert:\n");
    if (insertElem(table, 12, 76) == false)
    {
        printf("insert %d before the item %d failed.\n", 76, 12);
    }
    
    printTable(*table);
    // delete
    printf("delete:\n");
    if (deleteElem(table, 12) == false)
    {
        printf("delete the %dth item failed.\n", 12);
    }

    printTable(*table);
    return 0;
}

// 测试使用初始化函数，初始化20个单位
void initialize(Sequence *sq, int n)
{
    for (int i = 0; i < n; i++)
    {
        sq->data[i] = i;
        sq->length++;
    }
}