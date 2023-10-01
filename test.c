#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
int main()
{
   int i=0;
   for(int i=0,index=0;i<3;i++,(i>0&&i<4)?index++:0)
   {
      printf("%d ",index);
   }
}