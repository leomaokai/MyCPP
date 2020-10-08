//ST表
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;
const int maxn = 100;
int n, F[maxn][maxn]{}, a[maxn]{};
void createST()
{
    for (int i = 1; i <= n; ++i)
        F[i][0] = a[i];
    int k = log2(n);
    for (int j = 1; j <= k; ++j)
        for (int i = 1; i <= n - (1 << j) + 1; ++i)
            F[i][j] = max(F[i][j - 1], F[i + (1 << (j - 1))][j - 1]);
}
int queryST(int l, int r) //求区间[l,r]的最值
{
    int k = log2(r - l + 1);
    return max(F[l][k], F[r - (1 << k) + 1][k]);
}
int print()
{
    int k = log2(n);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 0; j <= k; ++j)
            cout << F[i][j] << '\t';
        cout << endl;
    }
}
int main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    createST();
    print();
    cout << "query l r" << endl;
    int l = 0, r = 0;
    cin >> l >> r;
    cout << queryST(l, r) << endl;
    return 0;
}