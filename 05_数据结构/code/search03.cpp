//search03.cpp
//AVL平衡二叉树
#include <iostream>
#include <algorithm>
using namespace std;
typedef struct avlnode
{
    int data;
    int height;
    avlnode *lchild;
    avlnode *rchild;
} * avltree;
//返回t的高度
int height(avltree t)
{
    if (t == nullptr)
        return 0;
    return t->height;
}
//更新t的高度
void updateheight(avltree &t)
{
    t->height = max(height(t->lchild), height(t->rchild)) + 1;
}
//LL型顺时针旋转调整
avltree LL_rotation(avltree &t)
{
    avltree temp = t->lchild;
    t->lchild = temp->rchild;
    temp->rchild = t;
    updateheight(t);
    updateheight(temp);
    return temp;
}
//RR型逆时针旋转调整
avltree RR_rotation(avltree &t)
{
    avltree temp = t->rchild;
    t->rchild = temp->rchild;
    temp->lchild = t;
    updateheight(t);
    updateheight(temp);
    return temp;
}
//LR型
avltree LR_rotation(avltree &t)
{
    t->lchild = RR_rotation(t->lchild);
    return LL_rotation(t);
}
//RL型
avltree RL_rotation(avltree &t)
{
    t->rchild = LL_rotation(t->rchild);
    return RR_rotation(t);
}
//插入一个结点
avltree insertnode(avltree &t, int x)
{
    if (t == nullptr)
    {
        t = new avlnode();
        t->lchild = nullptr;
        t->rchild = nullptr;
        t->data = x;
        t->height = 1;
        cout << "insert ok" << endl;
        return t;
    }
    if (t->data == x)
        return t;
    if (x < t->data) //插入左子树
    {
        t->lchild = insertnode(t->lchild, x);
        if (height(t->lchild) - height(t->rchild) == 2) //平衡调整
        {
            if (x < t->lchild->data)
                t = LL_rotation(t);
            else
                t = LR_rotation(t);
        }
    }
    else //插入右子树
    {
        t->rchild = insertnode(t->rchild, x);
        if (height(t->rchild) - height(t->lchild) == 2) //平衡调整
        {
            if (x > t->rchild->data)
                t = RR_rotation(t);
            else
                t = RL_rotation(t);
        }
    }
    updateheight(t);
    return t;
}
//删除结点后的平衡调整
avltree adjust(avltree &t)
{
    if (t == nullptr)
        return nullptr;
    if (height(t->lchild) - height(t->rchild) == 2)
    {
        if (height(t->lchild->lchild) >= height(t->lchild->rchild))
            t = LL_rotation(t);
        else
            t = LR_rotation(t);
    }
    if (height(t->rchild) - height(t->lchild) == 2)
    {
        if (height(t->rchild->rchild) >= height(t->rchild->lchild))
            t = RR_rotation(t);
        else
            t = RL_rotation(t);
    }
    return t;
}
//删除
avltree deltree(avltree &t, int x)
{
    if (t == nullptr)
        return nullptr;
    if (t->data == x)
    {
        if (t->rchild == nullptr) //结点右孩子为空,直接删除
        {
            avltree temp = t;
            t = t->lchild;
            delete temp;
        }
        else //将其右子树的最左结点替换这个结点
        {
            avltree temp;
            temp = t->rchild;
            while (temp->lchild)
                temp = temp->lchild;
            t->data = temp->data;
            t->rchild = deltree(t->rchild, t->data);
            updateheight(t);
        }
        return t;
    }
    if (t->data > x)
        t->lchild = deltree(t->lchild, x);
    if (t->data < x)
        t->rchild = deltree(t->rchild, x);
    updateheight(t);
    if (t->lchild)
        t->lchild = adjust(t->lchild);
    if (t->rchild)
        t->rchild = adjust(t->rchild);
    if (t)
        t = adjust(t);
    return t;
}
//创建avl
avltree createavl(avltree &t)
{
    int n, x = 0;
    cout << "input n" << endl;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        cout << "input x" << endl;
        cin >> x;
        t = insertnode(t, x);
    }
    return t;
}
void inorder(avltree t)
{
    if (t == nullptr)
        return;
    inorder(t->lchild);
    cout << t->data << '\t' << t->height << endl;
    inorder(t->rchild);
}
int main()
{
    avltree t = nullptr;
    t = createavl(t);
    inorder(t);
    int x = 0;
    cout<<"input del x"<<endl;
    cin >> x;
    t = deltree(t, x);
    inorder(t);
    return 0;
}
