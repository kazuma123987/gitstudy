#include"stdio.h"
#include"stdlib.h"
#include"math.h"
int main(void)
{
    double n;
    n=abs(100*sin(rand()));
    if(n<50)
        printf("bigger than 50,n=%d\n",&n);
    else
        printf("smaller than 50,n=%d\n");
    system("pause");
    return 0;
}