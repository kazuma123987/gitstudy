/*！！！！！！！！！！！！！注意！！！！！！！！！！！！！！！！
一个文本文件实质上是相连的，行与行之间以\n连接,\n占据两个字符位置，
所以当使用fseek移动到某一行的开头，再使用fputs修改该行时，如果输入
的字符串太长还会影响到后面几行，fputs输出的字符串会取代\n的位置
*/
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
void move_fp(FILE **flie_fp,int target_line);
int main()
{
   FILE *fp1 = NULL;
   FILE *fp2=NULL;
   fp1 = fopen("./test1.txt", "r+");
   fp2 = fopen("./test2.txt", "r");
   char str1[100], str2[100], str3[100], str4[100],str[8000];
   if (fp1)
   {
      fscanf(fp1, "\"%[^\"]\",%[^,],,%[^,],%[^\n]", str1, str2, str3, str4);//注意双引号要加转义字符
      move_fp(&fp1,2);
      //fseek(fp1,0,SEEK_CUR);//必须通过这种方式才能让文件指针在开头或结尾以外的位置
      printf("%ld\n",ftell(fp1));
      /*char c;
      while((c=fgetc(fp1))!=EOF)if(c=='\n')break;
      printf("%ld\n",ftell(fp1));*/
      fputs("第二行\n",fp1);
      fclose(fp1);
   }
   else
      printf("can't open the file\n");
     if (fp2)
   {
      fscanf(fp2, "%*[^\n]\n%[^-]%*[^\n]", str);
      fclose(fp2);
   }
   else
      printf("can't open the file\n");
   printf("str1:%s\n", str1);
   printf("str2:%s\n", str2);
   printf("str3:%s\n", str3);
   printf("str4:%s\n", str4);
   printf("str:\n%s\n", str);
}
void move_fp(FILE **file_fp,int target_line)
{
   int current_line=1;//设置当前行
   while(current_line<target_line)
   {
      int c=fgetc(*file_fp);
      if(c=='\n')current_line++;
      else if(c==EOF)break;
   }
   fseek(*file_fp,0,SEEK_CUR);
   if(current_line==target_line)printf("文件指针已移动到第%d行开头\n",target_line);
   else printf("不存在目标行!\n");
}