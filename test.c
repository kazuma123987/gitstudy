#include <stdio.h>

int isPrime(int number, int prime[], int count)
{
    int ret = 1;
    for (int i = 0; i < count; i++)
    {
        if (number % prime[i] == 0)
        {
            ret = 0;
            break;
        }
    }
    return ret;
}

int main()
{
    const int maxsize = 100;
    int prime[maxsize];
    prime[0]=2;
    int count = 1, i = 3;
    while (count != maxsize)
    {
        if (isPrime(i, prime, count))
        {
            prime[count++] = i;
        }
        i++;
    }
    printf("连续的%d个素数:\n",maxsize);
    for(int i=0;i<maxsize;i++)
    {
    printf("%d",prime[i]);
    if(i<maxsize-1)printf(", ");
    }
    return 0;
}