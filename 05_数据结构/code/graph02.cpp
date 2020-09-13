//graph02.cpp
//有向图邻接表
#include<iostream>
using namespace std;
const int maxvnum=100;//顶点数最大值

//邻接点结构体
typedef struct listnode
{
    int v;//邻接点下标
    struct listnode *next;//指向下一个邻接点
}listnode;
//顶点结构体
typedef struct vexnode
{
    char data;//顶点数据类型
    struct listnode *first;//指向第一个邻接点
}vexnode;
//邻接表
typedef struct
{
    vexnode vex[maxvnum];//顶点数组
    int vexnum,edgenum;//顶点数和边数
}graph;
//查找顶点下标
int locatevex(graph &G,char &x)
{
    for(int i=0;i<G.vexnum;++i)
    {
        if(x==G.vex[i].data)
            return i;
    }
    return -1;
}
//插入一条边
void insertedge(graph &g,int &i,int &j)
{
    listnode *lnode=new listnode();
    lnode->v=j;
    lnode->next=g.vex[i].first;//头插法
    g.vex[i].first=lnode;
}
//创建邻接表
void creategraph(graph &g)
{
    cout<<"vexnumber and edgenumber:"<<endl;
    cin>>g.vexnum>>g.edgenum;
    cout<<"vex information:"<<endl;
    for(int i=0;i<g.vexnum;++i)
        cin>>g.vex[i].data;
    for(int i=0;i<g.vexnum;++i)
        g.vex[i].first=nullptr;
    cout<<"input two vex:"<<endl;
    char u,v;
    int i,j;
    while(g.edgenum--)
    {
        cin>>u>>v;
        i=locatevex(g,u);//查找顶点u的下标
        j=locatevex(g,v);//查找顶点v的下标
        if(i!=-1 && j!=-1)
            insertedge(g,i,j);
        else
        {
            cout<<"input error"<<endl;
            g.edgenum++;//本次输入无效 
        }
    }
}
void print(graph &g)
{
    for(int i=0;i<g.vexnum;++i)
    {
        cout<<g.vex[i].data<<": ";
        listnode *tmp=g.vex[i].first;
        while(tmp!=nullptr)
        {
            cout<<tmp->v<<" ";
            tmp=tmp->next;
        }
        cout<<endl;
    }
}
int main()
{
    graph g;
    creategraph(g);
    print(g);
    return 0;
}