//search02.cpp
//二叉搜索树
#include <iostream>
using namespace std;
using elemtype = int;
const int END = -1;
//二叉树结点结构体
struct bstnode
{
    elemtype data;
    bstnode *lchild, *rchild;
};
//二叉搜索树递归查找
bstnode *searchbst(bstnode *&t, elemtype e)
{
    if ((t == nullptr) || (e == t->data))
        return t;
    else if (e < t->data)
        return searchbst(t->lchild, e);
    else
        return searchbst(t->rchild, e);
}
//插入
void insertbst(bstnode *&t, const elemtype e)
{
    if (t == nullptr)
    {
        bstnode *temp = new bstnode();
        temp->data = e;
        temp->lchild = nullptr;
        temp->rchild = nullptr;
        t = temp;
    }
    else if (e < t->data)
        insertbst(t->lchild, e);
    else if (e > t->data)
        insertbst(t->rchild, e);
}
//创建
void createbst(bstnode *&t)
{
    t = nullptr;
    elemtype e;
    cin >> e;
    while (e != END)
    {
        insertbst(t, e);
        cin >> e;
    }
}
//删除
void delbst(bstnode *&t, elemtype key)
{
    if (t == nullptr)
        return;
    bstnode *p = t;
    bstnode *f = nullptr;
    //查找被删除结点的
    while (p != nullptr)
    {
        if (p->data == key)
            break;
        f = p;
        if (key < p->data)
            p = p->lchild;
        else
            p = p->rchild;
    }
    if (p == nullptr)
        return;
    //结点删除,三种情况
    bstnode *temp = nullptr; 
    bstnode *s = nullptr;
    //一:被删除结点左右子树都不为空
    if ((p->lchild) && (p->rchild))
    {
        temp=p;
        s=p->lchild;
        //查找被删除结点左子树的最右结点s
        while (s->rchild)
        {
            temp = s;
            s = s->rchild;
        }
        p->data = s->data; //先将s的值赋给p,再删除s结点
        if (temp != p)
            temp->rchild = s->lchild;
        else
            temp->lchild = s->lchild;
        delete s;
    }
    else
    {
        if (p->rchild == nullptr)//二:被删除结点无右子树
        {
            temp=p;
            p=p->lchild;
        }
        else if(p->lchild==nullptr)//三:被删除结点无左子树
        {
            temp=p;
            p=p->rchild;
        }
        if(f==nullptr)
            t=p;
        else if(temp==f->lchild)
            f->lchild=p;
        else 
            f->rchild=p;
        delete temp;
    }
}
//中序遍历
void inorder(bstnode* &t)
{
    if(t!=nullptr)
    {
        inorder(t->lchild);
        cout<<t->data<<'\t';
        inorder(t->rchild);
    }
}
int main()
{
    bstnode* t;
    cout<<"input data"<<endl;
    createbst(t);
    cout<<"in order"<<endl;
    inorder(t);
    cout<<endl;
    delbst(t,7);
    inorder(t);
    return 0;
}
