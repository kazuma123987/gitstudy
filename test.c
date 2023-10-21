#include <stdio.h>
#include <wchar.h>//wchar_t,wprintf,L
#include <locale.h>//setlocale()
#include <unistd.h>//usleep()
#define MAX_NUM (100)
//wchar_t是宽字符类型，其长度根据编译器不同而在unsigned int和unsigned short之间切换,赋值方式要在字符前加上L,
//如wchar_t wch=L'国'，这里以 L'▁', L'▃', L'▄', L'▅', L'▆'，L'█'实现进度条为例讲解wchar_t的使用方法
int main() 
{
    setlocale(LC_ALL,"");//必须设置LC_ALL为本地环境！！！(环境变量等以本机为准)
    wchar_t buffer[MAX_NUM+1]={0};//长度为101,最后一个字节为'\0'，这样就能存100个字符,并且进行了初始化
    wchar_t pattern[]={L'▁', L'▃', L'▄', L'▅', L'▆'};//定义宽字符数组并赋值,以呈现充电效果
    for(int i=0;i<MAX_NUM;i++)
    {
        buffer[i]=L'█';
        wprintf(L"\r[%-*s][%d%%][%c]",MAX_NUM,buffer,i+1,pattern[i%5]);//wchar_t的输出函数,需要将字符串转换为wchar_t类型要在前面加L
        //另外%-*s左对齐输出100个字符,不够的会占位，%%是输出%的方式
        fflush(stdout);
        usleep(100000);
    }
    return 0;
}