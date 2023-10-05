#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
#define QUENE_SIZE 100
typedef struct _tree
{
    int value;
    int height;
    struct _tree *left;
    struct _tree *right;
} Tree;
typedef struct
{
    int front;
    int rear;
    int capacity;
    Tree **pNode; // 要存放的是指针，所以用指针数组
} quene;
/*--------------队列基本操作--------------*/
// 创建队列
quene *create_quene()
{
    quene *q = malloc(sizeof(quene));
    q->front = q->rear = 0;
    q->capacity = QUENE_SIZE;
    q->pNode = malloc(sizeof(Tree *) * q->capacity);
    return q;
}
// 入队
void quene_push(quene *q, Tree *node)
{
    if ((q->rear + 1) % q->capacity == q->front)
    {
        printf("队列已满");
        return;
    }
    q->pNode[(q->rear++) % q->capacity] = node;
}
// 出队
Tree *quene_pop(quene *q)
{
    if (q->front == q->rear)
    {
        printf("队列已空");
        return NULL;
    }
    return q->pNode[(q->front++) % q->capacity];
}
// 判断队列是否为空
bool isEmpty_quene(quene *q)
{
    return q->front == q->rear;
}
/*--------------树基本操作--------------*/
// 创建树
Tree *create_tree(int val)
{
    Tree *node = malloc(sizeof(Tree));
    node->height = 1;
    node->left = node->right = NULL;
    node->value = val;
    return node;
}
// 清除树
void free_tree(Tree **t)
{
    if (*t == NULL)
        return;
    free_tree(&(*t)->left);
    free_tree(&(*t)->right);
    free(*t);
}
// 查看树的高度
int tree_height(Tree *t)
{
    if (t == NULL)
        return -1;
    return t->height;
}
// 更新树的结点高度
int height_update(Tree *t)
{
    int ret = 0;//定义返回值
    if (t->left == NULL && t->right == NULL)//如果是叶节点直接返回1
        ret = 1;
    else//如果不是叶结点则返回左子树和右子树中高度最大者，返回的值+1就是当前父节点的高度
    {
        int lh = height_update(t->left) + 1;
        int rh = height_update(t->right) + 1;
        if (lh > rh)
            ret = lh;
        else
            ret = rh;
    }
    t->height = ret;//更新当前节点高度
    return ret;
}
//  层序遍历
void getArray_levelOrder(Tree *t, int **new_arr, int *size)
{
    *size = 0;
    quene *temp_quene = create_quene();
    quene_push(temp_quene, t);
    int *arr = malloc(sizeof(int) * temp_quene->capacity);
    int index = 0;
    for (Tree *node; !isEmpty_quene(temp_quene);)
    {
        node = quene_pop(temp_quene);
        arr[index++] = node->value;
        if (node->left != NULL)
            quene_push(temp_quene, node->left);
        if (node->right != NULL)
            quene_push(temp_quene, node->right);
    }
    arr = realloc(arr, sizeof(int) * index);
    free(temp_quene->pNode);
    free(temp_quene);
    *size = index;
    *new_arr = arr;
}
// 数组转树
Tree *ArrToTree(int *arr, size_t size)
{
    int index = 0;                          // 数组下标
    quene *q = create_quene();              // 创建临时队列装树节点
    Tree *root = create_tree(arr[index++]); // 根节点
    quene_push(q, root);                    // 根节点入队
    while (q->front != q->rear)             // 层序遍历创建二叉树
    {
        Tree *node = quene_pop(q); // 队列的节点出队(按照层序遍历)
        if (index < size)          // 只要数组还没遍历完就继续
        {
            node->left = create_tree(arr[index++]);
            quene_push(q, node->left);
        }
        if (index < size) // 只要数组还没遍历完就继续
        {
            node->right = create_tree(arr[index++]);
            quene_push(q, node->right);
        }
    }
    // 更新树的高度
    height_update(root);
    // 临时队列清理
    free(q->pNode);
    free(q);
    return root;
}
int main()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int size, *arr;
    Tree *t = ArrToTree(a, sizeof(a) / sizeof(int));
    getArray_levelOrder(t, &arr, &size);
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    free_tree(&t);
    free(arr);
}