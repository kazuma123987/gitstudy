#include <stdio.h>
#include <stdlib.h>//malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h>//bool,true,false
#include <limits.h>//INT_MAX
#include <string.h>//memcpy,strcat...
//定义节点
typedef struct _node
{
   int data;
   struct _node *pre;//前一个节点
   struct _node *next;//后一个节点
}Node;
//定义双向队列
typedef struct _deque
{
   int size;
   Node *front;
   Node *rear;
}deque;
//创建双向队列
deque *create_deque()
{
   deque *q=malloc(sizeof(deque));
   q->front=q->rear=NULL;
   q->size=0;
}
//清除双向队列空间
void free_deque(deque **q)
{
   for(Node *cur=(*q)->front,*del=NULL;cur;del=cur,cur=cur->next)
      free(del);
   free(*q);
   *q=NULL;
}
//队首入队
void push_front(deque *q,int data)
{
   //创建新节点
   Node *newNode=malloc(sizeof(Node));
   newNode->data=data;
   newNode->pre=NULL;
   //连接节点
   if(q->front==NULL)
   {
      newNode->next=NULL;
      q->front=q->rear=newNode;
      q->size++;
      return;
   }
   q->front->pre=newNode;
   newNode->next=q->front;
   q->front=newNode;
   //更新队列长度
   q->size++;
}
//队尾入队
void push_rear(deque *q,int data)
{
   //创建新节点
   Node *newNode=malloc(sizeof(Node));
   newNode->data=data;
   newNode->next=NULL;
   //连接节点
   if(q->front==NULL)
   {
      newNode->next=NULL;
      q->front=q->rear=newNode;
      q->size++;
      return;
   }
   q->rear->next=newNode;
   newNode->pre=q->rear;
   q->rear=newNode;
   //更新队列长度
   q->size++;
}
//队首出队
int pop_front(deque *q)
{
   int ret=-1;
   Node *del=q->front;
   if(q->size==0)
   {
      printf("双向队列已空\n");
      return INT_MAX;//直接退出，防止对q->size造成干扰
   }
   else if(q->size==1)
   {
      ret=q->front->data;
      q->front=q->rear=NULL;
   }
   else
   {
   ret=q->front->data;
   q->front=q->front->next;
   q->front->pre=NULL;
   }
   free(del);
   q->size--;//别忘记更新队列长度
   return ret;
}
//队尾出队
int pop_rear(deque *q)
{
   int ret=-1;
   Node *del=q->rear;
   if(q->size==0)
   {
      printf("双向队列已空\n");
      return INT_MAX;//直接退出，防止对q->size造成干扰
   }
   else if(q->size==1)
   {
      ret=q->rear->data;
      q->front=q->rear=NULL;
   }
   else
   {
      ret=q->rear->data;
      q->rear=q->rear->pre;
      q->rear->next=NULL;
   }
   free(del);
   q->size--;//别忘记更新队列长度
   return ret;
}
//返回双向队列尺寸
int size_deque(deque *q)
{
   return q->size;
}
//判断双向队列是否为空
bool isEmpty(deque *q)
{
   return q->size==0;
}
int main()
{
   deque *q=create_deque();
   push_front(q,1);
   push_front(q,2);
   push_rear(q,3);
   printf("%d ",pop_rear(q));
   printf("%d ",pop_rear(q));
   printf("%d ",pop_rear(q));
   push_rear(q,4);
   printf("%d ",pop_front(q));
   free_deque(&q);
}