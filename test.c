#include <stdio.h>
#include "stdlib.h"
typedef struct _poly
{
   int coef;  // 系数
   int expon; // 指数
   struct _poly *next;
} Poly; // 多项式链表单元素结构
typedef struct _list
{
   struct _poly *head;
   struct _poly *tail;
} List; // 链表封装
void attach_node(int coef, int expond, List *list)
{
   // 创建新节点
   Poly *newNode = (Poly *)malloc(sizeof(Poly));
   newNode->coef = coef;
   newNode->expon = expond;
   newNode->next = NULL;
   // 连接节点并把tail指向链表末尾
   list->tail->next = newNode;
   list->tail = list->tail->next;
}
void create_poly(List *list)
{
   int N;            // 多项式项数
   int coef, expond; // 多项式系数与指数
   // 创建临时节点为其分配空间（该节点不存放数据）,并把head和tail指向该节点，并让下一个节点为NULL
   Poly *temp = (Poly *)malloc(sizeof(Poly));
   list->tail = list->head = temp;
   list->head->next = NULL;
   // 读取多项式系数和指数
   printf("请输入多项式的项数：\n");
   scanf("%d", &N);
   while (getchar() != '\n')
      ;
   while (N--)
   {
      printf("请由高位向低位输入系数coef和指数expond:\n");
      scanf("%d%d", &coef, &expond);
      while (getchar() != '\n')
         ;
      attach_node(coef, expond, list);
   }
   // 删除临时的空节点
   list->head = list->head->next;
   free(temp);
}
void add_terms(int coef, int expon, List *list)
{
   // 创建新节点
   Poly *newNode = (Poly *)malloc(sizeof(Poly));
   newNode->coef = coef;
   newNode->expon = expon;
   newNode->next = NULL;
   // 根据指数大小进行排序或相加
   if (list->head == NULL) // 如果head为空则直接连接新节点
   {
      list->tail = list->head = newNode;
   }
   else if (list->tail->expon > expon) // 如果链表结尾的指数大于新节点的指数则把新节点放在后面
   {
      list->tail->next = newNode;
      list->tail = list->tail->next;
   }
   else if (list->tail->expon == expon) // 如果链表结尾的指数等于新节点指数则把新节点相加
   {
      if (list->tail->coef + coef != 0)//如果系数相加不等于0则只做加法
         list->tail->coef += coef;
      else
      {
         Poly *p = list->head, *q = p;//如果系数相加为0则需要删除最后一个节点并把前一个节点指向NULL(重要)
         if (p->next == NULL)//如果是第一个节点直接删除并初始化为NULL即可
         {
            list->head = list->tail = NULL;
            free(p);
         }
         else//如果不是第一个节点则按上面的方法进行删除
         {
            for (; p->next; q = p, p = p->next)
               ;
            list->tail = q;
            q->next=NULL;/******************************注意这里的赋值很重要************************************/
            free(p);
         }
      }
   }
   else//如果结尾的指数小于新节点指数则需要从头遍历
   {
      for (Poly *p = list->head, *q = NULL; p; q = p, p = p->next)//定义了p,q,之后q将会是p的前一个节点
      {
         if (p->expon < expon)//如果遍历到了比新节点指数小的节点
         {
            if (p == list->head)//如果是头节点则将新节点作为新的头节点,把head指向新节点并连接
            {
               newNode->next = list->head;
               list->head = newNode;
            }
            else//如果不是头节点则把新节点添加到前一个节点和当前节点之间
            {
               q->next = newNode;
               newNode->next = p;
            }
            break;
         }
         else if (p->expon == expon)//如果遍历到了和新节点指数相等的节点
         {
            if (p->coef + coef != 0)//如果系数相加不等于0则只做加法
               p->coef += coef;
            else//如果系数相加为0则需要删除最后一个节点并把前一个节点指向NULL(重要)
            {
               Poly *p1 = list->head, *q1 = p1;
               if (p1->next == NULL)//如果是第一个节点直接删除并初始化为NULL即可
               {
                  list->head = list->tail = NULL;
                  free(p1);
               }
               else//如果不是第一个节点则按上面的方法进行删除
               {
                  for (; p1->next; q1 = p1, p1 = p1->next)
                     ;
                  list->tail = q1;
                  q1->next=NULL;/******************************注意这里的赋值很重要************************************/
                  free(p1);
               }
            }
         }
      }
   }
}
void poly_mul(List *list1, List *list2, List *list_mul)
{
   Poly *p1, *p2;
   for (p1 = list1->head; p1; p1 = p1->next)
      for (p2 = list2->head; p2; p2 = p2->next)
         add_terms((p1->coef) * (p2->coef), (p1->expon) + (p2->expon), list_mul);
}
void print_poly(List *list)
{
   // 打印多项式的式子
   for (Poly *p = list->head; p; p = p->next)
   {
      printf("%d", p->coef);
      if (p->expon > 0)
         printf("x");
      if (p->expon > 1)
         printf("^%d", p->expon);
      if (p->next)
         printf("+");
   }
   printf("\n");
}
void free_list(List *list)
{
   // 清除链表空间
   Poly *p = list->head, *current;
   while (p)
   {
      current = p;
      p = p->next;
      free(current);
   }
}
int main()
{
   List list[2]; // 定义两个链表
   List *list_mul = (List *)malloc(sizeof(List));
   list_mul->head = list_mul->tail = NULL;
   create_poly(&list[0]);
   create_poly(&list[1]);
   poly_mul(&list[0], &list[1], list_mul);
   print_poly(&list[0]);
   print_poly(&list[1]);
   print_poly(list_mul);
   free_list(&list[0]);
   free_list(&list[1]);
   free_list(list_mul);
}