//tree05.cpp
#include <iostream>
using namespace std;
const int MAXBIT = 100;
const int MAXVALUE = 10000;
const int MAXLEAF = 30;
const int MAXNODE = MAXLEAF * 2 - 1;
//结点结构体
typedef struct
{
    double weight;
    int parent;
    int lchild;
    int rchild;
    char value;
} HNodeType;
//编码结构体
typedef struct
{
    int bit[MAXBIT];
    int start;
} HCodeType;
HNodeType Huffnode[MAXNODE];  //结点结构体数组
HCodeType Huffcode[MAXVALUE]; //编码结构体数组
//构造哈夫曼树,n为初始叶子数
void Huffmantree(HNodeType Huffnode[MAXNODE], int n)
{
    /*
    i,j:循环变量 m1,m2:两个最小权值结点的权值 x1,x2:最小权值结点的编号
    */
    int i, j, x1, x2;
    double m1, m2;
    for (i = 0; i < 2 * n - 1; ++i) //初始化结点
    {
        Huffnode[i].weight = 0;
        Huffnode[i].parent = -1;
        Huffnode[i].lchild = -1;
        Huffnode[i].rchild = -1;
    }
    for (i = 0; i < n; ++i) //初始化叶子
    {
        cout << "please input value and weigth of leaf node " << i + 1 << endl;
        cin >> Huffnode[i].value >> Huffnode[i].weight;
    }
    for (i = 0; i < n - 1; ++i) //构造哈夫曼树
    {
        m1 = m2 = MAXVALUE;
        x1 = x2 = 0;
        for (j = 0; j < n + i; ++j)
        {
            if (Huffnode[j].weight < m1 && Huffnode[j].parent == -1)
            {
                m2 = m1;
                x2 = x1;
                m1 = Huffnode[j].weight;
                x1 = j;
            }
            else if (Huffnode[j].weight < m2 && Huffnode[j].parent == -1)
            {
                m2 = Huffnode[j].weight;
                x2 = j;
            }
        }
        cout << "x1: " << m1 << "  x2: " << m2 << endl;
        //设置新结点
        Huffnode[x1].parent = n + i;
        Huffnode[x2].parent = n + i;
        Huffnode[n + i].weight = m1 + m2;
        Huffnode[n + i].lchild = x1;
        Huffnode[n + i].rchild = x2;
    }
}
//哈夫曼树编码
void HuffmanCode(HCodeType Huffcode[MAXLEAF], int n)
{
    HCodeType cd;   //临时变量存放求解编码时的信息
    int i, j, c, p; //c为结点编号,p为双亲编号
    for (i = 0; i < n; ++i)
    {
        cd.start = n - 1;
        c = i;
        p = Huffnode[c].parent;
        while (p != -1)
        {
            if (Huffnode[p].lchild == c)
                cd.bit[cd.start] = 0;
            else
                cd.bit[cd.start] = 1;
            cd.start--;
            c = p;
            p = Huffnode[c].parent;
        }
        for (j = cd.start + 1; j < n; ++j)
            Huffcode[i].bit[j] = cd.bit[j];
        Huffcode[i].start = cd.start;
    }
}
int main()
{
    int n;
    cout << "please input n:" << endl;
    cin >> n;
    Huffmantree(Huffnode, n);
    HuffmanCode(Huffcode, n);
    for (int i = 0; i < n; ++i)
    {
        cout << Huffnode[i].value << ": huffman code is ";
        for (int j = Huffcode[i].start + 1; j < n; ++j)
            cout << Huffcode[i].bit[j];
        cout << endl;
    }
    return 0;
}