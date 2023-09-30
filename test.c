#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"
#include "conio.h"
#include <assert.h>
// 节点
typedef struct _node
{
   int data;
   struct _node *next;
} Node;
// 栈
typedef struct _stack
{
   int size;
   Node *top;
} linkedlist_stack;
// 创建新栈
linkedlist_stack *create_stack()
{
   linkedlist_stack *s = malloc(sizeof(linkedlist_stack));
   s->top = malloc(sizeof(Node));
   s->top->next = NULL;
   s->top->data = EOF; // 栈底不存放数据
   s->size = 0;
   return s;
}
// 清理栈
void free_stack(linkedlist_stack **s)
{
   while ((*s)->top)//清理节点
   {
      Node *n = (*s)->top->next;
      free((*s)->top);
      (*s)->top = n;
   }
   free(*s);//清理栈
   *s = NULL;
}
// 入栈
void push_stack(linkedlist_stack *s, int data)
{
   Node *newNode = malloc(sizeof(Node));
   newNode->data = data;
   newNode->next = s->top;
   s->top = newNode;
   s->size++;
}
// 出栈
int pop_stack(linkedlist_stack *s)
{
   int ret = 0;
   if (s->size > 0)
   {
      Node *n = s->top;
      ret = n->data;
      s->top = n->next;
      free(n);
      s->size--;
   }
   else
   {
      printf("栈已空\n");
      ret = EOF;
   }
   return ret;
}
// 返回栈的长度
int size_stack(linkedlist_stack *s)
{
   return s->size;
}
//返回栈顶数据
int peek_stack(linkedlist_stack *s)
{
   return s->top->data;
}
int main()
{
   linkedlist_stack *s1 = create_stack();
   push_stack(s1, 1);
   push_stack(s1, 2);
   push_stack(s1, 3);
   push_stack(s1, 4);
   push_stack(s1, 5);
   printf("%d\n",peek_stack(s1));
   while(s1->size)
   {
      printf("%d ",pop_stack(s1));
   }
   free_stack(&s1);
}
