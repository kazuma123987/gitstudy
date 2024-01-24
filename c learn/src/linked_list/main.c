#include "my_linked_list.h"
#include <time.h>
int main(int argc, char *argv[])
{
    int array[5] = {1, 2, 3, 4, 5};
    LinkedList *list = linked_list_create();
    // 往链表尾部添加数据
    for (int i = 0; i < 5000000; i++)
        linked_list_push(list, 5000000 - i);
    // 链表归并排序
    clock_t start = clock();
    linked_list_merge_sort(list);
    printf("time:%ldms\n", clock() - start);
    // 验证链表正确性
    ListNode *tmp = list->head;
    for (int i = 0; i < 1000000; i++)
    {
        if (tmp->data != i + 1 || tmp == NULL)
        {
            printf("test failed\n");
            break;
        }
        tmp = tmp->next;
    }
    // linked_list_print(list->head);
    printf("num:%d\n", linked_list_getnum(list));
    printf("list[2]:%d\n", linked_list_access(list->head, 2)->data);
    printf("list中有值为100000000的节点:%s", (linked_list_find_by_data(list->head, 100000000) != NULL) ? "true" : "false");
    linked_list_free(list);
    return 0;
}