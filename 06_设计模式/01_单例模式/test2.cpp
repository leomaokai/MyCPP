//test2.cpp

//懒汉式单例模式:唯一的实例对象,直到第一次获取它的时候才产生
//非线程安全,加锁后可线程安全

#include <iostream>
#include <mutex>
using namespace std;
std::mutex mtx;
class Singleton
{
public:
    static Singleton *getInstance() // *3 获取类的唯一实例对象的接口方法
    {
        if (instance == nullptr)
        {
            lock_guard<std::mutex> guard(mtx);
            if (instance == nullptr)
            {
                instance = new Singleton();
            }
        }
        return instance;
    }

private:
    static Singleton *volatile instance; // *2 定义一个唯一的类的实例化对象指针
    Singleton()                 // *1 构造函数私有化
    {
    }
    Singleton(const Singleton &) = delete; //将实例化对象指针初始化为空
    Singleton &operator=(const Singleton &) = delete;
};
Singleton * volatile Singleton::instance = nullptr;
int main()
{
    Singleton *p1 = Singleton::getInstance();
    Singleton *p2 = Singleton::getInstance();
    Singleton *p3 = Singleton::getInstance();

    return 0;
}