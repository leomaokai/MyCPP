//tree00.cpp
#include <iostream>
#include <queue>
using namespace std;

typedef struct Bnode //二叉树存储结构
{
    char data;
    struct Bnode *lchild;
    struct Bnode *rchild;
} Bnode, *Btree;
void Createtree(Btree &T) //创建二叉树函数
{
    //按先序次序输入二叉树结点的值(一个字符)
    char ch;
    cin >> ch;
    if (ch == '#')
        T = nullptr;
    else if (ch == '*')
        return;
    else
    {
        T = new Bnode(); //生成新结点
        T->data = ch;
        Createtree(T->lchild); //递归创建左子树
        Createtree(T->rchild); //递归创建右子树
    }
}
void preorder(Btree T) //先序遍历
{
    if (T)
    {
        cout << T->data << " ";
        preorder(T->lchild);
        preorder(T->rchild);
    }
}
void inorder(Btree T) //中序遍历
{
    if (T)
    {
        inorder(T->lchild);
        cout << T->data << " ";
        inorder(T->rchild);
    }
}
void posorder(Btree T) //后序遍历
{
    if (T)
    {
        posorder(T->lchild);
        posorder(T->rchild);
        cout << T->data << " ";
    }
}
bool levelorder(Btree T) //层次遍历
{
    Btree p;
    if (T == nullptr)
        return false;
    queue<Btree> que;
    que.push(T);
    while (!que.empty())
    {
        p = que.front();
        que.pop();
        cout << p->data << " ";
        if (p->lchild)
            que.push(p->lchild);
        if (p->rchild)
            que.push(p->rchild);
    }
    return true;
}
Btree pre_in_creatrtree(char *pre, char *mid, int len) //前序中序还原树
{
    if (len == 0)
        return nullptr;
    char ch = pre[0];
    int index = 0;
    while (mid[index] != ch)
        index++;
    Btree T = new Bnode();
    T->data = ch;
    T->lchild = pre_in_creatrtree(pre + 1, mid, index);
    T->rchild = pre_in_creatrtree(pre + index + 1, mid + index + 1, len - index - 1);
    return T;
}
Btree pos_in_creatrtree(char *pos, char *mid, int len) //后序中序还原树
{
    if (len == 0)
        return nullptr;
    char ch = pos[len - 1];
    int index = 0;
    while (mid[index] != ch)
        index++;
    Btree T = new Bnode();
    T->data = ch;
    T->lchild = pos_in_creatrtree(pos, mid, index);
    T->rchild = pos_in_creatrtree(pos + index, mid + index + 1, len - index - 1);
    return T;
}
int main()
{
    // Btree tree1;
    // Createtree(tree1);
    // cout << "先序遍历" << endl;
    // preorder(tree1);
    // cout << endl;
    // cout << "中序遍历" << endl;
    // inorder(tree1);
    // cout << endl;
    // cout << "后序遍历" << endl;
    // posorder(tree1);
    // cout << endl;
    Btree tree2 = pos_in_creatrtree("DEBGFCA", "DBEAFGC", 7);
    posorder(tree2);
    cout << endl;
    inorder(tree2);
    cout << endl;
    Btree tree3 = pre_in_creatrtree("ABDECFG", "DBEAFGC", 7);
    preorder(tree3);
    cout << endl;
    inorder(tree3);
    cout << endl;
    posorder(tree3);
    return 0;
}
