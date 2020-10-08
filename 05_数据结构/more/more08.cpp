//RMQ算法求LCA
#include <iostream>
#include <math.h>
#include <algorithm>
using namespace std;
const int maxn = 1000;
int n, m, tot, F[maxn][20];
//结点数组,距离,位置,顺序,深度
int head[maxn], dist[maxn], pos[maxn], seq[maxn << 1], dep[maxn << 1], cnt;
bool vis[maxn]; //是否访问
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
void dfs(int u, int d)
{
    vis[u] = true;
    pos[u] = ++tot; //u首次出现的下标,结点转为下标
    seq[tot] = u;   //dfs遍历序列,下标转为结点
    dep[tot] = d;   //深度
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to, w = e[i].c;
        if (vis[v]) //邻接点已经访问过
            continue;
        dist[v] = dist[u] + w;
        dfs(v, d + 1);
        seq[++tot] = u; //返回时再次记录位置
        dep[tot] = d;   //深度
    }
}
//ST表记录了区间内深度最小结点的下标
void createST()
{
    for (int i = 1; i <= tot; ++i)
        F[i][0] = i; //记录下标
    int k = log2(tot);
    for (int j = 1; j <= k; ++j)
    {
        for (int i = 1; i <= tot - (1 << j) + 1; ++i)
        {
            if (dep[F[i][j - 1]] < dep[F[i + (1 << (j - 1))][j - 1]])
                F[i][j] = F[i][j - 1];
            else
                F[i][j] = F[i + (1 << (j - 1))][j - 1];
        }
    }
}
int RMQquery(int l, int r) //求区间内的最值
{
    int k = log2(r - l + 1);
    if (dep[F[l][k]] < dep[F[r - (1 << k) + 1][k]])
        return F[l][k];
    else
        return F[r - (1 << k) + 1][k];
}
int LCA(int x, int y)
{
    int l = pos[x], r = pos[y]; //读取第一次出现的下标
    if (l > r)
        swap(l, r);
    return seq[RMQquery(l, r)]; //返回结点
}
int main()
{
    return 0;
}