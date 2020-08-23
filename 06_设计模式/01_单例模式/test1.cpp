//test1.cpp

//饿汉式单例模式:还没有获取实例对象,实例对象就已经产生了
//线程安全
#include <iostream>
using namespace std;

class Singleton
{
public:
    static Singleton *getInstance() // *3 获取类的唯一实例对象的接口方法
    {
        return &instance;
    }

private:
    static Singleton instance; // *2 定义一个唯一的类的实例化对象
    Singleton()                // *1 构造函数私有化
    {
    }
    Singleton(const Singleton &) = delete;
    Singleton &operator=(const Singleton &) = delete;
};
Singleton Singleton::instance;
int main()
{
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();

    return 0;
}