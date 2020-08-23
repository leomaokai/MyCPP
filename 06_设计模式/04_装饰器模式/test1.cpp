//test1.cpp
#include <iostream>
#include <memory>
using namespace std;

class Car
{
public:
    virtual void show() = 0;
};
//汽车品牌类
class Bmw : public Car
{
public:
    void show()
    {
        cout << "this is a BMW" << endl;
    }
};
class Byd : public Car
{
public:
    void show()
    {
        cout << "this is a BYD" << endl;
    }
};
//装饰器
class decorator1 : public Car
{
public:
    decorator1(Car *p) : pCar(p) {}
    void show()
    {
        pCar->show();
        cout << "自动驾驶" << endl;
    }

private:
    Car *pCar;
};
class decorator2 : public Car
{
public:
    decorator2(Car *p) : pCar(p) {}
    void show()
    {
        pCar->show();
        cout << "自动导航" << endl;
    }

private:
    Car *pCar;
};
int main()
{
    unique_ptr<Car> p1(new decorator1(new Bmw));
    p1->show();
    unique_ptr<Car> p2(new decorator2(new Byd));
    p2->show();

    return 0;
}
