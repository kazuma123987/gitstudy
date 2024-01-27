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
extern int _custom_start;
extern int _custom_end;
extern int __bss_start__;
extern int __bss_end__;
// 定义段(section)属性
#define _AT(addr) __attribute__((at(addr)))
#define CUSTOM_OTHER_DATA __attribute__((section(".custom_data")))
#define CUSTOM_OTHER_FUNC __attribute__((section(".custom_func")))
#define CUSTOM_DATA __attribute__((section(".custom.data")))
#define CUSTOM_FUNC __attribute__((section(".custom.func")))
#define CUSTOM_API __attribute__((__stdcall__))
#define PACKED __attribute__((__packed__))
#define ALIGNED __attribute__((aligned))
#define ALIGN(x) __attribute__((aligned(x))) // x的有效参数为2的n次幂,即1,2,4,8;该属性会与系统默认对其字节进行比较,并取较大者
// 64位系统默认为8字节对齐,32位为4字节对齐,64位系统下,n<8时,取8,n>8时,取n
CUSTOM_OTHER_DATA int c[5];
CUSTOM_DATA int array;									// 把array定义到.custom_data段
CUSTOM_FUNC CUSTOM_API void linker_swap(int *a, int *b) // 把linker_swap函数定义到.custom_func段
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
// 位域存储规则:若相邻元素类型相同且未超过类型大小(int是4字节),则紧凑排列,这里abc紧凑排序,d单独排序,共占用4+1=5个字节(packed属性)
typedef struct PACKED Node
{
	int a : 1;
	int b : 1;
	int c : 1;
	char d : 1;
} Node;
typedef struct PACKED xNode
{
	char a : 1;
	char b : 1;
	unsigned char c : 1; // 只要占用字节数相同,都可以定义
	unsigned char : 4;	 // 未定义,占4个位,这里一定要定义为占一个字节的类型,否则占用字节数会变成1+4+1=6个
	char d : 1;
} xNode;

int global_init_zero = 0;
int global_no_init;
int program()
{
	int static_no_init;
	int static_init_zero = 0;
	printf("s1:%x\n"
		   "text_start:%x\n"
		   "text_end:%x\n"
		   "data_load_start:%x\n"
		   "data_start:%x\n"
		   "custom_data_start:%x\n"
		   "custom_data_end:%x\n"
		   "custom_func_start:%x\n"
		   "custom_end_start:%x\n"
		   "custom_start:%x\n"
		   "custom_end:%x\n"
		   "bss_start:%x\n"
		   "bss_end:%x\n"
		   "array:%x\n"
		   "swap:%x\n"
		   "c:%x\n"
		   "sizeof(Node):%ld\n"
		   "sizeof(xNode):%ld\n"
		   "global_no_init:%x\n"
		   "global_init_zero:%x\n"
		   "static_no_init:%x\n"
		   "static_init_zero:%x\n",
		   &s1, &_text_start, &_text_end, &_data_load_start, &__data_start__, &_custom_data_start, &_custom_data_end,
		   &_custom_func_start, &_custom_func_end, &_custom_start, &_custom_end, &__bss_start__, &__bss_end__,
		   &array, &linker_swap, &c, sizeof(Node), sizeof(xNode), &global_no_init, &global_init_zero, &static_no_init, &static_init_zero);
	int a = 2, b = 4;
	linker_swap(&a, &b);
	printf("a=%d,b=%d\n", a, b);
	return 0;
}