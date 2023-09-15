#include <stdio.h>

void frac_sum()
{
    int N,t=0,num1=2,num2=1;
    double sum=0;
    printf("输入N的值：");
    scanf("%d",&N);
    for(int i=1;i<=N;i++)
    {
        sum+=num1*1.0/num2;
        t=num2;
        num2=num1;
        num1+=t;
    }
    printf("2/1+3/2+5/3+8/5...的前%d项和为：%.2lf\n",N,sum);
}

int main()
{
    frac_sum();
    return 0;
}