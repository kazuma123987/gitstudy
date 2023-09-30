#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
//默认为顺环队列
typedef struct _quene
{
   int front;//队首
   int rear;//队尾+1，无数据
   int queCapacity;//队列大小，实际能放的元素为大小-1
   int data[0];//队列元素
}arrey_quene;
//创造队列
arrey_quene *create_quene(int capacity)
{
   arrey_quene *q=malloc(sizeof(arrey_quene)+capacity);//实际能放的元素为大小-1
   q->front=q->rear=0;
   q->queCapacity=capacity;
   return q;
}
//删除队列
void free_quene(arrey_quene **q)
{
   free(*q);
   *q=NULL;
}
//入队
void push_quene(arrey_quene *q,int data)
{
   if((q->rear+1)%(q->queCapacity)==q->front)printf("队列已满\n");
   else 
   {
      q->data[q->rear]=data;
      q->rear=(q->rear+1)%q->queCapacity;
   }
}
//出队
int pop_quene(arrey_quene *q)
{
   if(q->rear==q->front)
   {
      printf("队列已空");
      return INT_MAX;
   }
   else 
   {
      int ret=q->data[q->front];
      q->front=(q->front+1)%q->queCapacity;
      return ret;
   }
}
//判断队列是否为空
bool isEmpty(arrey_quene *q)
{
   return q->front==q->rear;
}
//返回队列最大容量
int quene_cap(arrey_quene *q)
{
   return (q->queCapacity-1);
}
int main(int argc,char *args[])
{
   arrey_quene *q=create_quene(4);
   push_quene(q,1);
   push_quene(q,2);
   push_quene(q,3);
   push_quene(q,4);
   while(!isEmpty(q))printf("%d ",pop_quene(q));
   free_quene(&q);
   return 0;
}
