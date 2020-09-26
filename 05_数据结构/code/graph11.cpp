//graph11.cpp
//关键路径
#include <iostream>
#include <string.h>
#include <stack>
using namespace std;
const int maxn = 100;

typedef string vextype; //顶点数据类型
typedef struct node     //邻接点类型
{
    int v;
    int w;
    struct node *next;
} node;
typedef struct vexnode //顶点类型
{
    vextype data;
    struct node *first;
} vexnode;
typedef struct graph //邻接表类型
{
    vexnode vex[maxn];
    vexnode revex[maxn];
    int vexnum, edgenum;
} graph;
int locatevex(graph &g, vextype x)
{
    for (int i = 0; i < g.vexnum; ++i)
        if (x == g.vex[i].data)
            return i;
    return -1;
}
void insertedge(graph &g, int i, int j, int weight)
{
    node *n1 = new node();
    n1->v = j;
    n1->w = weight;
    n1->next = g.vex[i].first;
    g.vex[i].first = n1;
    node *n2 = new node();
    n2->v = i;
    n2->w = weight;
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
    int i, j, w;
    while (g.edgenum--)
    {
        cin >> u >> v >> w;
        i = locatevex(g, u);
        j = locatevex(g, v);
        if (i != -1 && j != -1)
        {
            insertedge(g, i, j, w);
        }
        else
        {
            cout << "input error" << endl;
            g.edgenum++;
        }
    }
}
//统计所有顶点的入度
int indegree[maxn]; //入度数组
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
int topo[maxn]; //拓扑序列
int toposort(graph &g)
{
    stack<int> s;    //创建一个栈
    findindegree(g); //获得入度数组
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
    {
        cout << "the graph is loop" << endl;
        return -1;
    }
    else
    {
        for (int i = 0; i < g.vexnum; ++i)
            cout << topo[i] << "\t";
        cout << endl;
        return 1;
    }
}
//关键路径
int ve[maxn]; //事件最早发生时间
int vl[maxn]; //事件最迟发生时间
bool criticalpath(graph &g)
{
    if (toposort(g) == -1)
        return false;
    for (int i = 0; i < g.vexnum; ++i) //初始化每个事件的最早发生时间
        ve[i] = 0;
    for (int i = 0; i < g.vexnum; ++i) //按拓扑排序求每个事件的最早发生时间
    {
        int k = topo[i];          //拓扑序列中的第一个顶点k
        node *p = g.vex[k].first; //p指向顶点k的第一个邻接点
        while (p != nullptr)      //依次更新其邻接点的最早发生时间
        {
            int j = p->v;
            if (ve[j] < ve[k] + p->w)
                ve[j] = ve[k] + p->w; //ve[j]为弧尾ve加边权值的最大值
            p = p->next;
        }
    }
    for (int i = 0; i < g.vexnum; ++i) //初始化每个事件的最迟发生时间
        vl[i] = ve[g.vexnum - 1];
    for (int i = g.vexnum - 1; i >= 0; --i)
    {
        int k = topo[i];
        node *p = g.vex[k].first;
        while (p != nullptr)
        {
            int j = p->v;
            if (vl[k] > vl[j] - p->w)
                vl[k] = vl[j] - p->w; //vl[k]为弧头vl减边权值的最小值
            p = p->next;
        }
    }
    cout << "the ve and vl:" << endl;
    for (int i = 0; i < g.vexnum; ++i)
        cout << ve[i] << "\t" << vl[i] << endl;
    cout << endl;

    cout << "the criticalpath :" << endl;
    for (int i = 0; i < g.vexnum; ++i)
    {
        node *p = g.vex[i].first;
        while (p != nullptr)
        {
            int j = p->v;
            int e = ve[i];        //活动的最早开始时间为弧尾的最早开始时间
            int l = vl[j] - p->w; //活动的最迟开始时间为弧头最迟开始时间减边值
            if (e == l)
                cout << "<" << g.vex[i].data << "," << g.vex[j].data << ">  ";
            p = p->next;
        }
    }
    cout << endl;
    cout << "the longest :" << endl;
    cout << vl[topo[g.vexnum - 1]] << endl;
    return true;
}
int main()
{
    graph g;
    creategraph(g);
    if (criticalpath(g))
        cout << "ok" << endl;
    else
        cout << "no" << endl;
    return 0;
}