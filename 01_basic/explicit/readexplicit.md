# explicit

`显示`关键字,防止隐式类型转换

# explicit的应用

`explicit` 修饰构造函数,可防止隐式类型转换和复制初始化

`explicit` 修饰转换函数可防止隐式类型转换,但可按语境转换

```c++
//explicit.cpp
#include<iostream>
using namespace std;
class A  
{
    public:
    A(int){}
    operator bool () const {return true;}
};
class B
{
    public:
    explicit B (int){}   //explicit修饰构造函数
    explicit operator bool () const {return true;} //explicit修饰转换函数
};

void doA(A a) {}
void doB(B b) {}

int main()
{
    A a1(1);       //直接初始化
    A a2 = 1;      //复制初始化
    A a3{ 1 };     //直接列表初始化
    A a4 = { 1 };  //复制列表初始化
    A a5 = (A)1;   //允许 static_cast 的显式转换 
    doA(1);        //允许从 int 到A的隐式转换
    if (a1);       //使用转换函数从A到bool的隐式转换
    bool a6(a1);   //使用转换函数的从A到bool的隐式转换
    bool a7 = a1;  //使用转换函数的从A到bool的隐式转换
    bool a8 = static_cast<bool>(a1);  
                   //static_cast进行直接初始化

    B b1(1);       //直接初始化
//    B b2 = 1;    //不可以复制初始化
    B b3{ 1 };     //直接列表初始化
//    B b4 = { 1 };//不可以复制列表初始化
    B b5 = (B)1;   //允许 static_cast 的显式转换
//    doB(1);      //不可以从 int 到 B 的隐式转换
    if (b1);       //对象可以从 B 到 bool 的按语境转换
    bool b6(b1);   //对象可以从 B 到 bool 的按语境转换
//   bool b7 = b1; //对象不可以隐式转换
    bool b8 = static_cast<bool>(b1);  
                   // static_cast 进行直接初始化

    return 0;
}
```

