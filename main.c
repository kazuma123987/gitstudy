#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"time.h"
#include"string.h"
int main(void)
{
    int n;
    srand(time(0));//初始化随机种子
    n=abs(100*sin(rand()));
    if(n<50)
        printf("bigger than 50,n=%d\n",n);
    else
        printf("smaller than 50,n=%d\n",n);
    return 0;
}