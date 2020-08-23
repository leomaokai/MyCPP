//sizeof_1.cpp
#include <iostream>
#include<string>
using namespace std;
int func(char c[100])
{
    return sizeof(c);
}
int main()
{
    char str[]="cumt";
    char *p=str;
    int a=10;
    cout<<sizeof(str)<<endl;
    cout<<sizeof(p)<<endl;
    cout<<sizeof(a)<<endl;
    char s[]="hello";
    cout<<func(s)<<endl;
    void *b=malloc(10);
    cout<<sizeof(b)<<endl;
    return 0;
}