#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"time.h"
int main(void)
{
    int n;
    n=abs(100*sin(rand()));
    if(n<50)
        printf("bigger than 50,n=%d\n",n);
    else
        printf("smaller than 50,n=%d\n",n);
    system("pause");
    return 0;
}