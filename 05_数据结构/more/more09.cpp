//tarjan算法求LCA
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
const int maxn=1000;
int n,m;
int head[maxn],dis[maxn],cnt;//头结点,距离
int fa[maxn],ans[maxn];
bool vis[maxn];
vector<int> query[maxn],query_id[maxn];
struct edge
{
    int to,c,next;
}e[maxn<<1];
void add(int u,int v,int w)
{
    e[++cnt].to=v;
    e[cnt].c=w;
    e[cnt].next=head[u];
    head[u]=cnt;
}
void add_query(int x,int y,int id)
{
    query[x].push_back(y);
    query_id[x].push_back(id);
    query[y].push_back(x);
    query_id[y].push_back(id);
}
int find(int x)//并查集找祖宗
{
    if(x==fa[x])
        return x;
    return fa[x]=find(fa[x]);
}
void tarjan(int u)
{
    vis[u]=1;
    for(int i=head[u];i;i=e[i].next)
    {
        int v=e[i].to,w=e[i].c;
        if(vis[v])
            continue;
        dis[v]=dis[u]+w;
        tarjan(v);
        fa[v]=u;//返回时更新
    }
    for(int i=0;i<query[u].size();++i)//检查是否有与u相关的查询
    {
        int v=query[u][i];
        int id=query_id[u][i];
        if(vis[v])
        {
            int lca=find(v);//得到最近公共祖先
            ans[id]=dis[u]+dis[v]-2*dis[lca];//两结点距离
        }
    }
}
int main()
{
    return 0;
}