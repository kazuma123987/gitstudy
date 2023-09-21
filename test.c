#include <stdio.h>
#include "stdlib.h"
#include "string.h"
typedef enum{//第一个enum元素默认为0，不受yellow=0干扰，enum元素（int ,long long int,unsigned long long随机调整）可以定义为负数
   red,orange,yellow=0,green=-3,blue='a',purple=0x111111111111//这里blue实际上等于a的ASCII码97
} color;//enum大小根据最长元素进行调整
typedef union{
   char a,b,c,d,e,f,g,h;
   int x;
   char str[10];
} xyz;//最长占用10个字节，但要是int的倍数所以为12个字节
typedef struct{
   enum color2{ red2,orange2,yellow2,green2,blue2};//未定义变量，为空结构体
}b1_struct;
typedef struct{
   enum color3{ red3,orange3,yellow3,green3,blue3}col;
   char a;
}b2_struct;//8
typedef struct{
   int a;//0
   char str[7];//4
   color b;//11->16
   b1_struct c;//20
   b2_struct d;//20->24
   char t[5];//32
   xyz e;//37->40（偏移量不是随联合体长度改变，而是随联合体内最大类型的长度（int）改变）
   char f[5];//52（用于验证偏移量不是随联合体长度改变）
}main_struct;//57->64(主要与enum元素有关，其占用8个字节)
//说明结构体最后一步填充地址主要看enum元素类型（实质上是多种整形变量）、char、int、double等占用字节，与结构体、联合体长度无关
int main()
{
   printf("sizeof(color)=%d\n",sizeof(color));//enum大小根据最长元素进行调整
   printf("sizeof(xyz)=%d\n",sizeof(xyz));//union为公用空间，长度为变量的最高占用空间且为最长类型的倍数
   printf("sizeof(b1_struct)=%d\n",sizeof(b1_struct));//该结构体没有变量，长度为0
   printf("sizeof(b2_struct)=%d\n",sizeof(b2_struct));//该结构体只有一个enum元素且占用空间为4
   printf("sizeof(main_struct)=%d\n",sizeof(main_struct));//对于多个元素的结构体需要逐步计算偏移量
}