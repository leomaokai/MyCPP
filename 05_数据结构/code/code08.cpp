//code08.cpp
//分组背包
#include <iostream>
#include <string.h>
using namespace std;
const int maxn = 1000;
const int M = 100;
int dp[maxn]{};                   //dp[j]表示当前已放入容量为j的背包获得的最大价值
int w[M][M]{}, v[M][M]{}, c[M]{}; //价值,重量,个数
int n, W;                         //n表示n组物品,W表示背包的容量

//分组背包
void group_knapsack(const int &n, const int &W)
{
    for (int i = 1; i <= n; ++i)
        for (int j = W; j >= 0; --j)
            for (int k = 1; k <= c[i]; ++k)
                if (j >= w[i][k])
                    dp[j] = max(dp[j], dp[j - w[i][k]] + v[i][k]);
}
int main()
{
    cout << "input bag W" << endl;
    cin >> W;
    cout << "input n:" << endl;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cout << "input c" << endl;
        cin >> c[i];
        for (int j = 1; j <= c[i]; ++j)
            cin >> w[i][j] >> v[i][j];
    }
    group_knapsack(n, W);
    for (int i = 0; i < W; ++i)
        cout << dp[i] << " ";
    cout << endl;
    return 0;
}