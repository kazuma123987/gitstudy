#include "my_heap.h"
#include <time.h>
int main(int argc, char *argv[])
{
    srand(time(0));
    Heap *heap = Heap_create(3);
    int array[20];
    for(int i=0;i<20;i++)
    {
        array[i]=rand()%100;
    }
    for (int i = 0; i < 3; i++)
    {
        MinHeap_push(&heap, array[i]);
    }
    for(int i=3;i<20;i++)
    {
        if(array[i]>Heap_peek(heap))
        {
            MinHeap_pop(heap);
            MinHeap_push(&heap,array[i]);
        }
    }
    Heap_print(heap);
    Heap_free(heap);
    return 0;
}