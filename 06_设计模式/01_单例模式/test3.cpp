//test3.cpp

//懒汉式单例模式:唯一的实例对象,直到第一次获取它的时候才产生
//线程安全的懒汉式单例模式
#include <iostream>
using namespace std;
class Singleton
{
public:
    static Singleton *getInstance() // *3 获取类的唯一实例对象的接口方法
    {
        //函数静态局部变量的初始化,在汇编指令上已经自动添加互斥指令了
        static Singleton instance; // *2 定义一个唯一的类的实例化对象指针
        return &instance;
    }

private:
    Singleton() // *1 构造函数私有化
    {
    }
    Singleton(const Singleton &) = delete; //将实例化对象指针初始化为空
    Singleton &operator=(const Singleton &) = delete;
};
int main()
{
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();

    return 0;
}