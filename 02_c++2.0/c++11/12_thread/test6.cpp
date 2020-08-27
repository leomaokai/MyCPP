//test6.cpp
#include <iostream>
#include <thread>
#include <list>
#include <atomic> //包含很多原子类型
using namespace std;

//用互斥锁可保证原子操作
//但互斥锁比较重
//通过CAS可保证简单操作的原子操作
volatile std::atomic_bool isok = false;
volatile std::atomic_int countnumber = 0;
void handler()
{
    while (!isok)
    {
        //线程出让当前的CPU时间片,等待下一次调度
        std::this_thread::yield();
    }
    for (int i = 0; i < 100; ++i)
    {
        countnumber++;
    }
}
int main()
{
    list<std::thread> tlist;
    for (int i = 0; i < 5; ++i)
    {
        tlist.push_back(std::thread(handler));
    }
    std::this_thread::sleep_for(std::chrono::seconds(3));
    isok = true;
    cout << "countnumber:" << countnumber << endl;
    for (std::thread &t : tlist)
    {
        t.join();
    }
    cout << "countnumber:" << countnumber << endl;
    return 0;
}