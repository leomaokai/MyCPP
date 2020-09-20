//graph04.cpp
//tarjan_桥
#include <iostream>
#include <string.h>
using namespace std;
//链式前向星
const int maxn = 100; //最多顶点数
//顶点数,边数,边数组下标,头顶点数组
int n, m, cnt, head[maxn];

struct edge
{
    int to, next;
} edge[maxn * maxn]; //边集数组

void add(int u, int v) //插入邻接点
{
    edge[++cnt].next = head[u];
    edge[cnt].to = v;
    head[u] = cnt;
}
int low[maxn], dfn[maxn], num;
void tarjan(int u, int fa)
{
    dfn[u] = low[u] = ++num;
    for (int i = head[u]; i; i = edge[i].next)
    {
        int v = edge[i].to;
        if (v == fa)
            continue;
        if (!dfn[v])
        {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
            if (low[v] > dfn[u])
                cout << u << "--" << v << "是桥" << endl;
        }
        else
            low[u] = min(low[u], dfn[v]);
    }
}
void init() //初始化
{
    memset(head, 0, sizeof(head));
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    cnt = num = 0;
}
int main()
{
    cin >> n >> m;
    init();
    int u, v;
    while (m--)
    {
        cin >> u >> v;
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; ++i) //防止不连通
    {
        if (!dfn[i])
            tarjan(1, 0);
    }
    return 0;
}