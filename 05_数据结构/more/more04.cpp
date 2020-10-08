//线段树
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
const int maxn = 100;
int n, a[maxn]{};
struct node
{
    int l, r, mx;
} tree[maxn * 4];
//构建一个线段树
void build(int k, int l, int r) //k表示存储下标
{
    tree[k].l = l;
    tree[k].r = r;
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
//将a[i]修改为v,点更新
void update(int k, const int &i, const int &v)
{
    if (tree[k].l == tree[k].r && tree[k].l == i) //找到a[i]
    {
        tree[k].mx = v;
        return;
    }
    int mid, lc, rc;
    mid = (tree[k].l + tree[k].r) / 2;
    lc = k * 2;
    rc = k * 2 + 1;
    if (i <= mid)
        update(lc, i, v);
    else
        update(rc, i, v);
    tree[k].mx = max(tree[lc].mx, tree[rc].mx);
}
//区间[l,r]查询最值
int query(int k, const int &l, const int &r)
{
    if (tree[k].l >= l && tree[k].r <= r) //找到该区间
        return tree[k].mx;
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
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    build(1, 1, n);
    print(1);
    cout << "input query l r" << endl;
    int l = 0, r = 0;
    cin >> l >> r;
    cout << query(1, l, r) << endl;
    cout << "update i v" << endl;
    int i = 0, v = 0;
    cin >> i >> v;
    update(1, i, v);
    print(1);
    return 0;
}