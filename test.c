#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main(void) {
    //一般在C99之前定义数组时不能写为int array[N],数组括号内只能是常数，此时只能通过int *arrey=(int *)malloc(N*sizeof(int))来定义数组
    size_t numBytes = 10;  // 分配的字节数
    int* array = (int*)malloc(numBytes);
    void *p=malloc(1024*1024);//这里malloc(1)表示申请1Byte的数据给p存储，1024*1024则是1MByte的数据，p可以表示大小为1024*1024/sizeof(p)的数组
    if (array == NULL) {
        printf("内存分配失败\n");
        return 1;
    }
    // 释放内存
    free(array);
    free(p);
    //字符数组与字符串
    char str[]="abc!";            //字符串的最简定义方式
    char str1[]={'a','b','c','!'};//数组最后一个元素不是0或者'\0',这个是字符数组，不能做字符串的运算
    char str2[]={'a','b','c','!',0};//数组最后一个元素是0或者'\0',这个是字符串
    printf("strlen(str)=%d\n",strlen(str));
    printf("strlen(str1)=%d\n",strlen(str1));
    printf("sizeof(str)=%d,sizeof(str1)=%d,sizeof(str2)=%d,\n",sizeof(str),sizeof(str1),sizeof(str2));
    return 0;
}