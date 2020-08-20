//ptr_2.cpp
#include<iostream>
using namespace std;
int func1(int &ref)
{
    ref++;
    return ref;
}
int func2(const int &ref)
{
    //ref++;//常量引用无法修改
    return ref;
}
int main()
{
    int a = 5;
    int b=func1(a);
    const int c=func2(a);
    //int &b=c;
    const int &e=a;
    //++e;
    cout<<b<<endl;
    cout<<c<<endl;
    //cout<<d<<endl;
    cout<<e<<endl;
    return 0;
}