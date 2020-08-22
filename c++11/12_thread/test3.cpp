//test3.cpp
//自动释放锁
#include <iostream>
#include <thread>
#include <list>
//互斥锁头文件
#include <mutex>
using namespace std;

//线程间互斥锁应用

int countnumber = 10;
//全局一把互斥锁
std::mutex mtx;
void handler(int id)
{
    while (countnumber > 0)
    {
        // mtx.lock();    //lock 其它线程会阻塞
        //lock_guard<std::mutex> lock(mtx); //自动释放锁(类似scoped_ptr)
        unique_lock<std::mutex> lock(mtx); //第二种自动释放锁(类似unique_ptr)
        if (countnumber > 0)               //锁+双重判断
        {
            cout << "the thread id is " << id
                 << " and the number is5  "
                 << countnumber << endl;
            countnumber--; // -- 操作非线程安全
        }
        //mtx.unlock(); //unlock
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
int main()
{
    list<std::thread> tlist;
    for (int i = 0; i <= 2; ++i) //创建3个线程
    {
        tlist.push_back(std::thread(handler, i));
    }
    for (std::thread &t : tlist)
    {
        t.join();
    }
    cout << "main done" << endl;
    return 0;
}