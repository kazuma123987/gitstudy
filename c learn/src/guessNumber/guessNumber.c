#include <stdio.h>
#include <string.h>
#include <stdint.h>
void guessNumber()
{
    srand(time(0)); // time函数是返回一个值，即格林尼治时间1970年1月1日00:00:00到当前时刻的时长，时长单位是秒
    int MAX_INPUT_SIZE=100;
    while (1)
    {
        int n = abs(100 * sin(rand()));
        printf("Want to guess a number? Answer y or n.\n");
        char str_0[MAX_INPUT_SIZE];
        fgets(str_0, MAX_INPUT_SIZE, stdin);

        // remove newline at end, if it exists
        char *newline = strchr(str_0, '\n');
        if (newline)
            *newline = 0;

        if (strcmp(str_0, "y") == 0)
        {
            if (n < 50)
                printf("Bigger than 50, n=%d\n", n);
            else
                printf("Smaller than 50, n=%d\n", n);
        }
        else if (strcmp(str_0, "n") == 0)
        {
            break;
        }
        else
        {
            printf("Error, just input y or n!\n");
        }
    }
}
int main()
{
    guessNumber();
    return 0;
}