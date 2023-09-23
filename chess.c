#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"
#include "string.h"
void myscanf(int *num,int size)
{
    if(size>0)size++;
    char str[size];
    fgets(str,sizeof(str),stdin);//只读取指定长度的字符串
    if(str[strcspn(str,"\n")]=='\n')str[strcspn(str,"\n")]='\0';//将读取字符串的换行符去掉
    else while(getchar()!='\n');//读取缓冲区剩余字符串
    *num=atoi(str);
}
int find_line(int arrey_len, int arrey[arrey_len][arrey_len], bool x)
{
    int ret = 0;
    char str[2];
    if (x)
        strcpy(str, "O");
    else
        strcpy(str, "X");
    // 行遍历
    for (int i = 0; i < arrey_len; i++)
    {
        int t = x;
        for (int j = 0; j < arrey_len; j++)
        {
            if (arrey[i][j] == 2)
            {
                t = !x;
                break;
            }
            if (x)
                t = (t && arrey[i][j]);
            else
                t = (t || arrey[i][j]);
            if (t != x)
                break;
        }
        if (t == x)
        {
            printf("第%d行的%s连成一线\n", i + 1, str);
            ret = 1;
            goto Ret;
        }
    }
    // 列遍历
    for (int i = 0; i < arrey_len; i++)
    {
        int t = x;
        for (int j = 0; j < arrey_len; j++)
        {
            if (arrey[j][i] == 2)
            {
                t = !x;
                break;
            }
            if (x)
                t = (t && arrey[j][i]);
            else
                t = (t || arrey[j][i]);
            if (t == !x)
                break;
        }
        if (t == x)
        {
            printf("第%d列的%s连成一线\n", i + 1, str);
            ret = 1;
            goto Ret;
        }
    }
    // 左对角线遍历
    for (int i = 0, t = x; i < arrey_len; i++)
    {
        if (arrey[i][arrey_len - 1 - i] == 2)
        {
            t = !x;
            break;
        }
        if (x)
            t = (t && arrey[i][arrey_len - 1 - i]);
        else
            t = (t || arrey[i][arrey_len - 1 - i]);
        if (t == !x)
            break;
        if ((i == arrey_len - 1) && t == x)
        {
            printf("左对角线的%s连成一线\n", str);
            ret = 1;
            goto Ret;
        }
    }
    // 右对角线遍历
    for (int i = 0, t = x; i < arrey_len; i++)
    {
        if (arrey[i][i] == 2)
        {
            t = !x;
            break;
        }
        if (x)
            t = (t && arrey[i][i]);
        else
            t = (t || arrey[i][i]);
        if (t == !x)
            break;
        if (i == arrey_len - 1 && t == x)
        {
            printf("右对角线的%s连成一线\n", str);
            ret = 1;
            goto Ret;
        }
    }
Ret:
    if (ret == 1)
        printf("%s方获胜!\n", str);
    return ret;
}
void print_chess(int N, int arrey[N][N])
{
    printf("棋盘如下图所示：\n");
    printf("--------------------------begin--------------------------\n");
    printf("  ");
    for (int i = 1; i <= N; i++)
        printf("%d ", i);
    printf("\n");
    for (int i = 0; i < N; i++)
    {
        printf("%d ", i + 1);
        for (int j = 0; j < N; j++)
        {
            if (arrey[i][j] == 1)
                printf("O ");
            else if (arrey[i][j] == 0)
                printf("X ");
            else
                printf("- ");
        }
        printf("\n");
    }
    printf("---------------------------end---------------------------\n\n\n");
}
void game()
{
    // 棋盘数组大小定义和初始化
    int N = 1;
    printf("请输入棋盘的行数（或列数）N:(1<N<15)\n");
    while (N <= 1 || N >= 15)
    {
        myscanf(&N,1);
        if (N <= 1 || N >= 15)
            printf("invalid number.\n");
    }
    int arrey[N][N];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            arrey[i][j] = 2;
        }
    }
    // 先手决定
    int chess_order = 2;
    printf("请输入1表示O方为先手,或输入0表示X方为先手:\n");
    while (chess_order != 0 && chess_order != 1)
    {
        myscanf(&chess_order,1);
        if (chess_order != 0 && chess_order != 1)
            printf("无效的输入,请输入0或1\n");
    }
    // 下棋阶段
    int chess_line, chess_row;
    int chess_count = 0;
    print_chess(N, arrey);
    while (chess_count != N * N)
    {
        if (chess_order)
            printf("请输入O方要下在几行几列\n");
        else
            printf("请输入X方要下在几行几列\n");
        myscanf(&chess_line,1);
        myscanf(&chess_row,1);    
        if (chess_line > 0 && chess_line <= N && chess_row > 0 && chess_row <= N)
        {
            if (arrey[chess_line - 1][chess_row - 1] == 2)
            {
                if (chess_order)
                {
                    arrey[chess_line - 1][chess_row - 1] = 1;
                    chess_order = !chess_order;
                    chess_count++;
                }
                else
                {
                    arrey[chess_line - 1][chess_row - 1] = 0;
                    chess_order = !chess_order;
                    chess_count++;
                }
            }
            else
            {
                printf("\n\n此处已存在棋子了!\n\n\n");
                continue;
            }
        }
        else
        {
            printf("\n\nerror number!\n\n\n");
            continue;
        }
        print_chess(N, arrey);
        if (find_line(N, arrey, !chess_order))
            break;
    }
}

int main()
{
    game();
    getchar();
    return 0;
}