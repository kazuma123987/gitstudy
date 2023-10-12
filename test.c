#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <stdint.h>  //uint16_t,int8_t...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
typedef struct
{
    int size;
    int cap;
    int *arr;
}maxHeap;
//创建大顶堆
maxHeap *newheap()
{
    maxHeap *h=malloc(sizeof(maxHeap));
    h->cap=2;
    h->size=0;
    h->arr=malloc(sizeof(int)*h->cap);
    return h;
}
//析构函数
void heap_free(maxHeap *h)
{
    free(h->arr);
    free(h);
}
//左节点索引
int left_index(int index)
{
    return index*2+1;
}
//右节点索引
int right_index(int index)
{
    return index*2+2;
}
//父节点索引
int parent_index(int index)
{
    return (index-1)/2;
}
//交换函数
static void swap(maxHeap *h,int index1,int index2)
{
    int temp=h->arr[index1];
    h->arr[index1]=h->arr[index2];
    h->arr[index2]=temp;
}
//沿index所在路径向上堆化
void siftUp(maxHeap *h,int index)
{
    while(1)
    {
        int par=parent_index(index);
        if(h->arr[index]<=h->arr[par]||par<0)break;
        swap(h,index,par);
        index=par;
    }
}
//出堆的辅助堆化函数,从index所在节点沿着交换的路径向下堆化
void pop_sift(maxHeap *h,int index)
{
    int max=index;
    while(1)
    {
        int l=left_index(index);
        int r=right_index(index);
        if(h->arr[max]<h->arr[l]&&l<h->size)max=l;
        if(h->arr[max]<h->arr[r]&&r<h->size)max=r;//注意若左节点没越界但右节点越界了不能进行比较
        if(max==index)break;//如果索引越界或index所在处最大则跳出循环
        swap(h,index,max);
        index=max;
    }
}
//入堆
void push_heap(maxHeap *h,int val)
{
    if(h->size==h->cap)
    {
        h->cap*=2;
        h->arr=realloc(h->arr,sizeof(int)*h->cap);
    }
    h->arr[h->size++]=val;
    siftUp(h,h->size-1);
}
//出堆
int pop_heap(maxHeap *h)
{
    if(h->size==0)
    {
        printf("堆已空");
        return INT_MAX;
    }
    swap(h,0,h->size-1);
    int temp=h->arr[--h->size];
    pop_sift(h,0);
    return temp;
}
//无序列表转大顶堆
maxHeap *arrtoHeap(int *arr,int size)
{
    //创建无序堆
    maxHeap *h=malloc(sizeof(maxHeap));
    h->cap=size*2;
    h->size=size;
    h->arr=malloc(sizeof(int)*h->cap);
    memcpy(h->arr,arr,sizeof(int)*size);
    //无序堆有序化
    for(int i=parent_index(h->size-1);i>=0;i--)pop_sift(h,i);
    return h;
}
int main()
{
    int a[10]={7,3,2,8,9,0,1,5,4,6};
    maxHeap *h=arrtoHeap(a,sizeof(a)/sizeof(int));
    int size=h->size;
    for(int i=0;i<size;i++)
    {
        int val=pop_heap(h);
        printf("%d ",val);
    }
    heap_free(h);
}