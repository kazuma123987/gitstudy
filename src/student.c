#include "student.h"
#include "stdio.h"
#include <string.h>
int myscanf_int(int *p, int size)
{
    if (size <= 4 && size > 0)
        size++;
    else
    {
        printf("size应在区间(0,4]\n");
        return 1;
    }
    char str[size];
    fgets(str, sizeof(str), stdin);
    char c = str[strcspn(str, "\n")];
    if (c == '\n')
        str[strcspn(str, "\n")] = '\0';
    else
        while (getchar() != '\n')
            ;
    *p = atoi(str);
    return 0;
}
int myscanf_char(char str[], int size)
{
    int ret = -1;
    if (size > 0)
        size++;
    else
    {
        printf("size应大于0]\n");
        return 1;
    }
    fgets(str, size, stdin);
    char c = str[strcspn(str, "\n")];
    if (c == '\n')
        str[strcspn(str, "\n")] = '\0';
    else
        while (getchar() != '\n')
            ;
    ret = 0;
    return ret;
}
int student_write(FILE **fp)
{
    int ret = -1;
    fseek(*fp, 0, SEEK_END);
    if (ftell(*fp) % sizeof(student) != 0)
    {
        printf("ERROR:文件格式错误\n");
        return 1;
    }
    int num = 0;
    printf("一共有%d名学生的数据,\n", ftell(*fp) / sizeof(student));
    printf("请输入想要录入的学生数据个数\n");
    while (myscanf_int(&num, 1))
        ;
    student std[num];
    for (int i = 0; i < num; i++)
    {
        printf("请输入学生%d姓名:\n", i + 1);
        myscanf_char(std[i].name, sizeof(std[i].name));
        printf("请输入学生%d性别(0->男,1->女):\n", i + 1);
        do
        {
            myscanf_int(&std[i].gendar, sizeof(std[i].gendar));
            if (std[i].gendar != 1 && std[i].gendar != 0)
                printf("无效的输入,请输入0或1:\n");
        } while (std[i].gendar != 1 && std[i].gendar != 0);
        printf("请输入学生%d年龄:\n", i + 1);
        myscanf_int(&std[i].age, 3);
    }
    if (fwrite(std, sizeof(student), num, *fp) == num)
        ret = 0;
RET:
    return ret;
}
int student_read(FILE **fp)
{
    fseek(*fp, 0, SEEK_END);
    int num = ftell(*fp) / sizeof(student);
    if (ftell(*fp) % sizeof(student) != 0)
    {
        printf("ERROR:文件格式错误\n");
        return 1;
    }
    student stu[num];
    fseek(*fp, 0, SEEK_SET);
    fread(stu, sizeof(student), num, *fp);
    int student_operand = 0;
    while (1)
    {
        printf("一共有%d名学生的数据,请输入进行的操作:\n1.查找学生数据 2.查看所有学生姓名与序号 3.返回上级菜单\n", num);
        myscanf_int(&student_operand, 1);
        if (student_operand == 1)
        {
            while(1)
            {
            printf("请选择查找方式:1.姓名查找 2.序号查找\n");
            myscanf_int(&student_operand, 1);
            if(student_operand==1||student_operand==2)break;
            else printf("输入的数字无效,请重新输入\n");
            }
            if (student_operand == 1)
                ;
            else if (student_operand == 2)
            {
                int watch_num = 0;
                printf("请输入学生序号\n");
                myscanf_int(&watch_num, sizeof(watch_num));
                watch_num--;
                printf("学生姓名：%s\n", stu[watch_num].name);
                if (stu[watch_num].gendar)
                    printf("学生性别：女\n");
                else
                    printf("学生性别：男\n");
                printf("学生年龄：%d\n", stu[watch_num].age);
            }
        break;
        }
        else if(student_operand==2)
        {
            for(int i=0;i<num;i++)
                printf("%-4d:%s\n", i+1, stu[i].name);
        }
        else if(student_operand==3)break;
    }
    return 0;
}