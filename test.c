#include <stdio.h>
#include <string.h>
typedef struct
{
    double hour;//偏移量0
    double minute;//0+8且为8的倍数：8
    char str[64];//8+8且为1的倍数：16
    double second;//16+64且为8的倍数：80
}time;//80+8且为最大类型double的大小8的倍数：88

typedef struct
{
    char day;//偏移量0,占用字节1
    int month;//4，占用字节4
    double year;//8，占用字节8
    time p;//16，占用字节88
    float i;//104，占用字节4
    char str[16];//108，占用字节16+4，4为补充的字节
}date;//108+16=124,结构体最大字节sizeof(double)=8,8的倍数最接近124的为128
int main()
{
    date d;
    time t;
    printf("%p\n",d);//首地址为最大类型的倍数
    printf("%p\n",t);//首地址为最大类型的倍数,发现t和d首地址相同
    printf("sizeof(time)=%d,sizeof(date)=%d\n",sizeof(time),sizeof(date));
}