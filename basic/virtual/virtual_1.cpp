//virtual_1.cpp
#include<iostream>
using namespace std;;
class person
{
    public:
    virtual ~person()
    {
        cout<<"~person"<<endl;
    }
};
class stu : public person 
{
    public:
    ~stu()
    {
        cout<<"~stu"<<endl;
    }
};
int main()
{
    person* ptr = new stu;
    delete ptr;
    return 0;
} 