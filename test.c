#include <stdio.h>
#include "string.h"
#include "stdint.h"
/*-----------------------------------notice-----------------------------------

所有类型左移都是空位(低位)补0，
unsigned类型右移高位补0，而非unsigned类型(int ,char ,long等)右移高位保持不变

-------------------------------------notice---------------------------------*/
typedef struct
{
   uint8_t sfr1:2;//这里冒号后面的叫做位段,表示其占用的位数
   uint8_t sfr2:1;
   uint8_t sfr3:1;
   uint8_t sfr4:4;
}SFR;//加了位段也要保证结构体占用字节数为结构体内最大元素长度的倍数

int main()
{
   SFR r;
   r.sfr1=2;
   r.sfr2=1;
   r.sfr3=0;
   r.sfr4=4;
   unsigned char mask=1u<<7;//1000 0000
   for(;mask;mask>>=1)//只有unsigned类型最高位为1时右移补0
   {
      printf("%d",(*(char*)&r)&mask?1:0);//强制把结构体变量类型转化为char类型后输出其二进制
   }
   printf("\n");
   printf("sizeof(SFR)=%d\n",sizeof(SFR));
}