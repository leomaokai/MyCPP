//test4.cpp
#include <iostream>
#include <memory>
#include <thread>
using namespace std;
//多线程访问共享对象的线程安全问题

class A
{
public:
    A() { cout << "A()" << endl; };
    ~A() { cout << "~A()" << endl; }
    void testa() { cout << "使用A" << endl; }
};

//子线程
//通过weak_ptr检测A对象是否被析构
void handler01(weak_ptr<A> wp)
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    shared_ptr<A> p = wp.lock(); //将弱指针提升为强指针
    if (p != nullptr)
    {
        p->testa();
    }
    else
    {
        cout << "A析构,无法访问!" << endl;
    }
}
//main线程 
int main()
{
    {
        shared_ptr<A> sp(new A());
        thread t1(handler01, weak_ptr<A>(sp));
        t1.detach();
    }
    //父线程将A析构,子线程无法访问
    std::this_thread::sleep_for(std::chrono::seconds(10));

    return 0;
}