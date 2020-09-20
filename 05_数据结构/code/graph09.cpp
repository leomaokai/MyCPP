//graph09.cpp
//拓扑排序
//邻接表求顶点,逆邻接表求顶点入度
#include <iostream>
#include <string.h>
#include <stack>
#include <memory>
using namespace std;
const int maxn = 100; //顶点数最大值
int indegree[maxn];   //入度数组
typedef string vextype;
//邻接点类型
typedef struct node
{
    int v;             //邻接点下标
    struct node *next; //指向下一个邻接点
} node;
//顶点类型
typedef struct vexnode
{
    vextype data;       //顶点数据类型
    struct node *first; //指向第一个邻接点
} vexnode;
//邻接表和逆邻接表
typedef struct
{
    vexnode vex[maxn];   //邻接表
    vexnode revex[maxn]; //逆邻接表
    int vexnum, edgenum; //顶点数和边数
} graph;
//寻找顶点的位置下标
int locatevex(graph &g, vextype x)
{
    for (int i = 0; i < g.vexnum; ++i)
    {
        if (x == g.vex[i].data)
            return i;
    }
    return -1;
}
//插入一条边
void insertedge(graph &g, int i, int j)
{
    //创建邻接表结点
    node *n1 = new node();
    n1->v = j;
    n1->next = g.vex[i].first;
    g.vex[i].first = n1;
    //创建逆邻接表结点
    node *n2 = new node();
    n2->v = i;
    n2->next = g.revex[j].first;
    g.revex[j].first = n2;
}
//创建邻接表
void creategraph(graph &g)
{
    cout << "input vexnum and edgenum" << endl;
    cin >> g.vexnum >> g.edgenum;
    cout << "input vex" << endl;
    for (int i = 0; i < g.vexnum; ++i)
    {
        cin >> g.vex[i].data;
        g.revex[i].data = g.vex[i].data;
        g.vex[i].first = nullptr;
        g.revex[i].first = nullptr;
    }
    cout << "input vex and vex with a edge" << endl;
    vextype u, v;
    int i, j;
    while (g.edgenum--)
    {
        cin >> u >> v;
        i = locatevex(g, u);
        j = locatevex(g, v);
        if (i != -1 && j != -1)
            insertedge(g, i, j);
        else
        {
            cout << "input error" << endl;
            g.edgenum++;
        }
    }
}
//统计所有顶点的入度
void findindegree(graph &g)
{
    int count = 0;
    for (int i = 0; i < g.vexnum; ++i)
    {
        node *p = g.revex[i].first;
        while (p)
        {
            p = p->next;
            ++count;
        }
        indegree[i] = count;
    }
    cout << "the indegree:" << endl;
    for (int i = 0; i < g.vexnum; ++i)
        cout << indegree[i] << "\t";
    cout << endl;
}
//拓扑排序
void toposort(graph &g)
{
    int topo[g.vexnum]; //拓扑序列
    stack<int> s;       //创建一个栈
    findindegree(g);    //获得入度数组
    for (int i = 0; i < g.vexnum; ++i)
    {
        if (indegree[i] == 0) //入度为0入栈
            s.push(i);
    }
    int num = 0;
    while (!s.empty()) //栈非空
    {
        int n = s.top(); //获得栈顶的顶点
        s.pop();         //出栈
        topo[num] = n;   //将n保存到拓扑序列中
        ++num;
        //将n顶点邻接顶点的入度减一
        node *p = g.vex[n].first;
        while (p != nullptr)
        {
            int k = p->v;
            --indegree[k];
            if (indegree[k] == 0)
                s.push(k);
            p = p->next;
        }
    }
    if (num < g.vexnum)
        cout << "the graph is loop" << endl;
    else
    {
        for (int i = 0; i < g.vexnum; ++i)
            cout << topo[i] << "\t";
        cout << endl;
    }
}
int main()
{
    graph g;
    creategraph(g);
    toposort(g);
    return 0;
}