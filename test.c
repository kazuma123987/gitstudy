#include <stdio.h>
#include <math.h>

void printnum()
{
    int N, i, j, t, num, num1, sum;
    printf("请输入水仙花数的位数(3到7之间)：\n");
    scanf("%d", &N);
    num = pow(10, N - 1);
    int power_of_digits[10];
    for (i = 0; i < 10; i++)
    {
        power_of_digits[i] = pow(i, N);
    }

    for (i = num; i < num * 10; i++)
    {
        sum = 0;
        t = i;
        num1 = num;
        for (j = 1; j <= N; j++)
        {
            sum += power_of_digits[t / num1];
            t %= num1;
            num1 /= 10;
        }
        if (sum == i)
            printf("%d\n", sum);
    }
}

int main()
{
    printnum();
    return 0;
}