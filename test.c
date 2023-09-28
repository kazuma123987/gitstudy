#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
typedef struct
{
   uint8_t a[3];
   uint16_t b;
   uint8_t c[0];//c[0]只能在结构体最后添加，形成可变长度的数组，比用指针定义的数组使用方便（指针数组需要两次malloc和free，而0长数组只需一次）
} type_t, *ptype_t,arrey[10];
int main()
{
   int lenth = 10;//定义c[0]要增加的长度
   type_t *x1, y1;
   ptype_t x2, y2;
   arrey z;//定义结构体数组z[10],相当于type_t z[10]
   z[1].a[0]=2;//和结构体数组一样的使用方法
   type_t *t1 = malloc(sizeof(type_t) + lenth);
   for (int i = 0; i < lenth; i++)
      t1->c[i] = i;
   printf("sizeof(type_t)=%d\n", sizeof(type_t));
   for (int i = 0; i < lenth; i++)
      printf("%d ", t1->c[i]);
   free(t1);
   t1 = NULL;
   return 0;
}
// 上述代码做了些什么？c[0]的作用是什么？各个变量占多少字节？（32位CPU）
// 覆盖知识点：结构体对齐、typedef用法、0长度数组、指针定义(详见https://blog.csdn.net/gatieme/article/details/64131322)