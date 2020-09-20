//graph07.cpp
//prim最小生成树
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
//prim
void prim(AMGraph &G, int u0)
{
    bool s[G.vexnum];
    int lowcost[G.vexnum], closest[G.vexnum];
    s[u0] = true;                      //u0加入集合u
    for (int i = 0; i < G.vexnum; ++i) //初始化lowcost和closest
    {
        if (i != u0)
        {
            lowcost[i] = G.edge[u0][i];
            closest[i] = u0;
            s[i] = false;
        }
        else
        {
            lowcost[i] = 0;
            closest[i] = 0;
        }
    }
    for (int i = 0; i < G.vexnum; ++i)
    {
        int temp = inf;
        int t = u0;
        for (int j = 0; j < G.vexnum; ++j) //在集合V-u中寻找距离集合u最近的顶点t
        {
            if ((!s[j]) && (lowcost[j] < temp))
            {
                t = j;
                temp = lowcost[j];
            }
        }
        if (t == u0)
            break;
        s[t] = true;                       //将顶点t加入集合u
        for (int j = 0; j < G.vexnum; ++j) //更新t邻接顶点的lowcost和closest
        {
            if ((!s[j]) && (G.edge[t][j] < lowcost[j]))
            {
                lowcost[j] = G.edge[t][j];
                closest[j] = t;
            }
        }
    }
    cout << "lowcost: " << endl;
    for (int i = 0; i < G.vexnum; ++i)
    {
        cout << lowcost[i] << " ";
    }
    cout << endl;
    cout << "closest: " << endl;
    for (int i = 0; i < G.vexnum; ++i)
    {
        cout << closest[i] << " ";
    }
    cout << endl;
    int sumcost = 0;
    for (int i = 0; i < G.vexnum; ++i)
    {
        sumcost += lowcost[i];
    }
    cout << "sumcost: " << sumcost << endl;
}
int main()
{
    AMGraph G;
    creategraph(G);
    print(G);
    cout << endl;
    prim(G, 0);
    return 0;
}