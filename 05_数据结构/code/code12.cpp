//code12.cpp
//树形DP,最大独立集
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 5000;
int val[N], dp[N][2], fa[N], n; //结点值,规划数组,父亲数组,结点数
vector<int> E[N];               //记录孩子
void dfs(int u)
{
    dp[u][0] = 0;
    dp[u][1] = val[u];
    for (int i = 0; i < E[u].size(); ++i)
    {
        int v = E[u][i];
        dfs(v);
        dp[u][0] += max(dp[v][1], dp[v][0]);
        dp[u][1] += dp[v][0];
    }
}

int main()
{
    while (cin >> n)
    {
        for (int i = 1; i <= n; ++i)
        {
            cin >> val[i];
            E[i].clear();
            fa[i] = -1;
        }
        while (1)
        {
            int a, b; //a为孩子,b为父亲
            cin >> a >> b;
            if (a == 0 && b == 0)
                break;
            E[b].push_back(a);
            fa[a] = b;
        }
        int root = 1;
        while (fa[root] != -1)
            root = fa[root];
        dfs(root);
        cout << max(dp[root][1], dp[root][0]) << endl;
    }
    return 0;
}