#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
#include <windows.h> //Sleep()
#include <conio.h>   //kbhit(),_getch()
// 树节点
typedef struct _tree
{
    int val;
    int height;
    struct _tree *left;
    struct _tree *right;
} TreeNode;
// AVL树封装
typedef struct
{
    TreeNode *root;
} AVL_Tree;
// 创建新节点
TreeNode *newnode(int val)
{
    TreeNode *node = malloc(sizeof(TreeNode));
    node->val = val;
    node->left = node->right =NULL;
    node->height = 1;
    return node;
}
// 创建新树
AVL_Tree *newAVL()
{
    AVL_Tree *avl = malloc(sizeof(AVL_Tree));
    avl->root = NULL;
    return avl;
}
// 返回节点高度
int height(TreeNode *t)
{
    if (t != NULL)
        return t->height;
    return 0;
}
// 更新节点高度
void height_update(TreeNode *t)
{
    if (t == NULL)
        return;
    int lh = height(t->left);
    int rh = height(t->right);
    if (lh >= rh)
        t->height=lh + 1;
    else
        t->height=rh + 1;
}
// 平衡因子
int balanceFactor(TreeNode *t)
{
    if (t == NULL)
        return 0;
    return height(t->left) - height(t->right);
}
// 左旋转(只会在旋转操作函数失衡下调用，所以不用考虑其他情况)
TreeNode *lRotate(TreeNode *t)//左旋一般以child节点为中心，对节点t逆时针旋转到child的left端，
//但如果child的left端有节点grandchild，则将grandchild放在t的右端（因为child和grandchild都在t的右边，比t大）
{
    TreeNode *child = t->right;//左旋说明右方倾斜，则子节点朝右
    TreeNode *grandchild = child->left;
    child->left = t;
    t->right = grandchild;
    height_update(t);
    height_update(child);
    return child;
}
// 右旋转(同上，不会出现错误调用情况)
TreeNode *rRotate(TreeNode *t)
{
    TreeNode *child = t->left;
    TreeNode *grandchild = child->right;
    child->right = t;
    t->left = grandchild;
    height_update(t);
    height_update(child);
    return child;
}
// 旋转操作
TreeNode *rotate(TreeNode *t)
{
    int factor = balanceFactor(t);
    if (factor > 1)//左偏
    {
        if (balanceFactor(t->left) >= 0)//子节点也左偏，右转
            return rRotate(t);
        else//子节点右偏，左右旋转（先子节点左转，再父节点右转）
        {
            t->left = lRotate(t->left);
            return rRotate(t);
        }
    }
    else if (factor < -1)//右偏
    {
        if (balanceFactor(t->right) <= 0)//子节点也右偏，左转
            return lRotate(t);
        else//子节点左偏，右左旋转（先子节点右转，再父节点左转）
        {
            t->right = rRotate(t->right);
            return lRotate(t);
        }
    }
    else//不偏则直接返回原值
        return t;
}
//递归插入操作
TreeNode *insert(TreeNode *t, int val)
{
    if (t == NULL)//如果找到了尽头，则给父节点连接新的子节点
        return newnode(val);
    if (t->val > val)//要插入的值更小，则往左边插入
        t->left = insert(t->left, val);
    else if (t->val < val)//要插入的值更大，则往右边插入
        t->right = insert(t->right, val);
    else//如果有值和插入的值相等，则不插入，直接返回原值
        return t;
    t = rotate(t);//旋转操作
    height_update(t);//因为当插入后如果没偏那rotate会直接返回，不会更新高度，所以在这里要更新高度
    return t;
}
//递归删除操作
TreeNode *removeItem(TreeNode *t, int val)//递归删除时一条路径上的节点都应旋转并更新高度
{
    if (t == NULL)
        return t;
    if (t->val > val)
        t->left = removeItem(t->left, val);//传递旋转及更新后的左节点
    else if (t->val < val)
        t->right = removeItem(t->right, val);//传递旋转及更新后的右节点
    else//找到了要删除的节点
    {
        if (t->left == NULL || t->right == NULL)
        {
            TreeNode *node = t->left;
            if (t->right != NULL)
                node = t->right;
            free(t);
            if (node == NULL)//如果t是叶节点，则删除后直接返回NULL传递给父节点
                return NULL;
            else//如果t有一个子节点（但子节点可能还有子节点），所以删除后赋值node给t，
            //旋转并更新t的高度后把t传递给父节点（如果没错误操作其实可以直接return node）
                t = node;
        }
        else//如果待删除的节点t有两个子节点
        {
            TreeNode *cur;
            for (cur=t->right;cur->left;cur = cur->left);//找到t的右子树的最小节点，赋值给cur
            int cur_val=cur->val;//暂存cur的值
            t->right=removeItem(t->right,cur_val);//删除t的右子树的最小节点后把根节点传递给t的右指针
            t->val=cur_val;//把t的值替换为最小节点的值（这个操作相当于删除了t，并把右子树最小节点替换t的位置）
        }
    }
    t=rotate(t);//在路径上递归旋转节点的值
    height_update(t);//更新高度，防止rotate直接返回时未更新
    return t;//传递更新后的值给路径上的父节点
}
//查找操作
TreeNode *find(TreeNode *t,int val)
{
    if(t==NULL)return NULL;
    if(t->val>val)return find(t->left,val);
    else if(t->val<val)return find(t->right,val);
    else return t;
}
//中序遍历打印树
void printAVL(TreeNode *root)
{
    if(root==NULL)return;
    printAVL(root->left);
    printf("%d ",root->val);
    printAVL(root->right);
}
//递归清除树
void freeTree(TreeNode *t)
{
    if(t==NULL)return;
    freeTree(t->left);
    freeTree(t->right);
    free(t);
}
//清除AVL树
void freeAVL(AVL_Tree *avl)
{
    freeTree(avl->root);
    free(avl);
}
int main()
{
    AVL_Tree *avl=newAVL();
    for(int i=1;i<11;i++)
    avl->root=insert(avl->root,i);
    printAVL(avl->root);
    avl->root=removeItem(avl->root,6);
    TreeNode *a=find(avl->root,8);
    printf("\n");
    printAVL(avl->root);
    freeAVL(avl);
}