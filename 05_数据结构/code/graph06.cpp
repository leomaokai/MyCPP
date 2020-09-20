//graph05.cpp
//floyd
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
            if (i == j)
                G.edge[i][j] = 0;
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
//floyd
void floyd(AMGraph &G)
{
    int dist[G.vexnum][G.vexnum]; //记录顶点间距离数组
    int p[G.vexnum][G.vexnum];    //记录前驱顶点数组
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
        {
            dist[i][j] = G.edge[i][j];
            if (dist[i][j] < inf && i != j)
                p[i][j] = i; //如果i和j之间有弧,则将j的前驱置位i
            else
                p[i][j] = -1; //如果i和j之间无弧,则将j的前驱置为-1
        }
    }
    for (int k = 0; k < G.vexnum; ++k)
    {
        for (int i = 0; i < G.vexnum; ++i)
        {
            for (int j = 0; j < G.vexnum; ++j)
            {
                //i经k到j的最短路径
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j]; //更新dist[i][j]
                    p[i][j] = p[k][j];                    //更新j的前驱为k
                }
            }
        }
    }
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
            cout << dist[i][j] << " ";
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < G.vexnum; ++i)
    {
        for (int j = 0; j < G.vexnum; ++j)
            cout << p[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}
int main()
{
    AMGraph G;
    creategraph(G);
    print(G);
    cout << endl;
    floyd(G);
    return 0;
}
