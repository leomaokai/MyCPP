//tree01.cpp
/*
n为二叉树的结点数
每一个字母为结点,后面两个字母为左右儿子,空结点用'*'表示
输出二叉树的前中后序遍历结果
*/
#include <iostream>
#include <string>
using namespace std;

int n, root, l[100], r[100];
string s;

void preorder(int t)//前序遍历
{
    if (t != '*' - 'a')
    {
        cout << char(t + 'a');
        preorder(l[t]);
        preorder(r[t]);
    }
}
void midorder(int t)//中序遍历
{
    if (t != '*' - 'a')
    {
        midorder(l[t]);
        cout << char(t + 'a');
        midorder(r[t]);
    }
}
void bacorder(int t)//后序遍历
{
    if (t != '*' - 'a')
    {
        bacorder(l[t]);
        bacorder(r[t]);
        cout << char(t + 'a');
    }
}
int main()
{
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cin >> s;
        if (!i)
            root = s[0] - 'a';//记录根结点
        l[s[0] - 'a'] = s[1] - 'a'; //左孩子
        r[s[0] - 'a'] = s[2] - 'a'; //右孩子
    }
    cout << "------前序遍历--------" << endl;
    preorder(root);
    cout<<endl;
    cout << "------中序遍历-------" << endl;
    midorder(root); 
    cout<<endl;
    cout << "------后序遍历-------" << endl;
    bacorder(root); 
    cout<<endl;
    return 0;
}