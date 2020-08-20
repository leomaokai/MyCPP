//sizeof_2.cpp
#include<iostream>
using namespace std;
class A
{
    public:
    int i;
    short s;
    char c;
};
class B
{
    public:
    int i;
    char c1;
    char c2;
};
int main()
{
    cout<<sizeof(int)<<endl;
    cout<<sizeof(short)<<endl;
    cout<<sizeof(char)<<endl;
    cout<<sizeof(int)+sizeof(short)+sizeof(char)<<endl;
    cout<<sizeof(A)<<endl;
    cout<<sizeof(B)<<endl;
    return 0;
}