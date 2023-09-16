#include <stdio.h>
void fun()
{
    int n = 0;
    int count[10];
    for(int i=0;i<10;i++)count[i]=0;
    printf("input a number(0-9),the program will stop when you input '-1'\n");
    scanf("%d", &n);
    while (n != -1)
    {
        if (n > 9 || n < 0)
        {
            printf("input 0-9 or -1!!!\n");
        }
        else count[n]++;
        scanf("%d", &n);
    }
    for(int i=0;i<10;i++)
    {
        printf("输入%d的个数:\t%d\n",i,count[i]);
    }
}
int main()
{
    fun();
    return 0;
}