#include <stdio.h>
void printnum()
{
    int a,i,j,k;
    printf("请输入a(a为不大于6的正整数)的值：\n");
    scanf("%d", &a);
    for(i=a;i<a+4;i++)
    {
    printf("\n");
    for(j=a;j<a+4;j++)
    for(k=a;k<a+4;k++)
    if(i!=j&&j!=k&&k!=i)printf("%d,",i*100+j*10+k);
    }
}
int main()
{
    printnum();
    return 0;
}