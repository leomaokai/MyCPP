//树堆
#include <iostream>
#include <time.h>
using namespace std;
const int maxn = 1000;
int n, cnt = 0, root; //结点数,下标,树根
struct node
{
    int lc, rc;    //左右孩子
    int val, pri;  //值,优先级
    int num, size; //重复个数,根的子树大小
} tree[maxn];
int newnode(int val) //生成新结点
{
    tree[++cnt].val = val;
    tree[cnt].pri = rand();
    tree[cnt].num = tree[cnt].size = 1;
    tree[cnt].rc = tree[cnt].lc = 0;
    return cnt;
}
void updatetree(int &p)
{
    tree[p].size = tree[tree[p].lc].size + tree[tree[p].rc].size + tree[p].num;
}
void right(int &p)
{
    int q = tree[p].lc;
    tree[p].lc = tree[q].rc;
    tree[q].rc = p;
    tree[q].size = tree[p].size;
    updatetree(p);
    p = q;
}
void left(int &p)
{
    int q = tree[p].rc;
    tree[p].rc = tree[q].lc;
    tree[q].lc = p;
    tree[q].size = tree[p].size;
    updatetree(p);
    p = q;
}
void insertval(int &p, int val) //插入操作
{
    if (!p)
    {
        p = newnode(val);
        return;
    }
    tree[p].size++;
    if (val == tree[p].val)
    {
        tree[p].num++;
        return;
    }
    if (val < tree[p].val)
    {
        insertval(tree[p].lc, val);
        if (tree[p].pri < tree[tree[p].lc].pri)
            right(p);
    }
    else
    {
        insertval(tree[p].rc, val);
        if (tree[p].pri < tree[tree[p].rc].pri)
            left(p);
    }
}
void deleteval(int &p, int val)
{
    if (!p)
        return;
    tree[p].size--;         //size为子树的大小
    if (val == tree[p].val) //找到
    {
        if (tree[p].num > 1) //num为val的数量
        {
            tree[p].num--;
            return;
        }
        if (!tree[p].lc || !tree[p].rc)
            p = tree[p].lc + tree[p].rc; //用孩子代替
        else if (tree[tree[p].lc].pri > tree[tree[p].rc].pri)
        {
            right(p);
            deleteval(tree[p].rc, val);
        }
        else
        {
            left(p);
            deleteval(tree[p].lc, val);
        }
        return;
    }
    if (val < tree[p].val)
        deleteval(tree[p].lc, val);
    else
        deleteval(tree[p].rc, val);
}
int getpre(int val)
{
    int p = root;
    int res = -1;
    while (p)
    {
        if (tree[p].val < val)
        {
            res = tree[p].val;
            p = tree[p].rc;
        }
        else
        {
            res = tree[p].val;
            p = tree[p].lc;
        }
    }
    return res;
}
int getnext(int val)
{
    int p = root;
    int res = -1;
    while (p)
    {
        if (tree[p].val > val)
        {
            res = tree[p].val;
            p = tree[p].lc;
        }
        else
        {
            res = tree[p].val;
            p = tree[p].rc;
        }
    }
    return res;
}
void treap()
{
    int x;
    cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        cin >> x;
        insertval(root, x);
    }
}
void print(int p) //中序遍历
{
    if (p)
    {
        print(tree[p].lc);
        cout << tree[p].val << " ";
        print(tree[p].rc);
    }
}
int main()
{
    srand(time(0));
    treap();
    print(root);
    cout << endl;
    insertval(root, 33);
    print(root);
    cout << endl;
    deleteval(root, 33);
    print(root);
    cout << endl;
    return 0;
}