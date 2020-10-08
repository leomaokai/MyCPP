//线段树区间更新
#include <iostream>
#include <algorithm>
using namespace std;
const int maxn = 100;
int n, a[maxn]{};
struct node
{
    int r, l, mx, lz;
} tree[maxn * 4];
void build(int k, int l, int r) //k表示存储下标
{
    tree[k].l = l;
    tree[k].r = r;
    tree[k].lz = 0;
    if (l == r) //叶子最大值为对应位置的元素值
    {
        tree[k].mx = a[l];
        return;
    }
    int mid, lc, rc;
    mid = (l + r) / 2;                          //划分点
    lc = k * 2;                                 //左孩子存储下标
    rc = k * 2 + 1;                             //右孩子存储下标
    build(lc, l, mid);                          //递归创建左子树
    build(rc, mid + 1, r);                      //递归创建右子树
    tree[k].mx = max(tree[lc].mx, tree[rc].mx); //结点区间最大值
}
void lazy(int k, int v) //做懒标记
{
    tree[k].mx = v; //更新最值
    tree[k].lz = v; //做懒标记
}
void pushdown(int k) //向下传递懒标记
{
    lazy(2 * k, tree[k].lz);     //传给左子树
    lazy(2 * k + 1, tree[k].lz); //传给右子树
    tree[k].lz = 0;              //清除自己的懒标记
}
void update(int k, int l, int r, int v) //将区间[l,r]修改为v
{
    if (tree[k].l >= l && tree[k].r <= r) //找到该区间
        return lazy(k, v);                //更新并做懒标记
    if (tree[k].lz != 0)
        pushdown(k); //懒标记下移
    int mid, lc, rc;
    mid = (tree[k].l + tree[k].r) / 2;
    lc = k * 2;
    rc = k * 2 + 1;
    if (l <= mid)
        update(lc, l, r, v);
    if (r > mid)
        update(rc, l, r, v);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
}
//区间[l,r]查询最值
int query(int k, const int &l, const int &r)
{
    if (tree[k].l >= l && tree[k].r <= r) //找到该区间
        return tree[k].mx;
    if (tree[k].lz != 0)
        pushdown(k);
    int mid, lc, rc;
    mid = (tree[k].l + tree[k].r) / 2;
    lc = k * 2;
    rc = k * 2 + 1;
    int Max = 0;
    if (l <= mid)
        Max = max(Max, query(lc, l, r)); //到左子树查询
    if (r > mid)
        Max = max(Max, query(rc, l, r)); //到右子树查询
    return Max;
}
void print(int k)
{
    if (tree[k].mx)
    {
        cout << k << '\t' << tree[k].l << '\t' << tree[k].r
             << '\t' << tree[k].mx << '\t' << endl;
        print(k << 1);
        print((k << 1) + 1);
    }
}
int main()
{
    return 0;
}