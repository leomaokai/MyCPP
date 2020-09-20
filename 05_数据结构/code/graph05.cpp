//graph05.cpp
//dijkstra
#include <iostream>
using namespace std;
const int inf = 100;     //假设无穷远
const int maxvnum = 100; //顶点数最大值
typedef struct
{
    char vex[maxvnum];          //顶点数组
    int edge[maxvnum][maxvnum]; //邻接矩阵
    int vexnum, edgenum;        //顶点数,边数
} AMGraph;
//查找顶点在数组中的下标
int locatevex(AMGraph &G, char &x)
{
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (x == G.vex[i])
            return i;
    }
    return -1;
}
//创建邻接矩阵
void creategraph(AMGraph &G)
{
    char u, v; //u,v两个顶点
    cout << "vex number:" << endl;
    cin >> G.vexnum;
    cout << "edge number:" << endl;
    cin >> G.edgenum;
    cout << "vex information:" << endl;
    for (int i = 0; i < G.vexnum; ++i)
        cin >> G.vex[i];
    for (int i = 0; i < G.vexnum; ++i) //初始化邻接矩阵
    {
        for (int j = 0; j < G.vexnum; ++j)
        {
            if(i==j)
                G.edge[i][j]=0;
            else
                G.edge[i][j] = inf;
        }
    }
    int w = 0;
    cout << "vex and vex and weigth:" << endl;
    while (G.edgenum--)
    {
        cin >> u >> v >> w;
        int i = locatevex(G, u); //查找u顶点的下标
        int j = locatevex(G, v); //查找v顶点的下标
        if (i != -1 && j != -1)
        {
            G.edge[i][j] = G.edge[j][i] = w;
        }
        else
        {
            cout << "input error" << endl;
            G.edgenum++; //本次输入不算
        }
    }
}
//打印邻接矩阵
void print(AMGraph &G)
{
    cout << "output the graph" << endl;
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
            cout << G.edge[i][j] << " ";
        cout << endl;
    }
}
//dijkstra
void dijkstra(AMGraph &G, int u)
{
    int dist[G.vexnum];
    int p[G.vexnum];
    int flag[G.vexnum];
    for (int i = 0; i < G.vexnum; ++i)
    {
        dist[i] = G.edge[u][i]; //初始化源点u到其它各个顶点的最短路径长度
        flag[i] = 0;
        if (dist[i] == inf)
            p[i] = -1; //距离无穷大,u,i不相邻
        else
            p[i] = u; //u,i相邻,i顶点的前驱p[i]=u
    }
    dist[u] = 0;
    flag[u] = 1; //将源点u放入S集合
    for (int i = 0; i < G.vexnum; ++i)
    {
        int temp = inf, t;
        for (int j = 0; j < G.vexnum; ++j) //在V-S集合中寻找距离u最近的顶点
        {
            if (!flag[j] && dist[j] < temp)
            {
                t = j;
                temp = dist[j];
            }
        }
        if (t == u)
        {
            cout<<"error"<<endl;
            return;
        }
        flag[t] = 1;                    //将t结点加入S集合
        for (int j = 0; j < G.vexnum; ++j) //更新与t相邻接的顶点到源点u的距离
        {
            if (!flag[j] && G.edge[t][j] < inf)
            {
                if (dist[j] > (dist[t] + G.edge[t][j]))
                {
                    dist[j] = dist[t] + G.edge[t][j]; //更新dist[j]
                    p[j] = t;                         //更新j的前驱顶点
                }
            }
        }
    }
    for (int i = 0; i < G.vexnum; ++i)
    {
        cout << dist[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < G.vexnum; ++i)
    {
        cout << p[i] << " ";
    }
    cout << endl;
}
int main()
{
    AMGraph G;
    creategraph(G);
    print(G);
    cout<<endl;
    dijkstra(G, 0);
    return 0;
}