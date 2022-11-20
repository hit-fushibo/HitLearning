#include "Bst.h"

#include "Bst.c"

int func(int a[], int n)
{
    int temp, low = 0, low0 = 0, high = n - 1, high0 = n - 1, flag = 1, k = n / 2, i;
    int s1 = 0, s2 = 0;
    while (flag)
    {
        temp = a[low];     // 选择基准
        while (low < high) // 进行划分
        {
            while (low < high && a[high] >= temp)
                --high;
            if (low != high)
                a[low] = a[high];
            while (low < high && a[low] <= temp)
                ++low;
            if (low != high)
                a[high] = a[low];
        }
        a[low] = temp;
        if (low == k - 1) // 判断是否继续
            flag = 0;
        else if (low < k - 1)
        {
            low0 = ++low;
            high = high0;
        }
        else
        {
            high = --high0;
            low = low0;
        }
    }
    for (i = 0; i < k; i++)
        s1 += a[i];
    for (i = k; i < n; i++)
        s2 += a[i];
    return s2 - s1;
}

int main(void)
{
    TestSorted();

    return 0;
}