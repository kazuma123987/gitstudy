#include <stdio.h>
#include <string.h>
#include <stdint.h>
#define ADRESS_LENTH 100
int main(void)
{
    FILE *fp = NULL;
    char addr_str[ADRESS_LENTH];
    printf("�����������ļ����ڵ�ַ:");
    myscanf_char(addr_str, sizeof(addr_str));
    fp = fopen(addr_str, "r+");
    if (fp)
    {
        printf("�ļ��򿪳ɹ���\n");
        int8_t student_operand;
        while (1)
        {
            printf("��ӭ����ѧ�����ݹ���ϵͳ,������������еĲ���:\n1.д����Ϣ 2.������Ϣ 3.�˳�ϵͳ\n");
            myscanf_int(&student_operand, 1);
            if (student_operand == 1)
            {
                if (student_write(&fp) == 0)
                    printf("�ļ�д��ɹ�!\n");
                else
                    printf("�ļ�д��ʧ�ܣ�\n");
            }
            else if (student_operand == 2)
            {
                if (student_read(&fp) == 0)
                    printf("�ļ���ȡ�ɹ�!\n");
                else
                    printf("�ļ���ȡʧ�ܣ�\n");
            }
            else if (student_operand == 3)
            {
                printf("ϵͳ�˳��ɹ�!\n");
                break;
            }
            else
                printf("�����������Ч,���������룡\n");
        }
        fclose(fp);
    }
    else
        printf("�ļ��򿪴���\n");
    getchar();
    return 0;
}