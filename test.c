#include <stdio.h>
void num()
{
    char a=127;//char可表示整数，其范围为-128~127
    unsigned char b=127;//unsigned char范围为0~255
    a++;
    b++;
    printf("a=%d,b=%d\n", a,b);//对于char类型，127+1=-128（越界），-128-1=127
}

int main()
{
    num();
    return 0;
}