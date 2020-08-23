//person.cpp
#include<iostream>
using namespace std;
class person
{
    public:
    person()
    {
        cout<<"调用构造函数"<<endl;
    }
    ~person()
    {
        cout<<"调用析构函数"<<endl;
    }
};
int main()
{
    int i=0;
    if(i==0)
        //static person p;
        person p;
    cout<<"结束if()"<<endl;
    return 0;
}