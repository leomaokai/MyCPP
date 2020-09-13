//tree04.cpp
/*
通过根结点求两个结点之间的距离
两个结点之间的距离=左结点到父结点的距离*2+右结点到根结点的距离
*/
#include <iostream>
using namespace std;
const int maxn = 100;
//双亲表示法
int father[maxn], deep[maxn], width[maxn]; //父亲,深度,宽度
int n, maxd = 1, maxw = 0;

int lca(int u, int v)
{
    if (deep[u] < deep[v])
        swap(u, v);
    while (deep[u] != deep[v])
    {
        u = father[u];
    }
    if (u == v)
        return v;
    while (father[u] != father[v])
    {
        u = father[u];
        v = father[v];
    }
    return father[u];
}
int main()
{
    int u, v;
    cin >> n;
    deep[1] = 1;
    width[1] = 1;
    for (int i = 1; i < n; ++i)
    {
        cin >> u >> v;
        father[v] = u;
        deep[v] = deep[u] + 1;
        width[deep[v]]++;
        if (maxd < deep[v])
            maxd = deep[v];
    }
    for (int i = 1; i <= maxd; ++i)
    {
        if (maxw < width[i])
            maxw = width[i];
    }
    cout << maxd << endl;
    cout << maxw << endl;
    cin >> u >> v;
    cout << (deep[u] - deep[lca(u, v)]) * 2 + deep[v] - deep[lca(u, v)] << endl;
    return 0;
}