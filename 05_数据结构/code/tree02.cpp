//tree02.cpp
/*
根据二叉树的前序和中序输出其后序
*/
#include <iostream>
#include <string>
using namespace std;
string preorder, inorder;
void postorder1(string pre, string in)//后序遍历,传字串方式
{
    if (pre.size() <= 0)
        return;
    int len = 0;
    //while(in[len]!=pre[0])
    //  len++;
    len = in.find(pre[0]);                       //根结点在中序序列中的位置
    postorder1(pre.substr(1, len), in.substr(0, len));   //递归构造左子树
    postorder1(pre.substr(len + 1), in.substr(len + 1)); //递归构造右子树
    cout << pre[0];                                     //输出根(pre[0]为树根)
}
void postorder2(int l1,int l2,int size)//后序遍历,传下标方式
{
    if(size<0)
        return;
    int index=inorder.find(preorder[l1])-l2;
    postorder2(l1+1,l2,index);
    postorder2(l1+index+1,l2+index+1,size-index-1);
    cout<<preorder[l1];
}

int main()
{
    while (cin >> preorder >> inorder)//输入前序和中序
    {
        postorder1(preorder, inorder);//后序遍历
        cout<<inorder.find(preorder[0]);
        int size=preorder.size();
        postorder2(0,0,size);
        cout << endl;
    }
    return 0;
}