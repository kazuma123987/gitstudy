#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "time.h"
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
void list_delete(List *list,int delete_num);
void list_print(List *list);//直接传结构体其占用空间过大，传递指针只占用4-8个字节
void myscanf_int(int *n, int size);
void list_free(List *list);//直接传结构体其占用空间过大，传递指针只占用4-8个字节
int main()
{
   clock_t start,stop;
   double duration;
   start=clock();
   int number = 0;
   List list[2];
   list[0].head = list[0].tail = NULL;
      printf("输入数据为链表赋值，-1表示停止赋值\n");
      add_Node(&list[0], 1);
      add_Node(&list[0], 2);
      add_Node(&list[0], 3);
      add_Node(&list[0], 4);
      add_Node(&list[0], 5);
   list_delete(&list[0],3);
   list_print(&list[0]);//直接传结构体其占用空间过大，传递指针只占用4-8个字节
   list_free(&list[0]);//直接传结构体其占用空间过大，传递指针只占用4-8个字节 */
   stop=clock();
   duration=((double)(stop-start))/CLK_TCK;
   printf("程序花费%llf秒\n",duration);
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
void list_delete(List *list,int delete_num)
{
   Node *current,*pre;//pre指向current之前的结构体
   for(current=list->head,pre=NULL;current;pre=current,current=current->next)/*出循环的条件是current指向NULL，
   每次出循环后pre指向current的结构体,current指向下一个结构体*/
   {
      if(current->data==delete_num)//找到了要删除的节点
      {
         if(pre==NULL)//如果要删除头节点
         {
            list->head=list->head->next;
            free(current);
         }
         else
         {
            pre->next=current->next;
            free(current);
         }
         break;
      }
   }
}
void list_print(List *list)
{
   Node *p=list->head;
   while (p!= NULL)
   {
      printf("%d ", p->data);
      p = p->next;
   }
}
void list_free(List *list)
{
   Node *p=list->head;
   while(p!=NULL)
   {
   Node *current=p;
   p=p->next;
   free(current);
   }  
}
void myscanf_int(int *n, int size)
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