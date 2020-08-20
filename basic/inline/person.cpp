//person.cpp
#include<iostream>
using namespace std;
class person
{
    public:
    inline virtual void who()
    {
        cout<<"he is a person"<<endl;
    }
    virtual ~person(){}//为多态基类声明virtual析构函数
};
class stu : public person
{
    public:
    void who() //隐式内联
    {
        cout<<"he is a student"<<endl;
    }
};
int main(){
    person bob;
    bob.who();//bob属于person,可以内联
    person *tom = new stu();
    tom->who();//虚函数通过指针调用,不可内联
    delete tom;
    tom = nullptr;
    return 0;
}