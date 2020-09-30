//sort05.cpp
//采用一维辅助数组的基数排序
#include <iostream>
using namespace std;

//求数据的最大位数
int maxbit(const int *a, const int &n)
{
    int d = 1; //统计最大的位数
    int p = 10;
    for (int i = 0; i < n; ++i)
    {
        while (a[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;
}
//基数排序
void radixsort(int *a, const int &n)
{
    int d = maxbit(a, n);
    5 cout << "the maxbit:" << d << endl;
    int *temp = new int[n]();   //临时辅助数组
    int *count = new int[10](); //计数器数组
    int radix = 1;
    for (int i = 1; i <= d; ++i)
    {
        int j = 0, k = 0;
        for (j = 0; j < 10; ++j)
            count[j] = 0;
        for (j = 0; j < n; ++j) //统计每一位的个数
        {
            k = (a[j] / radix) % 10;
            count[k]++;
        }
        for (j = 1; j < 10; ++j) //计数器数组累加
            count[j] += count[j - 1];
        for (j = n - 1; j >= 0; --j) //将数据映射到临时数组中
        {
            k = (a[j] / radix) % 10;
            temp[--count[k]] = a[j];
        }
        for (j = 0; j < n; ++j) //将临时数组的内容复制到a中
            a[j] = temp[j];
        cout << "the sort " << i << endl;
        for (j = 0; j < n; ++j)
            cout << a[j] << " ";
        cout << endl;
        radix *= 10;
    }
    delete[] temp;
    delete[] count;
}
int main()
{
    int n = 0;
    cout << "input n" << endl;
    cin >> n;
    int *a = new int[n]();
    cout << "input val" << endl;
    for (int i = 0; i < n; ++i)
        cin >> a[i];
    radixsort(a, n);
    delete[] a;
    return 0;
}