//test1.cpp
#include <iostream>
using namespace std;
int main()
{
    int a = 10;
    int &b = a; //左值引用
    //int &&c = a;//错误，无法将左值绑定到右值引用
    //int &d = 10;//错误，无法将右值绑定到左值引用
    const int &e = 10; //右值可绑定到左值常引用
    /*int tmp = 10;
    const int &e = tmp;*/
    int &&f = 10; //右值绑定到右值引用
    /*int tmp = 10;
    int &&f = tmp;*/
    int &g = f; //一个右值引用变量本身是一个左值

    return 0;
}