//LCA树上倍增法
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
const int maxn = 1000;
int n, m, k, F[maxn][20];
int head[maxn]{}, dist[maxn]{}, deep[maxn]{}, cnt = 0;
struct edge
{
    int to, c, next;
} e[maxn << 1];
void add(int u, int v, int w)
{
    e[++cnt].to = v;
    e[cnt].c = w;
    e[cnt].next = head[u];
    head[u] = cnt;
}
void dfs(int u)
{
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v == F[u][0])
            continue;
        deep[v] = deep[u] + 1;      //深度
        dist[v] = dist[u] + e[i].c; //距离
        F[v][0] = u;
        dfs(v);
    }
}
void createST()
{
    for (int j = 1; j <= k; ++j)
        for (int i = 1; i <= m; ++i)
            F[i][j] = F[F[i][j - 1]][j - 1];
}
int lca_st_query(int x, int y)
{
    if (deep[x] > deep[y]) //x的深度小于等于y的深度
        swap(x, y);
    for (int i = k; i >= 0; --i) //y向上走到与x同一深度
    {
        if (deep[F[y][i]] >= deep[x])
            y = F[y][i];
    }
    if (x == y)
        return x;
    for (int i = k; i >= 0; --i) //刚开始跳很多
        if (F[x][i] != F[y][i])
            x = F[x][i], y = F[y][i];
    return F[x][0]; //此时x结点的父亲即使LCA
}
int main()
{
    cin >> n >> m;
    k = log2(n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        add(u, v, w);
        add(v, u, w);
    }
    deep[1] = 1;
    dfs(1);
    createST();
    int x = 0, y = 0, lca = 0;
    for (int i = 1; i <= m; ++i)
    {
        cin >> x >> y;
        lca = lca_st_query(x, y);
        cout << dist[x] + dist[y] - 2 * dist[lca] << endl;
    }
    return 0;
}