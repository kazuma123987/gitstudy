#include <stdio.h>
void fun()
{
    int a=0,b=2,c=2;
    if((a>0) || (b+=1))a++;
    printf("a=%d,b=%d\n",a,b);
    if((a==0) || (b+=1))a++;
    printf("a=%d,c=%d\n",a,c);    
}
int main()
{
    fun();
    return 0;
}