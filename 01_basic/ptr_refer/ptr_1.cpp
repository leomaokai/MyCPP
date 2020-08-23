#include<iostream>
using namespace std;
int main()
{
    int a=1;
    int* p=&a;
    int* &rp=p;
    (*rp)++;
    cout<<"a= "<<a<<endl;
    cout<<"*p= "<<*p<<endl;
    cout<<"*rp= "<<*rp<<endl;
    int b=5;
    p = &b;
    cout<<"a= "<<a<<endl;
    cout<<"*p= "<<*p<<endl;
    cout<<"*rp= "<<*rp<<endl;
    return 0;
}