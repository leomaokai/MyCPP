//并查集
#include <iostream>
using namespace std;
const int N = 100;
int father[N]{}; //集合号数组
int n, m;
void init()
{
    for (int i = 1; i <= n; ++i)
        father[i] = i; //将集合号初始化
}
//递归查找祖宗并将其集合号修改成和祖宗一致
int find(int x)
{
    if (x != father[x])
        father[x] = find(father[x]);
    return father[x];
}
//联合集合号,将两个集合号不一样的结点联合
void Union(int &x, int &y)
{
    int a, b;
    a = find(x);
    b = find(y);
    if (a != b)
        father[b] = a; //将集合号修改为一样
}
int main()
{
    int x, u, v, sum = 0; //sum统计祖宗个数
    cout << "input n and m" << endl;
    cin >> n >> m; //输入结点数和边数
    init();
    cout << "input u and v" << endl;
    for (int i = 1; i <= m; ++i) //确定两个结点的关系
    {
        cin >> u >> v;
        Union(u, v);
    }
    for (int i = 1; i <= n; ++i)
    {
        find(i);
        cout << father[i] << " ";
        if (father[i] == i)
            sum++;
    }
    cout << endl;
    cout << "sum=" << sum << endl;
    return 0;
}