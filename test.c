#include <stdio.h>
void printGCD()
{
    int a, b, t;
    printf("请输入a和b的值：\n");
    scanf("%d %d", &a, &b);
    while (b != 0)
    {
        t = a % b;
        a = b;
        b = t;
    }
    printf("a和b的最大公约数是:%d\n", a);
}
int main()
{
    printGCD();
    return 0;
}