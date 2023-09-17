#include "stdio.h"
#include "windows.h"
#include "stdbool.h"
#include "string.h"
void find_line(int arrey_len,int arrey[arrey_len][arrey_len],bool x)
{
    char str[10];
    if(x)strcpy(str,"O");
    else strcpy(str,"X");
  // 行遍历
    for (int i = 0; i < arrey_len; i++)
    {
        int t = x;
        for (int j = 0; j < arrey_len; j++)
        {
            if(x)t = (t && arrey[i][j]);
            else t = (t || arrey[i][j]);
            if (t == !x)
                break;
        }
        if (t == x)
            printf("第%d行的%s连成一线\n",i+1,str);
    }
    // 列遍历
    for (int i = 0; i < arrey_len; i++)
    {
        int t = x;
        for (int j = 0; j < arrey_len; j++)
        {
            if(x)t = (t && arrey[j][i]);
            else t = (t || arrey[j][i]);
            if (t == !x)
                break;
        }
        if (t == x)
            printf("第%d列的%s连成一线\n",i+1,str);
    }
    //左对角线遍历
    for(int i=0,t=x;i<arrey_len;i++)
    {
        if(x)t=(t&&arrey[i][arrey_len-1-i]);
        else t=(t||arrey[i][arrey_len-1-i]);
        if(t==!x)break;
        if((i==arrey_len-1)&&t==x)printf("左对角线的%s连成一线\n",str);
    }
    //右对角线遍历
    for(int i=0,t=x;i<arrey_len;i++)
    {
        if(x)t=(t&&arrey[i][i]);
        else t=(t||arrey[i][i]);
        if(t==!x)break;
        if(i==arrey_len-1&&t==x)printf("右对角线的%s连成一线\n",str);
    }   
}
void game()
{
    int N = 1;
    printf("请输入棋盘的行数（或列数）N:(1<N<15)\n");
    while (N <= 1 || N >= 15)
    {
        scanf("%d", &N);
        if (N <= 1 || N >= 15)
            printf("invalid number.\n");
    }
    int arrey[N][N];
    printf("输入%d个数字(1或0)为数组赋值(输入-1退出函数)：\n输入1表示O,输入0表示X\n", N * N);
    int i = 0;
    while (i != N)
    {
        int j = 0;
        while (j != N)
        {
            scanf("%d", &arrey[i][j]);
            if (arrey[i][j] == 1 || arrey[i][j] == 0)
            {
                j++;
            }
            else if(arrey[i][j]==-1)
            {
                printf("Exit successfully!\n");
                return;
            }
            else
                printf("input 1 or 0 !\n");
        }
        i++;
    }
    {
        printf("棋盘如下图所示：\n");
        printf("--------------------------begin--------------------------\n");
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (arrey[i][j] == 1)
                    printf("O ");
                else
                    printf("X ");
            }
            printf("\n");
        }
        printf("---------------------------end---------------------------\n");
    }
    find_line(N,arrey,true);
    printf("---------------------------分割线---------------------------\n");
    find_line(N,arrey,false);
}

int main()
{
    game();
    system("pause");
    return 0;
}