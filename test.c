#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
// 定义向量
typedef struct
{
    int size;    // 当前数组的元素个数
    int cap;     // 向量的容量
    int depth;   // 向量的维度，维度为1时data是一维指针数组(element type*)data[cap]，维度为2为二维指针数组（vector *）data[cap]
    void **data; // 指针数组
} vector;
// 数组二叉树的封装
typedef struct
{
    vector *tree;
} Tree;
/*----------------向量基本操作----------------*/
// 创建向量
vector *create_vector()
{
    vector *v = malloc(sizeof(vector));
    v->cap = 4;
    v->size = 0;
    v->depth = 1;
    v->data = malloc(sizeof(void *) * v->cap);
    memset(v->data, 0, sizeof(void *) * v->cap);
    return v;
}
// 清除向量空间
void free_vector(vector *v)
{
    if (v)
    {
        if (v->depth == 0)
            return;
        if (v->depth == 1)
        {
            for (int i = 0; i < v->cap; i++)
                free(v->data[i]);//free掉v->data[v->cap]里的所有指针
            free(v->data);//！！！free掉v->data这个指针数组(指针数组要free掉装载的元素和自身)
            free(v);//free掉v这个向量
        }
        else
        {
            for (int i = 0; i < v->cap; i++)
                free_vector(v->data[i]);
            free(v->data);
            free(v);
        }
    }
}
// 向量尾部添加新值
void addItem_vector(vector *v, void *element, int element_size)
{
    if (v->size == v->cap)
    {
        v->cap *= 2;
        v->data = realloc(v->data, sizeof(void *) * v->cap);
        memset(v->data+v->size,0,sizeof(void*)*(v->cap-v->size));
    }
    void *tmp = malloc(element_size);
    memcpy(tmp, element, element_size);
    v->data[v->size++] = tmp;
}
// 向量尾部删除元素
void deleteItem_vector(vector *v)
{
    if (v->size != 0)
        free(v->data[--v->size]);
}
// 获取索引index处的int类型的值
int val_int_vector(vector *v, int index)
{
    if (index >= 0 && index < v->size)
        return *(int *)v->data[index];
    else
        return INT_MAX;
}
// 获取索引index处的char类型的字符串
char *val_char_vector(vector *v, int index)
{
    if (index >= 0 && index < v->size)
        return (char *)v->data[index];
    else
        return NULL;
}
//打印整形向量
void print_int_vector(vector *v)
{
    for(int i=0;i<v->size;i++)
    printf("%d ",*(int *)v->data[i]);
    printf("\n");
}
void print_char_vector(vector *v)
{
    for(int i=0;i<v->size;i++)
    printf("%s ",(char *)v->data[i]);
    printf("\n");
}
/*----------------树基本操作----------------*/
// 创建新树
Tree *create_tree(vector *v)
{
    Tree *t = malloc(sizeof(Tree));
    t->tree = v;
    return t;
}
// 清除树
void free_tree(Tree *t)
{
    if (t)
    {
        free_vector(t->tree);
        free(t);
    }
}
// 左子树索引
int left(int index)
{
    return index * 2 + 1;
}
// 右子树索引
int right(int index)
{
    return index * 2 + 2;
}
// 父节点索引
int parent(int index)
{
    return (index - 1) / 2;
}
// 深度优先遍历
void DeepFirstSearch(Tree *t, int index, char *order, vector *arr)
{
    // 返回触发点
    if (val_int_vector(t->tree, index) == INT_MAX)
        return;
    if (strcmp(order, "pre") == 0) // 前序遍历
    {
        int temp = val_int_vector(t->tree, index);
        addItem_vector(arr, &temp, sizeof(int));
    }
    DeepFirstSearch(t, left(index), order, arr); // 左节点递归
    if (strcmp(order, "in") == 0)                // 中序遍历
    {
        int temp = val_int_vector(t->tree, index);
        addItem_vector(arr, &temp, sizeof(int));
    }
    DeepFirstSearch(t, right(index), order, arr); // 右节点递归
    if (strcmp(order, "post") == 0)               // 后序遍历
    {
        int temp = val_int_vector(t->tree, index);
        addItem_vector(arr, &temp, sizeof(int));
    }
}
// 层序遍历
vector *levelOrder(Tree *t)
{
    vector *res = create_vector();
    for (int i = 0; i < t->tree->size; i++)
    {
        int temp = val_int_vector(t->tree, i);
        if (temp != INT_MAX)
            addItem_vector(res, &temp, sizeof(int));
    }
    return res;
}
// 前序遍历
vector *preOrder(Tree *t)
{
    vector *res=create_vector();
    DeepFirstSearch(t,0,"pre",res);
    return res;
}
//中序遍历
vector *inOrder(Tree *t)
{
    vector *res=create_vector();
    DeepFirstSearch(t,0,"in",res);
    return res;
}
//后序遍历
vector *postOrder(Tree *t)
{
    vector *res=create_vector();
    DeepFirstSearch(t,0,"post",res);
    return res;
}
int main()
{
    int arr[] = {1, 2, 3, 4, INT_MAX, 6, 7, 8, 9, INT_MAX, INT_MAX, 12, INT_MAX, INT_MAX, 15};
    Tree *t=create_tree(create_vector());
    for(int i=0;i<sizeof(arr)/sizeof(int);i++)
        addItem_vector(t->tree,&arr[i],sizeof(int));
    //层序遍历
    printf("level:\n");
    vector *level_arr=levelOrder(t);
    print_int_vector(level_arr);
    //前序遍历
    printf("pre:\n");
    vector *pre_arr=preOrder(t);
    print_int_vector(pre_arr);
    //中序遍历
    printf("in:\n");
    vector *in_arr=inOrder(t);
    print_int_vector(in_arr);
    //后序遍历
    printf("post:\n");
    vector *post_arr=postOrder(t);
    print_int_vector(post_arr);
    //清理堆内存
    free_vector(level_arr);
    free_vector(pre_arr);
    free_vector(in_arr);
    free_vector(post_arr);
    free_tree(t);
}