//test2.cpp
//工厂方法

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
class factory
{
public:
    virtual cake *createcake(string name) = 0;
};
class acakefactory : public factory//acake factory
{
public:
    cake *createcake(string name)
    {
        return new acake(name);
    }
};
class bcakefactory : public factory//bcake factory
{
public:
    cake *createcake(string name)
    {
        return new bcake(name);
    }
};
//若要添加一个新的蛋糕店,直接添加一个其工厂负责其生产
int main()
{
    unique_ptr<factory> afactory(new acakefactory());
    unique_ptr<factory> bfactory(new bcakefactory());
    unique_ptr<cake> p1(afactory->createcake("A"));
    unique_ptr<cake> p2(bfactory->createcake("B"));
    p1->show();
    p2->show();

    return 0;
}