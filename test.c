#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
typedef struct _tree
{
    int value;
    int height;
    struct _tree *left;
    struct _tree *right;
} Tree;
int main()
{
    int len=3;//数组长度
    int *arr = malloc(sizeof(int) * len);//创建数组arr[3]
    for(int i=0;i<len;i++)arr[i]=i+1;
    int len_new=len+3;//扩容后的数组长度
    arr = realloc(arr, sizeof(int) * len_new);//扩容arr[3]到arr[6],数组内容不变
    for(int i=len;i<len_new;i++)arr[i]=i+1;
    for(int i=0;i<len_new;i++)//打印数组内容
        printf("%d ", arr[i]);
    free(arr);
}