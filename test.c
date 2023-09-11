#include <stdio.h>

void printDigits(long long int num) {
    if (num < 10) {
        printf("%d ", num);
        return;
    }

    printDigits(num / 10);
    printf("%d ", num % 10);
}

int main() {
    long long int num;
    printf("请输入一个数字: ");
    scanf("%lld", &num);

    printf("分解后的数字为: ");
    printDigits(num);
    printf("\n");

    return 0;
}