//sizeof_4.cpp
#include<iostream>
#include<string.h>
using namespace std;
int main()
{
    char str1[10]="cumt";
    cout<<sizeof(str1)<<endl;
    cout<<strlen(str1)<<endl;
    char str2[]="hello\\0";
    cout<<sizeof(str2)<<endl;
    cout<<strlen(str2)<<endl;
    char str3[]="hello\\\0";
    cout<<sizeof(str3)<<endl;
    cout<<strlen(str3)<<endl;        
    return 0;
}
