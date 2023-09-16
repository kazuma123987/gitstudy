#include <stdio.h>
void fun()
{
    //光标回退\b
    printf("光标回退:\n");
    printf("123\b\n");
    printf("123\b456\n");
    printf("%d",sizeof("123\b456"));//注意在sizeof里面一切运算无效，包括a++，\n换行等
    printf("\n");
    //光标到下一个表格位\t
    printf("光标到下一个表格位:\n");
    printf("1234\t56\n");
    printf("123\t45\n");
    //光标到当前行最开始处\r
    printf("光标到当前行最开始处:\n");
    printf("1234\r56\n");
    printf("1234\r\n");
}
int main()
{
    fun();
    return 0;
}