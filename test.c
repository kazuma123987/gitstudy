#include <stdio.h>
void fun()
{
    int a[100];
    char str[100];
    printf("sizeof(a)=%d,sizeof(str)=%d",sizeof(a),sizeof(str));   
}
int main()
{
    fun();
    return 0;
}