//graph01.cpp
//邻接矩阵创建无向图
#include <iostream>
using namespace std;

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
    cin >> G.edgenum;
    cout << "edge number:" << endl;
    cin >> G.edgenum;
    cout << "vex information:" << endl;
    for (int i = 0; i < G.vexnum; ++i)
        cin >> G.vex[i];
    for (int i = 0; i < G.vexnum; ++i) //初始化邻接矩阵
    {
        for (int j = 0; j < G.vexnum; ++j)
            G.edge[i][j] = 0;
    }
    cout << "vex and vex:" << endl;
    while (G.edgenum--)
    {
        cin >> u >> v;
        int i = locatevex(G, u); //查找u顶点的下标
        int j = locatevex(G, v); //查找v顶点的下标
        if (i != -1 && j != -1)
        {
            G.edge[i][j] = G.edge[j][i] = 1;
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

int main()
{
    AMGraph G;
    creategraph(G);
    print(G);
    return 0;
}