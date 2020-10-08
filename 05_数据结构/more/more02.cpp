//优先级队列
#include <iostream>
using namespace std;
const int maxn = 1000;
int r[maxn]{};
void sink(int k, const int &n) //k为插入位置,n为结点数,下沉
{
    while (2 * k < n) //如果有左孩子,则k的左孩子为2*k,右孩子为2*k+1
    {
        int j = 2 * k;
        if (j < n  && r[j] < r[j + 1]) //比较左右孩子的大小
            j++;
        if (r[k] >= r[j]) //以满足大顶堆
            break;
        else
            swap(r[k], r[j]); //否则交换位置
        k = j;
    }
}
void pop(int &n) //出队
{
    cout << r[1] << endl; //输出堆顶
    r[1] = r[n--];        //最后一个结点代替堆顶
    sink(1, n);           //下沉操作
}
void swim(int k) //上浮
{
    while (k > 1 && r[k] > r[k / 2]) //如果大于双亲
    {
        swap(r[k], r[k / 2]);
        k = k / 2;
    }
}
void push(int &n, const int &x) //入队
{
    r[++n] = x;
    swim(n); //最后一个结点上浮
}
void creatheap(const int &n) //构建堆
{
    for (int i = n / 2; i > 0; --i)
        sink(i, n);
}
int main()
{
    int n = 0;
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> r[i];
    creatheap(n);
    push(n, 30);
    for (int i = 1; i <= n; ++i)
        cout << r[i] << " ";
    cout << endl;
    for (int i = 0; i < 5; ++i)
        pop(n);
    for (int i = 1; i <= n; ++i)
        cout << r[i] << " ";
    cout << endl;
    return 0;
}