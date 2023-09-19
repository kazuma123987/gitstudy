#include "stdio.h"
int main(void)
{
    int a[2]={1,2};
    int *p=&a[0];
    char *q=(char *)p;
    printf("%d\n",*q);
    printf("%d\n",*(q+1));
    printf("%d\n",*(q+2));
    printf("%d\n",*(q+3));
    printf("%d\n",*(q+4));
}