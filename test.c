#include <stdio.h>
#include <math.h>

void printform()
{
    for(int i=1;i<=9;i++)
    {
        for(int j=1;j<=i;j++)printf("%d*%d=%-4d",j,i,i*j);//%-4d是左对齐，%4d是右对齐，一共4个空位
        printf("\n");
    }
}

int main()
{
    printform();
    return 0;
}