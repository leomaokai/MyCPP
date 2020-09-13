//graph03.cpp
//链式前向星
#include <iostream>
#include <string.h>
using namespace std;
const int maxn = 100;  //最大顶点数
const int maxe = 1000; //最多边数
int n, m, cnt;
int head[maxn]; //头节点数组,数组标号为顶点,数组值为边的下标

//to表示顶点编号,w为权值,next为另一条边的下标
struct node
{
    int to, w, next;
} edge[maxe]; //边集数组


//u --w-> v
void add(int u, int v, int w)
{
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u]; //类似于头插法
    head[u] = cnt++;
}
void printg()
{
    for(int u=1;u<=n;++u)
    {
        cout<<u<<" ";
        for(int i=head[u];i!=-1;i=edge[i].next)//i为边的下标
            cout<<"--> "<<edge[i].to<<" "<<edge[i].w<<" "<<edge[i].next<<" ";
        cout<<endl;
    }
}
int main()
{
    //n为结点数,m为边数
    cin >> n >> m;
    cnt = 0;
    memset(head, -1, sizeof(head));
    int u, v, w;
    for (int i = 1; i <= m; ++i)
    {
        //输入一个顶点和其连接的顶点以及其权值
        cin >> u >> v >> w;
        //无向图一次添加两条边,有向图一次添加一条边
        add(u, v, w);
        add(v, u, w);
    }
    printg();
    return 0;
}
