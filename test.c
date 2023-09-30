#include <stdio.h>
#include <stdlib.h>//malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h>//bool,true,false
#include <limits.h>//INT_MAX
#include <string.h>//memcpy,strcat...
#define data_size 4
//定义存放数据的结构体
typedef struct{
   int num;
   char data[data_size];
}Data;
//定义双向队列(double-ended quene)
typedef struct _deque
{
   int front;//指向头节点
   int rear;//指向没有数据的尾节点
   int captacity;//双向队列容量
   Data data[0];//数据存放区
}deque;
//创造新的双向队列
deque *create_deque(int captacity)
{
   deque *q=malloc(sizeof(deque)+sizeof(Data)*captacity);//只能存放captacity-1个数据
   q->front=q->rear=0;
   q->captacity=captacity;
   return q;
}
//队首入队
void push_front(deque *q,char *data,int num)
{
   if((q->rear+1)%q->captacity==q->front)
   {
      printf("双向队列已满\n");
      return;
   }
   q->front=(q->front+q->captacity-1)%q->captacity;
   memcpy(q->data[q->front].data,data,data_size-1);
   q->data[q->front].data[data_size-1]='\0';
   q->data[q->front].num=num;
}
//队尾入队
void push_rear(deque *q,char *data,int num)
{
   if((q->rear+1)%q->captacity==q->front)
   {
      printf("双向队列已满\n");
      return;
   }
   memcpy(q->data[q->rear].data,data,data_size-1);
   q->data[q->rear].data[data_size-1]='\0';
   q->data[q->rear].num=num;
   q->rear=(q->rear+1)%q->captacity;
}
//队首出队
void pop_front(deque *q,char *data,int *num)
{
   if(q->front==q->rear)
   {
      printf("双向队列已空\n");
      return;
   }
   memcpy(data,q->data[q->front].data,data_size);
   *num=q->data[q->front].num;
   q->front=(q->front+1)%q->captacity;
}
//队尾出队
void pop_rear(deque *q,char *data,int *num)
{
   if(q->front==q->rear)
   {
      printf("双向队列已空\n");
      return;
   }
   memcpy(data,q->data[(q->captacity+q->rear-1)%q->captacity].data,data_size);
   *num=q->data[(q->captacity+q->rear-1)%q->captacity].num;
   q->rear--;
}
//返回双向队列长度
int size_deque(deque *q)
{
   return (q->rear+q->captacity-q->front)%q->captacity;
}
//判断双向队列是否为空
bool isEmpty(deque *q)
{
   return q->rear==q->front;
}
int main()
{
   int cap=5;
   deque *q=create_deque(cap);//创建一个最大容量为4的双向队列
   Data data[cap];
   push_front(q,"12345",6);
   push_front(q,"23456",7);
   push_rear(q,"hello",9174);
   push_rear(q,"world",1357);
   push_rear(q,"world",1357);
   int size=size_deque(q);
   for(int i=0;i<size;i++)
      pop_front(q,data[i].data,&data[i].num);
   for(int i=0;i<size;i++)
      printf("str%d=%s,num%d=%d\n",i,data[i].data,i,data[i].num);
}