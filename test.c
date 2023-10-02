#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
//memset(*ptr,int c,size_t size);从指针ptr指向的（值）所存放的内存空间开始,以（字节）为单位，将连续size个字节赋值为c
int main() {
    int *p[5];//创建指针数组(*p)[5]
    int *arr=malloc(sizeof(int)*10);//创建整数数组arr[10]
    char str[]="hello world",c=49;//创建字符数组str[sizeof("hello world")]
    char *str1="hello world";
    
    memset(p, 0, sizeof(int*) * 5);//从p所指的第一个元素(int *)p[0]开始,将连续5*sizeof(int*)个字节的值设置为0，最终所有指针被设置为0
    memset(arr,1,sizeof(int)*10);//从arr所指的第一个元素(int)arr[0]开始,将连续5*sizeof(int)个字节的值设置为1，如下图:
    //比如arr[0]        arr[1]       arr[2]       arr[3] ...   arr[9]
    //  0x01010101   0x01010101    0x01010101   0x01010101    0x01010101 (十六进制按int大小排序)
    //  01 01 01 01  01 01 01 01  01 01 01 01  01 01 01 01    01 01 01 01(十六进制按字节排序)
    //  16843009       16843009     16843009     16843009     16843009   (十进制按int大小排序)
    memset(str,c,strlen(str));//从str所指的值(str[0]='h')开始,以字节为单位,将连续strlen个字节的值设置为49(字符'1')
    /*----------------------------------error----------------------------------*/
    memset(str1,c,strlen(str1));//因为str1指向的是常量字符串的直接地址，程序运行后不允许写入，所以会发送写入异常
    /*----------------------------------error----------------------------------*/
    
    for (int i = 0; i < 5; i++)printf("p[%d]=%p\n",i, p[i]);//打印p指针数组的元素,因为是指针，所以有8个字节，16位16进制表示
    for (int i = 0; i < 10; i++)printf("%d ",arr[i]);//打印arr整数数组的元素
    printf("\n%s",str);
    return 0;
}