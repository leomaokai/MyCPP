//sort01.cpp
//快速排序
#include <iostream>
using namespace std;
//划分函数1 每次交换都是与pivot交换
int partition1(int r[], int low, int high)
{
    int i = low, j = high, pivot = r[low];
    while (i < j)
    {
        while (i < j && r[j] > pivot) //从右向左扫描
            j--;
        if (i < j)
            swap(r[i++], r[j]);
        while (i < j && r[i] <= pivot) //从左向右扫描
            i++;
        if (i < j)
            swap(r[i], r[j--]);
    }
    return i;
}
//划分函数2 优化减少交换次数
int partition2(int r[], int low, int high)
{
    int i = low, j = high, pivot = r[low];
    while (i < j)
    {
        while (i < j && r[j] > pivot) //从右向左扫描
            j--;
        while (i < j && r[i] <= pivot) //从左向右扫描
            i++;
        if (i < j)
            swap(r[i++], r[j--]);
    }
    if (r[i] > pivot)
    {
        swap(r[i - 1], r[low]);
        return i - 1;
    }
    swap(r[i], r[low]);
    return i;
}
void quicksort(int r[], int low, int high)
{
    int mid = 0;
    if (low < high)
    {
        mid = partition1(r, low, high); //基准位置
        quicksort(r, low, mid - 1);     //左序列递归快排
        quicksort(r, mid + 1, high);    //右序列递归快排
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
    cout << endl;
    quicksort(a, 0, n - 1);
    cout << "quicksort:" << endl;
    for (int i = 0; i < n; ++i)
        cout << a[i] << " ";
    cout << endl;
    return 0;
}