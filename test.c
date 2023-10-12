#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <stdint.h>  //uint16_t,int8_t...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
// 堆的作用:一般用于实现"优先队列"等动态更新的问题,处理流式数据，出堆和入堆的时间复杂度最低为O(logN),适合频繁进行插入和删除
/*---------top-K问题（给定一个长度为n无序数组nums,请返回数组中top k(前k大)的元素,且有新数据时要实时更新）----------*/
// 最小堆
typedef struct
{
    int size;
    int cap;
    int *arr;
} minHeap;
// 建立最小堆
minHeap *newheap()
{
    minHeap *h = malloc(sizeof(minHeap));
    h->cap = 2;
    h->size = 0;
    h->arr = malloc(sizeof(int));
    return h;
}
// 析构函数
void free_heap(minHeap *h)
{
    free(h->arr);
    free(h);
}
// 左节点索引
int left_index(int index)
{
    return index * 2 + 1;
}
// 右节点索引
int right_index(int index)
{
    return index * 2 + 2;
}
// 父节点索引
int parent_index(int index)
{
    return (index - 1) / 2;
}
//获取堆顶元素
int peek(minHeap *h)
{
    return h->arr[0];
}
// 交换函数
void swap(minHeap *h, int index1, int index2)
{
    int temp = h->arr[index1];
    h->arr[index1] = h->arr[index2];
    h->arr[index2] = temp;
}
// 自下而上沿大小交换路径有序化堆
void siftUp(minHeap *h, int i)
{
    while (1)
    {
        int p = parent_index(i);
        if (p < 0 || h->arr[i] >= h->arr[p])
            break;
        swap(h, i, p);
        i = p;
    }
}
// 自上而下沿大小交换路径有序化堆
void siftDown(minHeap *h, int i)
{
    int min = i;
    while (1)
    {
        int l = left_index(i);
        int r = right_index(i);
        if (h->arr[l] < h->arr[min] && l < h->size)
            min = l;
        if (h->arr[r] < h->arr[min] && r < h->size)
            min = r;
        if (i == min)
            break;
        swap(h, min, i);
        i = min;
    }
}
// 入堆
void push_heap(minHeap *h, int val)
{
    if (h->cap == h->size)
    {
        h->cap *= 2;
        h->arr = realloc(h->arr, sizeof(int) * h->cap);
    }
    h->arr[h->size++] = val;
    siftUp(h, h->size - 1);
}
// 出堆
int pop_heap(minHeap *h)
{
    if (h->size == 0)
    {
        printf("heap is empty!");
        return INT_MAX;
    }
    swap(h, 0, h->size - 1);
    int temp = h->arr[--h->size];
    siftDown(h, 0);
    return temp;
}
// 列表转最小堆
minHeap *arrToheap(int *arr, int size)
{
    minHeap *h = malloc(sizeof(minHeap));
    h->cap = size;
    h->size = size;
    h->arr = malloc(sizeof(int) * h->cap);
    memcpy(h->arr, arr, sizeof(int) * size);
    for (int i = parent_index(h->size - 1); i >= 0; i--)
        siftDown(h, i);
    return h;
}
//打印堆的元素
void print_heap(minHeap *h)
{
    minHeap *p=malloc(sizeof(minHeap));
    p->size=h->size;
    p->cap=h->cap;
    p->arr=malloc(sizeof(int)*p->cap);
    memcpy(p->arr,h->arr,sizeof(int)*h->size);
    int size=p->size;
    for(int i=0;i<size;i++)
    {
        int val=pop_heap(p);
        printf("%d ",val);
    }
    free_heap(p);
}
// 自定义scanf
void myscanf(int *n)
{
    char str[11]; // 最后一位会是'\0',最多保存10个字符
    fgets(str, 11, stdin);
    int index;
    if (str[index = strcspn(str, "\n")] == '\n')
        str[index] = '\0';
    else
        while (getchar() != '\n')
            ;
    *n = atoi(str);
}
int main(int argc, char *argv[])
{
    int arr[] = {4, 9, 5, 1, 0, 6, 8, 7, 2, 3};
    int size=sizeof(arr) / sizeof(int);
    int k = 0;
    while (1)
    {
        printf("input the value of 'k':\n");
        myscanf(&k);
        if(k > 0 && k < size)break;
        printf("error input!\n");
    }
    minHeap *h = arrToheap(arr, k);
    for(int i=k;i<size;i++)
    {
        if(arr[i]>peek(h))
        {
            pop_heap(h);
            push_heap(h,arr[i]);
        }
    }
    print_heap(h);
    printf("\n");
    srand(0);
    while(!kbhit())
    {
        int val=rand()%100+1;
        pop_heap(h);
        push_heap(h,val);
        Sleep(200);
    }
    print_heap(h);
    free_heap(h);
    return 0;
}
