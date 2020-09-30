//sort03.cpp
//堆排序,n为结点数,堆顶点下标从1开始
#include <iostream>
#include<ctime>
using namespace std;
void sink(int r[], int k, int n)
{
    while (2 * k <= n)
    {
        int j = 2 * k;
        if (j < n && r[j] < r[j + 1])
            j++;
        if (r[k] >= r[j])
            break;
        else
            swap(r[k], r[j]);
        k = j;
    }
}
void createheap(int r[], int n)
{
    for (int i = n / 2; i > 0; --i)
        sink(r, i, n);
}
void heapsort(int r[], int n)
{
    createheap(r, n);
    while (n > 0)
    {
        swap(r[1], r[n--]);
        sink(r, 1, n);
    }
}
int main()
{
    srand(time(0));
    int r[20]{};
    for (int i = 1; i <= 10; ++i)
        r[i] = rand() % 100 + 1;
    heapsort(r, 10);
    for (int i = 1; i <= 10; ++i)
        cout << r[i] << " ";
    cout << endl;
    return 0;
}