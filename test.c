#include <stdio.h>
void fun()
{
    int a=0,b=2,c=2;
    if((a>0) || (b+=1))a++;
    printf("a=%d,b=%d\n",a,b);
    if((a==0) || (b+=1))a++;
    printf("a=%d,c=%d\n",a,c); 
    //说明在写代码时避免把复合赋值写在逻辑运算中   
}
int main()
{
    fun();
    return 0;
}