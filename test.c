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
    const int maxsize = 4;
    char str1[maxsize]; // 用于存储输入的字符串的字符数组
    char str2[maxsize];
    printf("请输入字符串：");
    fgets(str1, maxsize, stdin); // 从标准输入读取字符串
    fgets_check(str1, sizeof(str1));

    fgets(str2, maxsize, stdin);
    fgets_check(str2, sizeof(str2));
    printf("%s##%s##\n", str1, str2);

    return 0;
}