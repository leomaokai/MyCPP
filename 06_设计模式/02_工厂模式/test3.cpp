//test3.cpp
//抽象工厂

#include <iostream>
#include <string>
#include <memory>
using namespace std;

//蛋糕店
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
//黄油
class butter
{
public:
    virtual void show() = 0;
};
class abutter : public butter
{
    void show() { cout << "A butter" << endl; }
};
class bbutter : public butter
{
    void show() { cout << "B butter" << endl; }
};

//工厂方法-->抽象工厂(对有一组关联关系的产品族提供产品对象的统一创建)
class abstractfactory
{
public:
    //工厂方法创建蛋糕
    virtual cake *createcake(string name) = 0;
    //工厂方法创建与蛋糕有关的黄油
    virtual butter *createbutter() = 0;
};
class acakefactory : public abstractfactory //acake factory
{
public:
    cake *createcake(string name)
    {
        return new acake(name);
    }
    butter *createbutter()
    {
        return new abutter();
    }
};
class bcakefactory : public abstractfactory //bcake factory
{
public:
    cake *createcake(string name)
    {
        return new bcake(name);
    }
    butter *createbutter()
    {
        return new bbutter();
    }
};

int main()
{
    unique_ptr<abstractfactory> afactory(new acakefactory());
    unique_ptr<abstractfactory> bfactory(new bcakefactory());
    unique_ptr<cake> p1(afactory->createcake("A"));
    unique_ptr<cake> p2(bfactory->createcake("B"));
    unique_ptr<butter> b1(afactory->createbutter());
    unique_ptr<butter> b2(bfactory->createbutter());
    p1->show();
    b1->show();
    p2->show();
    b1->show();

    return 0;
}