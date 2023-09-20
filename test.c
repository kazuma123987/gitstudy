#include <stdio.h>
#include <string.h>

void fgets_check(char *str, size_t size)
{
    // 检查是否输入的字符串超过了最大长度
    if (strlen(str) == size - 1 && str[size - 2] != '\n')
    {
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
            // 丢弃剩余的字符
        }
    }
}
int main()
{
    char str2[]="Abcd";//9-13
    char str1[2];//11-12
    printf("%p\n",str1);
    printf("%p\n",str2);
    printf("%s\n",strcpy(str1,str2));//注意定义时先定义str1,或者str1长度大于str2,否则会出现重合
    printf("%s\n",str2);//重合后影响str2的值
    return 0;
}