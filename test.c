#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
#include "stdbool.h"
#include "conio.h"
#define stack_size 2000
typedef struct{
   int size;
   int16_t data[0];//可变长度的数组
}arrey_stack;
//创建新栈
void create_stack(arrey_stack **s)
{
   *s=malloc(sizeof(arrey_stack)+stack_size);
   (*s)->size=0;
}
//清除栈
void free_stack(arrey_stack **s)
{
   free(*s);
   *s=NULL;
}
//入栈
void push_stack(arrey_stack *s,int16_t data)
{
   if(s->size<stack_size) s->data[s->size++]=data;
   else printf("栈已满\n");
}
//查看栈顶元素
int16_t peek_stack(arrey_stack *s)
{
   if(s->size!=0)
   return s->data[s->size-1];
   else
   {
      printf("栈已空\n");
      return EOF;
   }
}
//出栈
int16_t pop_stack(arrey_stack *s)
{
   if(s->size>0)
   {
      return s->data[--s->size];
   }
   else
   {
      printf("栈已空\n");
      return EOF;
   }
}
//判断栈是否为空
bool isEmpty(arrey_stack *s)
{
   return s->size==0;
}
//返回栈的长度
int size(arrey_stack *s)
{
   return s->size;
}
int main()
{
   int a=0;
   arrey_stack *S1=NULL;
   create_stack(&S1);
   push_stack(S1,1);
   push_stack(S1,2);
   while(S1->size)
   {
   printf("%d ",pop_stack(S1));
   }
   free_stack(&S1);
}