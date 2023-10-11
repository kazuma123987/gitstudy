#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <stdint.h>  //uint16_t,int8_t...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
#ifdef _WIN64//visual studio的x64编译器会定义宏定义_WIN64,x86则是_WIN32
#define myint uint64_t
#else
#define myint uint32_t
#endif
#define NAME_SIZE 20
//栈结构
typedef struct
{
    int stack_cap;                // 栈容量
    int ele_num;                  // 目前栈的元素个数
    void* stack_top;              // 栈顶，在地址最低位
    void* p;                      // 栈指针，指向下一个要出栈的元素的地址，地址比栈顶大
    void (*destroy_func)(void*); // 回调函数，用于调用解析函数
} stack;
//简单结构体示例
typedef struct
{
    char* name;
    int age;
}student;
//初始化栈
stack* stack_init(void (*destroy_func)(void*))
{
    stack* s = malloc(sizeof(stack));
    s->ele_num = 0;
    s->stack_cap = 2;
    s->stack_top = malloc(sizeof(myint*) * s->stack_cap);       // 分配栈容量个指针，并使指向栈空间最顶部
    s->p = (myint*)s->stack_top + s->stack_cap;             // 栈指针指向栈底
    s->destroy_func = destroy_func;                            // 传入解析函数
    return s;
}
//栈的清除
void stack_des(stack* s)
{
    int size = s->ele_num;
    for (int i = 0; i < size; i++)
    {
        s->destroy_func((void*)(*(myint*)s->p));
        s->p = (myint*)s->p + 1;
    }
    free(s->stack_top);
    free(s);
}
//进栈
void stack_push(stack* s, void* p)
{
    if (s->ele_num == s->stack_cap)
    {
        s->stack_cap *= 2;
        //！！！notice：--这里realloc之后s->stack_top到（s->stack_top+s->elenum）的空间存放了数据，而数据应该
        //在（s->stack_top+s->elenum）到（s->stack_top+s->stack_cap）的空间内，所以之后要拷贝数据，这里分清栈底在何处
        s->stack_top = (myint*)realloc(s->stack_top, sizeof(myint*) * s->stack_cap);
        memcpy((myint*)s->stack_top + s->ele_num, s->stack_top, sizeof(void*) * s->ele_num);
        s->p = (myint*)s->stack_top + s->ele_num;
    }
    s->p = (myint*)s->p - 1;//注意这里栈底是栈分配的最高地址，最高地址不能再存放任何指针，所以先移动再赋值
    *((myint*)s->p) = (myint)p;//不改变指针p的值，不用加*    
    s->ele_num++;
}
//出栈
void stack_pop(stack* s, void* p)
{
    if (s->ele_num == 0)
    {
        printf("栈已空");
        *(myint*)p = NULL;
        return;
    }
    *(myint*)p = *(myint*)s->p;//改变指针p的值，p要加*，此时*p内容是地址
    s->p = (myint*)s->p + 1;//注意入栈是先移动指针再赋值，所以指针最后指向不为空，应先赋值再移动指针
    s->ele_num--;
}
//结构体的析构
void stu_des(student* stu)
{
    free(stu->name);
    free(stu);
}
//一般指针的free
void normal_des(void* p)
{
    free(p);
}
//函数进栈测试函数
void* my_print1()
{
    printf("this is my_print1\n");
}
void* my_print2()
{
    printf("this is my_print2\n");
}
void* my_print3()
{
    printf("this is my_print3\n");
}
//scanf的安全替换
void myscanf(int* num)
{
    char input[10];
    fgets(input, sizeof(input), stdin);
    if (input[strcspn(input, "\n")] == '\n')input[strcspn(input, "\n")] = '\0';
    else while (getchar() != '\n');
    *num = atoi(input);
}
int main()
{
    //整数进栈
    stack* s_int = stack_init(normal_des);
    for (int i = 0; i < 10; i++)
    {
        int* val = malloc(sizeof(int));
        *val = i + 1;
        stack_push(s_int, val);
    }
    for (int i = 0; i < 8; i++)
    {
        int* val;
        stack_pop(s_int, &val);
        printf("%d ", *val);
        free(val);
    }
    printf("\n");
    stack_des(s_int);
    //结构体进栈
    stack* s_struct = stack_init((void*)stu_des);
    for (int i = 0; i < 3; i++)
    {
        student* stu = malloc(sizeof(student));
        printf("input student%d's name:\n", i + 1);
        stu->name = malloc(sizeof(char) * NAME_SIZE);
        fgets(stu->name, NAME_SIZE, stdin);
        if (stu->name[strcspn(stu->name, "\n")] == '\n')stu->name[strcspn(stu->name, "\n")] = '\0';
        else while (getchar() != '\n');
        stu->name = realloc(stu->name, strlen(stu->name) + 1);
        printf("input student%d's age:\n", i + 1);
        myscanf(&stu->age);
        stack_push(s_struct, stu);
    }
    for (int i = 0; i < 3; i++)
    {
        student* st;
        stack_pop(s_struct, &st);
        printf("name:%s,age:%d", st->name, st->age);
        printf("\n");
        stu_des(st);
    }
    stack_des(s_struct);
    //函数进栈
    stack* s = stack_init(normal_des);
    stack_push(s, my_print1);
    stack_push(s, my_print2);
    stack_push(s, my_print3);
    for (int i = 1; i < 10; i++)
    {
        void (*p)();
        stack_pop(s, &p);
        if (p)p();
    }
    stack_des(s);
}