#include <stdio.h>

void print_pinyin(int n)
{
    static const char *pinyin[] = {"ling", "yi", "er", "san", "si", "wu", "liu", "qi", "ba", "jiu"};

    if (n >= 10)
    {
        print_pinyin(n / 10);
        printf(" ");
    }

    printf("%s", pinyin[n % 10]);
}

void num_pinyin(int n)
{
    if (n == 0)
    {
        printf("ling");
        return;
    }

    if (n < 0)
    {
        printf("fu ");
        n = -n;
    }

    print_pinyin(n);
}

int main()
{
    int n;
    printf("请输入一个数字：\n");
    scanf("%d", &n);
    num_pinyin(n);
    return 0;
}