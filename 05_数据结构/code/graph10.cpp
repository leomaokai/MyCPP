//graph10.cpp
//拓扑排序邻接矩阵
#include <iostream>
#include <string.h>
#include <stack>
using namespace std;
const int maxn = 100;
int map[maxn][maxn], indegree[maxn], topo[maxn];
int n;
stack<int> s;
void toposort()
{
    int cnt = 0;
    for (int i = 1; i <= n; ++i)
        if (indegree[i] == 0)
            s.push(i);
    while (!s.empty())
    {
        int n = s.top();
        s.pop();
        topo[++cnt] = n;
        for (int i = 1; i <= n; ++i)
        {
            if (map[n][i] == 1)
                --indegree[i];
            if (indegree[i] == 0)
                s.push(i);
        }
    }
    for (int i = 1; i <= n; ++i)
        cout << topo[i] << " ";
    cout << endl;
}
int main()
{
    cin >> n >> m;
    memset(map, 0, sizeof(map));
    memset(indegree, 0, sizeof(indegree));
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        while (cin >> u >> v)
        {
            map[u][v] = 1;
            indegree[v]++;//在输入时统计入度
        }
    }
    toposort();
    return 0;
}