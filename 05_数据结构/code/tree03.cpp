//tree03.cpp
/*
输入一个二叉树的中序和后序遍历,输出一个叶子结点,该叶子节点到根的数值总和最小
*/
#include <iostream>
#include <string>
using namespace std;
const int maxn = 1000;
int inorder[maxn], postorder[maxn], lch[maxn], rch[maxn];
int n, minv, minsum;

int createtree(int l1, int l2, int m)
//l1为中序开始的下标,l2为后序开始的下标,m为树序列长度
{
    if (m <= 0)
        return 0;
    int root = postorder[l2 + m - 1]; //根是后序序列的最后一个
    int len = 0;
    while (inorder[l1 + len] != root)
        ++len;
    lch[root] = createtree(l1, l2, len);
    rch[root] = createtree(l1 + len + 1, l2 + len, m - len - 1);
    return root;
}
bool readline(int *a) //读入
{
    string line;
    if (!getline(cin, line)) //一次读一行
        return false;
    stringstream s(line); //流对象,将读到的一行放入s中
    n = 0;
    int x;
    while (s >> x) //将s中的int放入x中
        a[n++] = x;
    return n > 0;
}
void findmin(int v, int sum)
{
    sum += v;
    if (!lch[v] && !rch[v]) //叶子的满足条件
        if (sum < minsum || (sum == minsum && v < minv))
        {
            minv = v;
            minsum = sum;
        }
    if (lch[v]) //v有左子树
        findmin(lch[v], sum);
    if (rch[v]) //v有右子树
        findmin(rch[v], sum);
}
int main()
{
    while (readline(inorder))
    {
        readline(postorder);
        createtree(0, 0, n);
        minsum = 0x7fffffff;
        findmin(postorder[n - 1], 0);
        cout << minv << endl;
    }
    return 0;
}