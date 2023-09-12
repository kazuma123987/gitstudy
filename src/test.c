#include <stdio.h>
#include <math.h>

void printPrime(int num) {
    int count = 1;
    int limit = sqrt(num);
    for (int i = 2; i <= limit; i++) {
        if (num % i == 0) {
            count++;
            break;
        }
    }
    if (count == 1) {
        printf("%d, ", num);
    }
}

#define LIMIT 100

int main() {
    for (int i = 2; i <= LIMIT; i++) {
        printPrime(i);
    }
    printf("是素数\n");
    return 0;
}