//sort02.cpp
//归并排序
#include <iostream>
using namespace std;
//合并函数
void merge(int a[], int low, int mid, int high)
{
    int *b = new int[high - low + 1]; //申请一个辅助数组
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) //按从小到大存放到辅助数组中
    {
        if (a[i] <= a[j])
            b[k++] = a[i++];
        else
            b[k++] = a[j++];
    }
    while (i <= mid)
        b[k++] = a[i++]; //存放剩余元素
    while (j <= high)
        b[k++] = a[j++];
    for (i = low, k = 0; i <= high; ++i)
        a[i] = b[k++];
    delete[] b;
}
void mergesort(int a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        mergesort(a, low, mid);
        mergesort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}
int main()
{
    int a[100];
    int n = 0;
    cout << "input n" << endl;
    cin >> n;
    cout << "input val" << endl;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    mergesort(a, 0, n-1);
    cout << "mergesort:" << endl;
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}