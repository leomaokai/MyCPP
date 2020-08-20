//test_1.cpp
#include<iostream>
using namespace std;
int main()
{
    unsigned int a=2;
    unsigned int b=1;
    cout<<"~2= "<<~a<<endl;
    cout<<"1 & 2 = "<<(b&a)<<endl;
    cout<<"1 | 2 = "<<(a|b)<<endl;
    cout<<"1 ^ 2 = "<<(a^b)<<endl;
    return 0;
}