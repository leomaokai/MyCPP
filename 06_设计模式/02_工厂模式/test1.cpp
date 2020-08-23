//test1.cpp
//简单工厂
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class cake
{
public:
    cake(string name) : _name(name) {}
    virtual void show() = 0;
    string _name;
};
class acake : public cake
{
public:
    acake(string name) : cake(name) {}
    void show()
    {
        cout << "acake" << _name << endl;
    }
};
class bcake : public cake
{
public:
    bcake(string name) : cake(name) {}
    void show()
    {
        cout << "bcake" << _name << endl;
    }
};
enum caketype
{
    Acake,
    Bcake
};
class simplefactory
{
public:
    cake *createcake(caketype ct)
    {
        switch (ct)
        {
        case Acake:
            return new acake("水果");
        case Bcake:
            return new bcake("巧克力");
        default:
            break;
        }
        return nullptr;
    }
};
//若要再增加一个蛋糕店,需要修改整个工厂类,违背了开发封闭原则
int main()
{
    unique_ptr<simplefactory> factory(new simplefactory());
    unique_ptr<cake> p1(factory->createcake(Acake));
    unique_ptr<cake> p2(factory->createcake(Bcake));
    p1->show();
    p2->show();
    return 0;
}
