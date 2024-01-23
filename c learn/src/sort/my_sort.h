#ifndef __MY_SORT__H
#define __MY_SORT__H
#include <stdlib.h>
#ifdef __cplusplus
extern "C"
{
#endif
    // 选择排序(selection sort),每次找出最小元素放在前面
    void selection_sort(int *array, int arrayNum);
    // 堆排序(heap sort),构建最大堆,并交换堆的首尾,然后堆的大小减一,并对新堆进行堆化
    void heap_sort(int *array, int arrayNum);
    // 冒泡排序(bubble sort),每次比较相邻元素,如果后者大则交换
    void bubble_sort(int *array, int arrayNum);
    // 插入排序(insertion sort),从第二个元素开始,依次在前面已排序好的元素中进行正确的插入
    void insertion_sort(int *array, int arrayNum);
    // 快速排序(quick sort),每次从数组中找出一个基准值,把低于基准的放在左边,高于基准的放在右边
    void quick_sort(int *array, int left, int right);
    // 归并排序(merge sort),先递归地划分数组为左右数组,然后再进行合并并排序
    void merge_sort(int *array, int left, int right);
#ifdef __cplusplus
}
#endif
#endif