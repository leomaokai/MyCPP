//graph08.cpp
//kurskal
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100;
int nodeset[maxn]; //集合号数组
int n, m;          //顶点数和边数
struct edge        //边集数组
{
    int u, v, w;
} e[maxn * maxn];
//优先级函数
bool comp(edge x, edge y)
{
    return x.w < y.w;
}
//初始化集合号数组
void init(int n)
{
    for (int i = 1; i <= n; ++i)
        nodeset[i] = i;
}
//合并1,复杂度较高
bool merge1(int a, int b)
{
    int p = nodeset[a];
    int q = nodeset[b];
    if (p == q)
        return false;
    for (int i = 1; i <= n; ++i) //检查所有的结点,把集合号是q的改为p
    {
        if (nodeset[i] == q)
            nodeset[i] = p;
    }
    return true;
}
//合并2,使用并查集
int find(int x) //找祖宗
{
    if (x != nodeset[x])
    {
        //把当前结点到其祖宗路径上的所有集合号改为祖宗集合号
        nodeset[x] = find(nodeset[x]);
    }
    return nodeset[x]; //返回其祖宗的集合号
}
bool merge2(int a, int b)
{
    int p = find(a);
    int q = find(b);
    if (p == q)
        return 0;
    if (p > q)
        nodeset[p] = q; //小的集合号赋值给大的集合号
    else
        nodeset[q] = p;
}
//算法
int kruskal(int n)
{
    int ans = 0;
    for (int i = 0; i < m; ++i) //merge1 O(n^2) merge2 O(nlogn)
    {
        if (merge2(e[i].u, e[i].v))
        {
            ans += e[i].w;
            --n;
            if (n == 1)
                return ans; //返回权值之和
        }
    }
    return 0;
}
int main()
{
    cout << "input vexs and edges:" << endl;
    cin >> n >> m;
    init(n);
    cout << "input u  v  and w:" << endl;
    for (int i = 1; i <= m; ++i)
        cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e, e + m, comp); //O(eloge)
    int ans = kruskal(n);
    cout << "the cost: " << ans << endl;
    return 0;
}