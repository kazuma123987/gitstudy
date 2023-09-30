#include <stdio.h>
#include <stdlib.h>//malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h>//bool,true,false
#include <limits.h>//INT_MAX
#include <string.h>//memcpy,strcat...
#define data_size 4
//定义链表节点
typedef struct _node
{
   char data[data_size];
   struct _node *next; 
}Node;
//定义队列
typedef struct _quene
{
   int size;
   Node *front;
   Node *rear;
}linkedlist_quene;
//创建新队列
linkedlist_quene *create_quene()
{
   linkedlist_quene *q=malloc(sizeof(linkedlist_quene));
   q->front=q->rear=NULL;
   q->size=0;
   return q;
}
//清除队列
void free_quene(linkedlist_quene **q)
{
   for(Node *cur=(*q)->front,*del=NULL;cur;del=cur,cur=cur->next)
   {
      free(del);
   }
   free(*q);
   *q=NULL;
}
//入队
void push_quene(linkedlist_quene *q,char *data)
{
   Node *newNode=malloc(sizeof(Node));
   memcpy(newNode->data,data,data_size-1);
   newNode->data[data_size-1]='\0';
   newNode->next=NULL;
   if(q->front==NULL)q->front=q->rear=newNode;
   else
   {
      q->rear->next=newNode;
      q->rear=newNode;
   }
   q->size++;
}
//出队
char *pop_quene(linkedlist_quene *q)
{
   static char ret[data_size]={0};//static调用的变量全局存在
   Node *node=q->front;
   if(q->front==NULL)//队列为空
   {
      printf("队列已空\n");
      return NULL;
   }
   else if(q->front==q->rear)//队列只有一个节点
   {
      memcpy(ret,node->data,data_size-1);
      q->front=q->rear=NULL;
   }
   else//队列不只有一个节点
   {
      memcpy(ret,node->data,data_size-1);
      q->front=q->front->next;
   }
   q->size--;//出队后队列长度-1
   free(node);//清除出队的节点
   return ret;//返回静态局部变量的地址
}
//返回队列的长度
int size_quene(linkedlist_quene *s)
{
   return s->size;
}
int main()
{
   linkedlist_quene *q=create_quene();
   push_quene(q,"12345");
   push_quene(q,"23456");
   push_quene(q,"34567");
   printf("%s\n",pop_quene(q));
   printf("%s\n",pop_quene(q));
   printf("%s\n",pop_quene(q));
   printf("%s\n",pop_quene(q));
   free_quene(&q);
}

