#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
void write(FILE *fp,int num);
int myscanf(void *p,int size,int mode);//size代表输入数字的字节数,mode为1是bool类型输入,mode为2是整数类型输入,mode为3是字符串输入
int main(void) {
    FILE *fp=NULL;
    fp=fopen("./student.data","r+");
    if(fp)
    {
        int student_num=0;
        printf("请输入想要录入的学生数据个数\n");
        while(myscanf(&student_num,1,2));
        write(fp,student_num);
        fclose(fp);
    }
    else printf("文件打开错误！\n");
    return 0;
}
void write(FILE *fp,int num)
{
    student std[num];
    for(int i=0;i<num;i++)
    {
        printf("请输入学生姓名:\n");
        
        printf("请输入学生性别(0->男,1->女):\n");
        
        printf("请输入学生年龄:\n");
        myscanf(&std[i].age,1);
    }
}
int myscanf(void *p,int size,int mode)
{
    if(size<=4&&size>0)size++;
    else
    {
        printf("size应在区间(0,4]\n");
        return 1;
    }
    char str[size];
    fgets(str,sizeof(str),stdin);
    while(getchar()!='\n');
    str[strcspn(str,"\n")]='\0';
    *p=atoi(str);
    return 0;
}