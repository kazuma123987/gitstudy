#include "my_heap.h"
// 获取左子节点索引
inline int Heap_left(int index)
{
    return index * 2 + 1;
}
// 获取右子节点索引
inline int Heap_right(int index)
{
    return index * 2 + 2;
}
// 获取父节点索引
inline int Heap_parent(int index)
{
    return (index - 1) / 2;
}
// 获取堆顶元素
inline int Heap_peek(Heap *heap)
{
    return heap->data[0];
}
// 交换堆的元素
inline void Heap_Swap(Heap *heap, int index1, int index2)
{
    int tmp_val = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = tmp_val;
}
// 打印堆
void Heap_print(Heap *heap)
{
    int height = log2(heap->size) + 1;
    for (int i = 0; i < height; i++)
    {
        int num, first_index;
        first_index = pow(2, i) - 1;
        num = (i < height - 1) ? (first_index + 1) : (heap->size - first_index);
        for (int j = 0; j < num; j++)
        {
            printf("%d", heap->data[first_index + j]);
            putchar(' ');
        }
        printf("\n");
    }
}
// 创建堆
Heap *Heap_create(int capacity)
{
    Heap *heap = (Heap *)malloc(sizeof(Heap) + sizeof(int) * capacity);
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}
// 扩容堆
void Heap_realloc(Heap **heap, int capacity)
{
    if ((*heap)->capacity < capacity)
    {
        Heap *oldHeap = *heap;
        *heap = (Heap *)realloc(*heap, sizeof(Heap) + sizeof(int) * capacity);
        if (*heap == NULL)
            *heap = oldHeap;
        (*heap)->capacity = capacity;
    }
}
// 清理堆空间
inline void Heap_free(Heap *heap)
{
    free(heap);
}
/*####################最大堆####################*/
// 入堆
void MaxHeap_push(Heap **heap, int val)
{
    if ((*heap)->size == (*heap)->capacity)
        Heap_realloc(heap, (*heap)->capacity * 2);
    (*heap)->data[(*heap)->size++] = val;
    MaxHeap_siftUp(*heap, (*heap)->size - 1);
}
// 出堆,返回值为堆顶元素
int MaxHeap_pop(Heap *heap)
{
    Heap_Swap(heap, 0, --heap->size);
    MaxHeap_siftDown(heap, 0);
    return heap->data[heap->size];
}
// 从指定索引开始向下堆化
void MaxHeap_siftDown(Heap *heap, int index)
{
    int left, right, max_index;
    while (1)
    {
        left = Heap_left(index);
        right = left + 1;
        max_index = index;
        if (left < heap->size && heap->data[max_index] < heap->data[left])
            max_index = left;
        if (right < heap->size && heap->data[max_index] < heap->data[right])
            max_index = right;
        if (max_index == index)
            break;
        Heap_Swap(heap, index, max_index);
        index = max_index;
    }
}
// 从指定索引开始向上堆化
void MaxHeap_siftUp(Heap *heap, int index)
{
    int parent;
    while (1)
    {
        if (index == 0)
            break;
        parent = Heap_parent(index);
        if (heap->data[index] > heap->data[parent])
            Heap_Swap(heap, index, parent);
        else
            break;
        index = parent;
    }
}

/*####################最小堆####################*/
// 入堆
void MinHeap_push(Heap **heap, int val)
{
    if ((*heap)->size == (*heap)->capacity)
        Heap_realloc(heap, (*heap)->capacity * 2);
    (*heap)->data[(*heap)->size++] = val;
    MinHeap_siftUp(*heap, (*heap)->size - 1);
}
// 出堆,返回值为堆顶元素
int MinHeap_pop(Heap *heap)
{
    Heap_Swap(heap, 0, --heap->size);
    MinHeap_siftDown(heap, 0);
    return heap->data[heap->size];
}
// 从指定索引开始向下堆化
void MinHeap_siftDown(Heap *heap, int index)
{
    int left, right, min_index;
    while (1)
    {
        left = Heap_left(index);
        right = left + 1;
        min_index = index;
        if (left < heap->size && heap->data[min_index] > heap->data[left])
            min_index = left;
        if (right < heap->size && heap->data[min_index] > heap->data[right])
            min_index = right;
        if (min_index == index)
            break;
        Heap_Swap(heap, index, min_index);
        index = min_index;
    }
}
// 从指定索引开始向上堆化
void MinHeap_siftUp(Heap *heap, int index)
{
    int parent;
    while (1)
    {
        if (index == 0)
            break;
        parent = Heap_parent(index);
        if (heap->data[index] < heap->data[parent])
            Heap_Swap(heap, index, parent);
        else
            break;
        index = parent;
    }
}