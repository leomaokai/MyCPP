//test.cpp
#include<iostream>
//#define NDEBUG
#include<cassert>
using namespace std;
int main()
{
    int a=10;
    a=5;
    assert(a==10);
    cout<<"a= "<<a<<endl;
    return 0;
}