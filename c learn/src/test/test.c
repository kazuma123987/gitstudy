#include "test.h"
#define LIST_HEAD(name) \
    list_t name = {&(name), &(name)}
#define PACKED __attribute__((__packed__))
typedef struct list
{
    struct list *prev;
    struct list *next;
} list_t;
typedef struct PACKED pNode
{
    char a;
    char b;
    list_t p;
} pNode;
#define __offset(TYPE, MEMBER) (size_t)(&((TYPE *)0)->MEMBER)
int main(int argc, char *argv[])
{
    pNode data = {'a', 'b', {NULL, NULL}};
    void *ptr1 = (void *)((unsigned char *)&data.p - __offset(pNode, p));
    void *ptr2 = &data;
    size_t b = __offset(pNode, p);
    return 0;
}