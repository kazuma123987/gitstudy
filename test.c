#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
typedef struct _node
{
   int data;
   struct _node *next;
} Node;
typedef struct _list
{
   Node *head;
   Node *tail;
} List;
void add_Node(List *list, int number);
void list_print(Node *p);
int myscanf_int(int *n, int size);
int main()
{
   int number = 0;
   List list1;
   list1.head = list1.tail = NULL;
   while (1)
   {
      printf("输入数据为链表赋值，-1表示停止赋值\n");
      myscanf_int(&number, 9);
      if (number == -1)
         break;
      add_Node(&list1, number);
   }
   list_print(list1.head);
}
void add_Node(List *list, int number)
{
   //创建新节点
   Node *newNode = (Node *)malloc(sizeof(Node));
   newNode->data = number;
   newNode->next = NULL;
   //连接节点
   if (list->tail!=NULL)//如果链表的尾部指向的不是NULL则将新节点连接到tail后面
   {
      list->tail->next = newNode;
      list->tail = list->tail->next;
   }
   else //如果链表的尾部指向的是NULL，则将头部和尾部都连接到新节点
      list->tail = list->head = newNode;
}
void list_print(Node *p)
{
   while (p != NULL)
   {
      printf("%d ", p->data);
      p = p->next;
   }
}
int myscanf_int(int *n, int size)
{
   if (size > 0)
      size++;
   else
      printf("size应为正整数\n");
   char str[size];
   fgets(str, size, stdin);
   if (str[strcspn(str, "\n")] == '\n')
      str[strcspn(str, "\n")] == '\0';
   else
      while (getchar() != '\n')
         ;
   *n = atoi(str);
}