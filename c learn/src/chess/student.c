#include "student.h"
#include "stdio.h"
#include <string.h>
int myscanf_int(int *p, int size)
{
    if (size <= 4 && size > 0)
        size++;
    else
    {
        printf("sizeӦ������(0,4]\n");
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
        printf("sizeӦ����0]\n");
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
        printf("ERROR:�ļ���ʽ����\n");
        return 1;
    }
    int num = 0;
    printf("һ����%d��ѧ��������,\n", ftell(*fp) / sizeof(student));
    printf("��������Ҫ¼���ѧ�����ݸ���\n");
    while (myscanf_int(&num, 1))
        ;
    student std[num];
    for (int i = 0; i < num; i++)
    {
        printf("������ѧ��%d����:\n", i + 1);
        myscanf_char(std[i].name, sizeof(std[i].name));
        printf("������ѧ��%d�Ա�(0->��,1->Ů):\n", i + 1);
        do
        {
            myscanf_int(&std[i].gendar, sizeof(std[i].gendar));
            if (std[i].gendar != 1 && std[i].gendar != 0)
                printf("��Ч������,������0��1:\n");
        } while (std[i].gendar != 1 && std[i].gendar != 0);
        printf("������ѧ��%d����:\n", i + 1);
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
        printf("ERROR:�ļ���ʽ����\n");
        return 1;
    }
    student stu[num];
    fseek(*fp, 0, SEEK_SET);
    fread(stu, sizeof(student), num, *fp);
    int student_operand = 0;
    while (1)
    {
        printf("һ����%d��ѧ��������,��������еĲ���:\n1.����ѧ������ 2.�鿴����ѧ����������� 3.�����ϼ��˵�\n", num);
        myscanf_int(&student_operand, 1);
        if (student_operand == 1)
        {
            while(1)
            {
            printf("��ѡ����ҷ�ʽ:1.�������� 2.��Ų���\n");
            myscanf_int(&student_operand, 1);
            if(student_operand==1||student_operand==2)break;
            else printf("�����������Ч,����������\n");
            }
            if (student_operand == 1)
                ;
            else if (student_operand == 2)
            {
                int watch_num = 0;
                printf("������ѧ�����\n");
                myscanf_int(&watch_num, sizeof(watch_num));
                watch_num--;
                printf("ѧ��������%s\n", stu[watch_num].name);
                if (stu[watch_num].gendar)
                    printf("ѧ���Ա�Ů\n");
                else
                    printf("ѧ���Ա���\n");
                printf("ѧ�����䣺%d\n", stu[watch_num].age);
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