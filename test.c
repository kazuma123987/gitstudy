#include <stdio.h>
#include <math.h>

void pn_func()
{
    int m,n,sum=0,count=0;
    printf("输入m与n的值：");
    scanf("%d %d",&m,&n);
    for(int i=m;i<=n;i++)
    {
        int num=0;
        for(int j=2;j<=sqrt(i);j++)//平方根优化循环次数
        {
            if(i%j==0)num++;
        }
        if(num==0)
        {
            sum+=i;
            count++;
        }
    }
    printf("%d到%d的素数个数为：%d,其和为：%d",m,n,count,sum);
}

int main()
{
    pn_func();
    return 0;
}