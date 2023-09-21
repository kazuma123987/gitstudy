#include <stdio.h>
#include "string.h"
int main()
{
   printf("this function is:%s\n",__func__);
   printf("this file is:%s\n",__FILE__);
   printf("this line is:%d\n",__LINE__);
   printf("this date is:%s\n",__DATE__);
   printf("this time is:%s\n",__TIME__);
   printf("sizeof(__DATE__)=%d\n",sizeof(__DATE__));
}