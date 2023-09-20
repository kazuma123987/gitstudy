#include <stdio.h>
#define f(a,b) a+b
int main()
{
   int a=4,b=6,c=4;
   c=f(a,b)/f(a*b,b);//注意展开后为a+b/a*b+b=4+6/4*6+6=16
   printf("%d",c);
}