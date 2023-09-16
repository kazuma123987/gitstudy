#include <stdio.h>

void findNumber(int number, int array[], int size)
{
    int count=0;
    int pos[size];
    for(int i=0;i<size;i++)
    {
        if(array[i]==number)
        {
            pos[count]=i;
            count++;
        }
    }
    if(count==0)printf("数字不存在于此数组！");
    else
    {
        printf("数字%d在数组的第",number);
        for(int i=0;i<count;i++)
        {
            printf("%d",pos[i]+1);
            if(i<count-1)printf(", ");
        }
        printf("个位置处\n");
    }
}

int main()
{
    int array[] = {13, 13, 445, 66, 7, 7, 5, 3, 1, 9, 76, 13, 144, 245, 4, 7};
    int size = sizeof(array) / sizeof(array[0]);
    int number;
    printf("请输入一个数字: ");
    scanf("%d", &number);
    findNumber(number, array, size); 
    return 0;
}