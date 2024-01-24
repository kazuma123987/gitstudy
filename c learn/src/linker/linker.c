#include <stdio.h>
extern int s1;
extern int _text_start;
extern int _text_end;
extern int _data_load_start;
extern int __data_start__;
extern int _custom_data_start;
extern int _custom_data_end;
extern int _custom_func_start;
extern int _custom_func_end;
//定义段(section)属性
#define CUSTOM_DATA __attribute__((section(".custom_data")))
#define CUSTOM_FUNC __attribute__((section(".custom_func")))
CUSTOM_DATA int array;//把array定义到.custom_data段
CUSTOM_FUNC void linker_swap(int *a,int *b)//把linker_swap函数定义到.custom_func段
{
	int tmp=*a;
	*a=*b;
	*b=tmp;
}
int program()
{
	printf("s1:%x\n"
	"text_start:%x\n"
	"text_end:%x\n"
	"data_load_start:%x\n"
	"data_start:%x\n"
	"custom_data_start:%x\n"
	"custom_data_end:%x\n"
	"custom_func_start:%x\n"
	"custom_end_start:%x\n"
	"array:%x\n"
	"swap:%x\n",&s1,&_text_start,&_text_end,&_data_load_start,&__data_start__,&_custom_data_start,&_custom_data_end,
	&_custom_func_start,&_custom_func_end,&array,&linker_swap);
	return 0;
}