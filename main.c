#include"stdio.h"
#include"stdlib.h"
#include"math.h"
#include"time.h"
#include"string.h"
int main(void)
{
    int n;
    char str_0[]="初始化";//使用strcmp一定要初始化
    char str_1[]="y";
    char str_2[]="n";
    srand(time(0));
    while(1)
    {
        n=abs(100*sin(rand()));
        printf("Want to guess a number? answer y or n.\n");
        scanf("%s",str_0);
        if (!strcmp(str_0, str_1))
        {
            if(n<50)
                printf("bigger than 50,n=%d\n",n);
            else
                printf("smaller than 50,n=%d\n",n);
            goto jump1;
        }
        else if(!strcmp(str_0, str_2)) goto jump2;
    }
    jump1:
    while(1)
    {
        n=abs(100*sin(rand()));
        printf("Want to guess a number again? answer y or n.\n");
        scanf("%s",str_0);
        if (!strcmp(str_0, str_1))
        {
            if(n<50)
                printf("bigger than 50,n=%d\n",n);
            else
                printf("smaller than 50,n=%d\n",n);
            goto jump1;
        }
        else if(!strcmp(str_0, str_2)) break;
    }
    jump2:
    return 0;
}