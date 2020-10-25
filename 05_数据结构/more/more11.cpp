//树链剖分求LCA
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 1000;
int n, m;                                       //n个结点,m个查询
int head[maxn]{}, dist[maxn]{}, cnt;            //头结点,距离
int fa[maxn]{}, dep[maxn]{};                    //父亲,深度
int sizenode[maxn]{}, son[maxn]{}, top[maxn]{}; //子树结点数,重儿子,所在重链顶端结点
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
void dfs1(int u, int f) //求dep,fa,size,son,dist
{
    sizenode[u] = 1;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v == f) //父结点
            continue;
        dep[v] = dep[u] + 1;
        fa[v] = u;
        dist[v] = dist[u] + e[i].c;
        dfs1(v, u);
        sizenode[u] += sizenode[v];
        if (sizenode[v] > sizenode[son[u]])
            son[u] = v;
    }
}
void dfs2(int u) //求top
{
    if (u == son[fa[u]])
        top[u] = top[fa[u]];
    else
        top[u] = u;
    for (int i = head[u]; i; i = e[i].next)
    {
        int v = e[i].to;
        if (v != fa[u])
            dfs2(v);
    }
}
