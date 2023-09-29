#include <stdio.h>
#include "stdlib.h"
#include "string.h"
#include "stdint.h"
int main()
{
   int len=10;//定义要发送的数据长度
   char data[]="1010010110111100";//要发送的数据，实际长度可能比定义的长
   printf("data[1]=%d\n",data[1]);//在data[17]中，data[0]='1'=49,data[1]='0'=48,data[16]='\0'=0
   printf("-------------------分割线-------------------\n");
   /*-------------------%10s和%.10s-------------------*/
   printf("%10s\n",data);//虽小于data长度,但输出完整17字节数据
   printf("%20s\n",data);//大于data长度,输出完整17字节数据，多余的在左边用空格填充
   printf("%.10s\n",data);//小于data长度，只输出10字节数据
   printf("%.20s\n",data);//虽大于data长度,但只输出完整17字节数据
   printf("-------------------分割线-------------------\n");
   /*-------------------%*s和%.*s-------------------*/
   printf("%*s\n",len,data);//%10s
   printf("%*s\n",20,data);//%20s
   printf("%.*s\n",len,data);//%.10s
   printf("%.*s\n",20,data);//%.20s
}