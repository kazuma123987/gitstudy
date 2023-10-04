#include <stdio.h>
#include <stdlib.h>  //malloc,free,rand,srand,system,exit,atoi,itoa,abs,labs,qsort
#include <stdbool.h> //bool,true,false
#include <limits.h>  //INT_MAX
#include <string.h>  //memcpy,strcat...
// 节点封装
typedef struct _node
{
    int key;
    char *val;
    struct _node *next;
} Node;
// 链表封装
typedef struct list
{
    Node *head;
    Node *tail;
} List;
typedef struct
{
    int size;         // 当前节点个数
    int capacity;     // 哈希表容量(最大节点个数)
    int extendRadio;  // 扩容倍数
    double loadThres; // 触发扩容的负载因子阈值
    List *buckets;    // 装载节点的链表结构的桶
} hashMap;
// 函数声明
hashMap *create_hashmap(const int init_cap);
void free_hashmap(hashMap **m);
int hash_func(const hashMap *m, const int key);
double loadFactor(const hashMap *m);
void extend_hash(hashMap *m);
void putItem_hash(hashMap *m,const int key,const char *val);
void deleteItem_hash(hashMap *m,const int key);
const char *Inquire_hash(const hashMap *m,const int key);
void print_hash(const hashMap *m);
// 主函数
int main()
{
    hashMap *map = create_hashmap(4);
    putItem_hash(map, 131194, "hello");
    putItem_hash(map, 35394, "world");
    putItem_hash(map, 3131, "小蓝");
    putItem_hash(map, 1414, "陨石");
    putItem_hash(map, 13113, "地球");
    printf("before:\n");
    print_hash(map);
    deleteItem_hash(map, 13113);
    printf("after:\n");
    print_hash(map);
    free_hashmap(&map);
    return 0;
}
// 创建哈希表
hashMap *create_hashmap(const int init_cap)
{
    hashMap *m = malloc(sizeof(hashMap));
    m->size = 0;
    m->capacity = init_cap;
    m->extendRadio = 2;
    m->loadThres = 2.0 / 3.0;
    m->buckets = malloc(sizeof(List) * m->capacity); // ！！！List *变量分配时应按sizeof(List)，而不是sizeof((List *)m->buckets)
    /*从(List *)m->buckets指向的值(List)m->buckets[0]开始，把整个(List)m->buckets[m->capacity]数组的值按字节初始化为0
    这样（List）m->buckets[m->capacity]里面的(Node *)head也被赋值为0(即为NULL)*/
    memset(m->buckets, 0, sizeof(List) * m->capacity); //!!!注意(int *)分配sizeof(int),(int **)分配sizeof(int *),(List *)分配sizeof(List)
    return m;
}
// 清除哈希表
void free_hashmap(hashMap **m)
{
    List *li = (*m)->buckets;
    for (int i = 0; i < (*m)->capacity; i++)
    {
        for (Node *cur = li[i].head, *del; cur;)
        {
            del = cur;
            cur = cur->next; // 这两步应该在for循环的判断之后进行
            free(del->val);
            free(del);
        }
    }
    free(li);
    free(*m);
}
// 哈希函数
int hash_func(const hashMap *m, const int key)
{
    return key % m->capacity;
}
// 负载因子
double loadFactor(const hashMap *m)
{
    return (double)m->size / m->capacity;
}
// 哈希表扩容
void extend_hash(hashMap *m)
{
    int old_size = m->capacity;                        // ！！！注意这里的赋值很重要，决定下面给新表赋值的循环次数，如果按新版容量的次数进行赋值会导致指针出错，因为旧表后面部分没初始化
    m->capacity *= m->extendRadio;                     // 按照扩容倍率把容量扩大(实际上容量应该尽可能是质数，减少周期分布，比如9会出现0，3，6的周期分布)
    List *oldbuckets = m->buckets;                     // 将旧桶数组保存在oldbuckets里
    m->buckets = malloc(sizeof(List) * m->capacity);   // 分配新桶数组
    memset(m->buckets, 0, sizeof(List) * m->capacity); // 初始化head值，详见前面创建哈希表的分析
    m->size = 0;                                       // 防止下面赋值时put_hash重复对m->size进行操作
    for (int i = 0; i < old_size; i++)                 // 注意要循环的次数是旧表链表总个数old_size，而不是新表m->capacity,更不是节点个数m->size,
    {
        for (Node *old = oldbuckets[i].head, *del; old;)
        {
            putItem_hash(m, old->key, old->val);
            del = old;
            old = old->next; // 这两步应该在for循环的判断之后进行
            free(del);
        }
    }
}
// 添加键值对
void putItem_hash(hashMap *m,const int key,const char *val)
{
    // 添加节点前要判断是否需要扩容
    if (loadFactor(m) > m->loadThres)
        extend_hash(m);
    // 创建新节点
    Node *newNode = malloc(sizeof(Node));
    newNode->key = key;
    newNode->val = malloc(strlen(val) + 1);
    strcpy(newNode->val, val);
    newNode->next = NULL;
    // 连接桶链表
    int index = hash_func(m, key);
    Node *cur = m->buckets[index].head;
    while (1)
    {
        // 如果index对应桶的链表head为空，则把新节点作为头节点，并使size加1
        if (cur == NULL)
        {
            m->buckets[index].head = newNode;
            m->size++;
            break;
        }
        // 如果链表中有相同的key值，则覆盖其val值
        if (cur->key == key)
        {
            free(cur->val);
            cur->val = malloc(strlen(val) + 1);
            strcpy(cur->val, val);
            break;
        }
        // 当到达最后一个节点时连接新节点
        if (cur->next == NULL)
        {
            cur->next = newNode;
            m->size++;
            break;
        }
        // 都不满足条件则把cur指向下一个节点
        cur = cur->next;
    }
}
// 按key值删除键值对
void deleteItem_hash(hashMap *m,const int key)
{
    int index = hash_func(m, key);
    for (Node *cur = m->buckets[index].head, *pre = NULL; cur; pre = cur, cur = cur->next)
    {
        // 如果找到了要删除的节点
        if (cur->key == key)
        {
            // 如果头节点是要删的节点
            if (pre == NULL)
            {
                m->size--;
                m->buckets[index].head = cur->next;
                free(cur->val);
                free(cur);
                return;
            }
            // 如果要删的不是头节点
            else
            {
                m->size--;
                pre->next = cur->next;
                free(cur->val);
                free(cur);
                return;
            }
        }
    }
    printf("要删除的元素不存在!");
}
//根据key值查询value
const char *Inquire_hash(const hashMap *m,const int key)
{
    int index=hash_func(m,key);
    for(Node *cur=m->buckets[index].head,*pre=NULL;cur;pre=cur,cur=cur->next)
    {
        if(cur->key==key)
        {
            return cur->val;
        }
    }
    printf("没找到要查询的值!");
    return NULL;
}
//打印哈希表
void print_hash(const hashMap *m)
{
    for(int i=0;i<m->capacity;i++)
    {
        for(Node *cur=m->buckets[i].head;cur;cur=cur->next)
            printf("key:%d,val:%s\n",cur->key,cur->val);
    }
}