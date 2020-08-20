//sizeof_3.cpp
#include<iostream>
using namespace std;
class A
{
    public:
    virtual void func();
    int a;
};
class B:public A
{
    public:
    virtual void func();
    int b;
    static int  c;
};
class C:virtual public B
{};
int main()
{
    cout<<sizeof(A)<<endl;
    cout<<sizeof(B)<<endl;
    cout<<sizeof(C)<<endl;
    return 0;
}