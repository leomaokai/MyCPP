//test.cpp
#include<iostream>
#include<functional>
#include<map>
using namespace std;

int main()
{
    map<int,function<int(int,int)>> mymath;
    mymath[1]=[](int a,int b)->int {return a+b;};
    mymath[2]=[](int a,int b)->int {return a-b;};
    mymath[3]=[](int a,int b)->int {return a*b;};
    mymath[4]=[](int a,int b)->int {return a/b;};
    int choice=0;
    int a=0,b=0;
    cin>>choice;
    cin>>a>>b;
    cout<<mymath[choice](a,b)<<endl;

    return 0;
}