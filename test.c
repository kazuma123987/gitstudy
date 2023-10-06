#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
#define QUEUE_SIZE (100)//宏定义加括号避免出现其他问题
// 树节点
typedef struct _tree
{
    int val;
    int height;
    struct _tree *left;
    struct _tree *right;
} Tree;
// 队列节点
typedef struct
{
    int capacity;
    int front;
    int rear;
    Tree **pTree;
} queue;
/*--------------队列基本操作--------------*/
// 创建新队列
queue *create_queue(int cap)
{
    queue *q = malloc(sizeof(queue));
    q->capacity = cap;
    q->front = q->rear = 0;
    q->pTree = malloc(sizeof(Tree *) * q->capacity);
    return q;
}
// 清除队列
void queue_free(queue **q)
{
    free((*q)->pTree);
    free((*q));
    *q = NULL;
}
// 入队
void enqueue(queue *q, Tree *t)
{
    if ((q->rear + 1) % q->capacity == q->front)
    {
        printf("队列已满,请扩大队列容量");
        return;
    }
    q->pTree[q->rear = (q->rear + 1) % q->capacity] = t;
}
// 出队
Tree *dequeue(queue *q)
{
    if (q->front == q->rear)
    {
        printf("队列已空");
        return NULL;
    }
    return q->pTree[q->front = (q->front + 1) % q->capacity];
}
// 判断队列是否为空
bool isEmpty_queue(queue *q)
{
    return q->front == q->rear;
}
/*--------------树基本操作--------------*/
// 创建新树
Tree *create_tree(const int val)
{
    Tree *t = malloc(sizeof(Tree));
    t->val = val;
    t->height = 1;
    t->left = t->right = NULL;
    return t;
}
// 清除树
void free_tree(Tree **root)
{
    if (*root == NULL)
        return;
    free_tree(&(*root)->left);
    free_tree(&(*root)->right);
    free(*root);
}
//树高查询
int height_tree(Tree *t)
{
    if(t==NULL)return -1;
    return t->height;
}
//后序遍历更新树高
int height_update(Tree *t)
{
    int ret=0;
    if(t==NULL)return 0;//如果是空树直接返回0(不赋值)
    else if(t->left==NULL&&t->right==NULL)ret=1;//如果是叶节点赋值为1
    else//如果是父节点赋值为左右子树高度大者+1
    {
        int lh=height_update(t->left)+1;
        int rh=height_update(t->right)+1;
        if(lh>rh)ret=lh;
        else ret=rh;
    }
    t->height=ret;//赋值
    return ret;
}
// 数组转树
Tree *ArrToTree(int *arr, int size)
{
    int index = 0;
    Tree *root = create_tree(arr[index++]);
    queue *q = create_queue(QUEUE_SIZE);
    enqueue(q, root);
    while (!isEmpty_queue(q))
    {
        Tree *node = dequeue(q);
        if (index < size && arr[index] != INT_MAX) // 这里INT_MAX是提前对数组做好的标记，防止越界
        {
            node->left = create_tree(arr[index++]);
            enqueue(q, node->left);
        }
        if (index < size && arr[index] != INT_MAX) // 这里INT_MAX是提前对数组做好的标记，防止越界
        {
            node->right = create_tree(arr[index++]);
            enqueue(q, node->right);
        }
    }
    height_update(root);
    queue_free(&q);
    return root;
}
// 层序遍历
void levelOrder(Tree *root, int *arr)
{
    queue *q = create_queue(QUEUE_SIZE);
    enqueue(q, root);
    int index = 0;
    while (!isEmpty_queue(q))
    {
        Tree *node = dequeue(q);
        arr[index++] = node->val;
        if (node->left != NULL)
            enqueue(q, node->left);
        if (node->right != NULL)
            enqueue(q, node->right);
    }
    queue_free(&q);
}
// 先序遍历
void preOrder(Tree *root, int *arr, int *index)
{
    if (root == NULL)
        return;
    arr[(*index)++] = root->val;
    preOrder(root->left, arr, index);
    preOrder(root->right, arr, index);
}
// 中序遍历
void inOrder(Tree *root, int *arr, int *index)
{
    if (root == NULL)
        return;
    inOrder(root->left, arr, index);
    arr[(*index)++] = root->val;
    inOrder(root->right, arr, index);
}
// 后序遍历
void postOrder(Tree *root, int *arr, int *index)
{
    if (root == NULL)
        return;
    postOrder(root->left, arr, index);
    postOrder(root->right, arr, index);
    arr[(*index)++] = root->val;
}
/*--------------------其他调试--------------------*/
// 打印数组
void printArray(int *arr, int size)
{
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}
int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0,INT_MAX};              // 打上标记INT_MAX
    Tree *t = ArrToTree(arr, sizeof(arr) / sizeof(int) + 3); // 尝试写入超过数组大小的额外3个元素
    int a[20];
    memset(a + sizeof(arr) / sizeof(*arr)-1, 0xff, sizeof(*a) * (20 - sizeof(arr) / sizeof(*arr)+1)); // ！！记住memset不要超越malloc的个数，
    // ！！即malloc以后，从地址a开始最多写20个，地址a+10开始最多写入10个
    //层序遍历
    levelOrder(t, a);
    printArray(a, sizeof(a) / sizeof(int));
    //先序遍历
    int index = 0;
    preOrder(t, a, &index);
    printArray(a, sizeof(a) / sizeof(int));
    //中序遍历
    index = 0;
    inOrder(t, a, &index);
    printArray(a, sizeof(a) / sizeof(int));
    //后序遍历
    index = 0;
    postOrder(t, a, &index);
    printArray(a, sizeof(a) / sizeof(int));
    //清理树
    free_tree(&t);
    return 0;
}