//test1.cpp
#include <iostream>
#include <thread>

//线程函数
void threadHandler1()
{
    std::cout << "hello thread1!" << std::endl;
}
void threadHandler2(int time)
{
    std::cout<<"hello thread2!"<<std::endl;
}
int main()
{
    //创建一个线程对象,传入一个线程函数
    std::thread t1(threadHandler1);
    //t2结束睡眠5秒
    std::thread t2(threadHandler2,5);
    //主线程等待子线程结束
    t1.join();

    //把子线程设置为分离线程
    t2.detach();

    // 主线程睡眠10秒
    std::this_thread::sleep_for(std::chrono::seconds(10));

    std::cout << "main processed" << std::endl;
    return 0;
}