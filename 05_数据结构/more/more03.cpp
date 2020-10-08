//树状数组
#include <iostream>
#include <string.h>
using namespace std;
const int maxn = 1000;
int n, a[maxn], c[maxn], s[maxn];

int lowbit(int i)
{
    return (-i) & i;
}
void add(int i, int z)
{
    for (; i <= n; i += lowbit(i))
        c[i] += z;
}
int sum(int i)
{
    int s = 0;
    for (; i > 0; i -= lowbit(i))
        s += c[i];
    return s;
}
int sum(int i, int j)
{
    return sum(j) - sum(i - 1);
}
int main()
{
    memset(c, 0, sizeof(c));
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        add(i, a[i]);
    }
    cout << sum(5) << endl;
    cout << sum(2, 6) << endl;
    return 0;
}