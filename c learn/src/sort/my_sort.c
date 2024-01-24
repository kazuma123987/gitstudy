#include "my_sort.h"
#include <string.h>
// 交换索引
static inline void swap(int *array, int index1, int index2)
{
    int tmp_val = array[index1];
    array[index1] = array[index2];
    array[index2] = tmp_val;
}
// 取三个数的中位数
static inline int mid_of_three(int *array, int index1, int index2, int index3)
{
    // 此处使用异或运算来简化代码(一真一假则为真,两真或两假都为假)
    // 异或规则为 0 ^ 0 = 1 ^ 1 = 0, 0 ^ 1 = 1 ^ 0 = 1
    if ((array[index1] < array[index2]) ^ (array[index1] < array[index3]))
        return index1;
    else if ((array[index2] < array[index1]) ^ (array[index2] < array[index3]))
        return index2;
    else
        return index3;
}
// 堆排序辅助函数(从指定索引开始向下堆化)
static inline void Vector_SiftDown(int *array, int arrayNum, int index)
{
    while (1)
    {
        int left = index * 2 + 1;
        int right = left + 1;
        int max_index = index;
        if (left < arrayNum && array[max_index] < array[left])
            max_index = left;
        if (right < arrayNum && array[max_index] < array[right])
            max_index = right;
        if (max_index == index)
            break;
        int tmp_val = array[index];
        array[index] = array[max_index];
        array[max_index] = tmp_val;
        index = max_index;
    }
}
// 快速排序辅助函数
static inline int partition(int *array, int left, int right)
{
    int i = left;
    int j = right;
    int mid = mid_of_three(array, left, (left + right) / 2, right); // 把数组左边中间和右边的数的中位数作为基准
    swap(array, left, mid);                                         // 把基准交换到最左边
    while (i < j)
    {
        while (i < j && array[j] >= array[left]) // 从右到左找第一个小于基准值的索引
            j--;
        while (i < j && array[i] <= array[left]) // 从左到右找第一个大于基准值的索引
            i++;
        swap(array, i, j); // 交换两者
    }
    swap(array, i, left); // 交换基准值与i(接近但小于等于基准值)对应的值
    return i;             // 返回基准值索引
}
static inline void mergeArray(int *array, int left, int mid, int right)
{
    int tmpNum = right - left + 1;                  // 数组的元素数量
    int *tmp = (int *)malloc(sizeof(int) * tmpNum); // 分配临时数组
    int i = left, j = mid + 1, k = 0;               // 数组范围是[left,mid],[mid+1,right]
    while (i <= mid && j <= right)                  // tmp数组存放两数组最小值(能这样做是因为两数组都按从小到大排序好了)
        tmp[k++] = (array[i] <= array[j]) ? array[i++] : array[j++];
    while (i <= mid) // 如果j在while (i <= mid && j <= right)循环中存放完了则存放i剩余元素
        tmp[k++] = array[i++];
    while (j <= right) // 如果i在while (i <= mid && j <= right)循环中存放完了则存放j剩余元素
        tmp[k++] = array[j++];
    memcpy(array + left, tmp, tmpNum * sizeof(int)); // 把排序好的数组复原回去
    free(tmp);
}
// 选择排序(selection sort)
void selection_sort(int *array, int arrayNum)
{
    for (int i = 0; i < arrayNum - 1; i++) // 执行n-1轮排序
    {
        int min_index = i;
        for (int j = i + 1; j < arrayNum; j++)
        {
            if (array[j] < array[min_index])
                min_index = j;
        }
        if (min_index != i)
            swap(array, min_index, i);
    }
}
// 堆排序(heap sort)
void heap_sort(int *array, int arrayNum)
{
    // 建立大顶堆
    for (int i = (arrayNum - 2) / 2; i >= 0; i--)
        Vector_SiftDown(array, arrayNum, i);
    for (int i = arrayNum - 1; i > 0; i--)
    {
        // 交换首尾
        swap(array, 0, i);
        // 对数量为i的堆进行堆化(这样堆顶又是最大值)
        Vector_SiftDown(array, i, 0);
    }
}
// 冒泡排序(bubble sort)
void bubble_sort(int *array, int arrayNum)
{
    for (int i = arrayNum - 1; i > 0; i--) // i的范围[n-1,1]
    {
        char flag = 1;              // 定义一个flag,如果本轮冒泡有进行交换则置0
        for (int j = 0; j < i; j++) // 排序区间为[0,i],j的范围[0,i-1]
        {
            if (array[j] > array[j + 1])
            {
                swap(array, j, j + 1);
                flag = 0;
            }
        }
        if (flag)
            break; // 如果本轮冒泡没有进行交换则结束冒泡
    }
}
// 插入排序(insertion sort)
void insertion_sort(int *array, int arrayNum)
{
    for (int i = 1; i < arrayNum; i++) // i代表base的索引,范围[1,n-1]
    {
        int base = array[i];              // 先把要插入的数存在base中
        int j = i - 1;                    // j的范围:base前一个元素~第一个元素
        while (j >= 0 && base < array[j]) // 要插入的索引(j+1)最开始是base的索引,如果base更小,则要插入的索引-1
        {
            array[j + 1] = array[j]; // 如果base更小,则向右赋值,给要插入的base腾出空间
            j--;
        }
        array[j + 1] = base; // 把base插入到正确的位置
    }
}
// 快速排序(quick sort)
void quick_sort(int *array, int left, int right)
{
    while (left < right)
    {
        int baseIndex = partition(array, left, right);
        if (baseIndex - left > right - baseIndex) // 只递归排序长数组
        {
            quick_sort(array, left, baseIndex - 1); // 排序[left,baseIndex-1]
            left = baseIndex + 1;                   // 未排序[baseIndex+1,right],则让left=baseIndex+1,下次循环即可进行排序
        }
        else
        {
            quick_sort(array, baseIndex + 1, right); // 排序[baseIndex+1,right]
            right = baseIndex - 1;                   // 未排序[left,baseIndex-1],则让right = baseIndex - 1,下次循环即可进行排序
        }
    }
}
// 归并排序(merge sort)
void merge_sort(int *array, int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2; // 计算中点
    merge_sort(array, left, mid);
    merge_sort(array, mid + 1, right);
    mergeArray(array, left, mid, right); // 后序遍历进行合并
}