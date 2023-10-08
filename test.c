#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
typedef struct _tree
{
    int val;
    int height;
    struct _tree *left;
    struct _tree *right;
} Tree;
// 创建树
Tree *create_tree(int val)
{
    Tree *t = malloc(sizeof(Tree));
    t->val = val;
    t->height = 1;
    t->left = t->right = NULL;
    return t;
}
// 清除树
void free_tree(Tree *t)
{
    if (t == NULL)
        return;
    free_tree(t->left);
    free_tree(t->right);
    free(t);
}
// 搜索节点
Tree *search_tree(Tree *root, int val)
{
    Tree *t = root;
    while (t != NULL)
    {
        if (t->val > val)
            t = t->left;
        else if (t->val < val)
            t->right;
        else
            return t;
    }
    printf("没找到节点！");
    return NULL;
}
// 插入节点
void insert_tree(Tree *root, int val)
{
    if (root == NULL)return;//如果根节点为NULL则直接返回
    Tree *node = root;//创建一个指针指向根节点
    while (node->left != NULL || node->right != NULL)//如果有左节点或者右节点就要循环
    {
        if (node->val > val)//如果要插入的值大于当前节点则往左子树找，如果左子树是空则直接跳出循环
        {
            if(node->left)node = node->left;
            else break;
        }
        else if (node->val < val)//如果要插入的值小于当前节点则往右子树找，如果右子树是空则直接跳出循环
        {
            if(node->right)node = node->right;
            else break;
        }
        else if (node->val == val)//如果要插入的值和当前节点相同则跳出函数
            return;
    }
    if (node->val > val)//插入左节点
        node->left = create_tree(val);
    else if (node->val < val)//插入右节点
        node->right = create_tree(val);
}
// 删除节点
void delete_tree(Tree *root, int val)
{
    int flag = -1;//建立一个标志，flag为0表示删除节点在父节点的左子节点，为1则反之
    Tree *cur = root, *pre = NULL;//定义一个cur和pre，cur代表待删除节点，pre代表待删除节点的父节点
    while (cur && cur->val != val)//通过循环找到待删除节点，将cur和pre指向它们代表的节点，并更新flag的值
    {
        if (cur->val > val)//如果val值大于当前节点，则往右子树找
        {
            pre = cur;
            cur = cur->left;
            flag = 0;
        }
        else//如果val值小于当前节点，则往左子树找
        {
            pre = cur;
            cur = cur->right;
            flag = 1;
        }
    }
    if (cur != NULL)//如果cur不为NULL(找到了要删除的节点)
    {
        if (root->val == val)//如果要删根节点，直接free掉
            free(root);
        else if (cur->left == NULL && cur->right == NULL)//如果要删叶节点，直接free掉并使父节点指向叶节点改为指向NULL
        {
            free(cur);
            if (flag)
                pre->right = NULL;
            else
                pre->left = NULL;
        }
        else if (cur->left && !cur->right)//如果要删节点只有一个左子树，将父节点指向左子树后free掉待删除节点
        {
            if (flag)
                pre->right = cur->left;
            else
                pre->left = cur->left;
            free(cur);
        }
        else if (!cur->left && cur->right)//如果要删节点只有一个右子树，将父节点指向右子树后free掉待删除节点
        {
            if (flag)
                pre->right = cur->right;
            else
                pre->left = cur->right;
            free(cur);
        }
        else//如果要删节点又有左子树又有右子树，那么将右子树最小节点代替待删除节点后删除节点
        {
            Tree *t = cur->right, *p = NULL;//先用t指向右子树根节点，t之后代表右子树最小节点，p之后代表t的父节点
            while (t->left)//通过循环使t和p符合其定位
            {
                p = t;
                t = t->left;
                if (t->left == NULL)//循环结束时t指向最小节点
                    break;
            }
            if (flag)//父节点先指向待删节点右子树最小节点
                pre->right = t;
            else
                pre->left = t;
            t->left = cur->left;//最小节点左边指向待删节点左子树
            if (p)//如果p不是NULL(最小节点不是右子树根节点),则把最小节点右边再指向待删节点右边(右子树根节点)，并把原父节点的左边指向NULL
            {
                t->right = cur->right;
                p->left = NULL;
            }
            free(cur);//删除待删节点
        }
    }
    else printf("未找到要删除节点");
}
Tree *arrTotree(int *arr, int size)
{
    if (size <= 0)
        return NULL;
    Tree *t = create_tree(arr[0]);
    t->left = t->right = NULL;
    t->height = 1;
    for (int i = 1; i < size; i++)
        insert_tree(t, arr[i]);
    return t;
}
void inPrint(Tree *t)
{
    if(t==NULL)return;
    inPrint(t->left);
    printf("%d ",t->val);
    inPrint(t->right);
}
int main()
{
    int arr[]={0,1,3,4,14,12,5,2,7,8,10};
    Tree *t=arrTotree(arr,sizeof(arr)/sizeof(int));
    inPrint(t);
    delete_tree(t,33);
    delete_tree(t,12);
    delete_tree(t,14);
    printf("\n");
    inPrint(t);
    free_tree(t);
    return 0;
}