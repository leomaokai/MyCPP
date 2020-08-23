//test5.cpp
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
using namespace std;

std::mutex mtx;             //pthread_mutex_t
std::condition_variable cv; //pthread_condition_t
int main()
{
    //lock_guard 不能用在函数参数传递或返回过程中
    //只能用在简单的临界区代码段的互斥操作中
    //lock_guard<std::mutex> guard(mtx);

    //unique_lock 不仅可以用在简单的临界区代码段的互斥操作中
    //还能用在函数调用过程中如cv.wait();
    // unique_lock<std::mutex> lck(mtx);
    // cv.wait(lck); //使线程进入等待状态并释放锁

    //通知在cv上等待的线程运行
    //其它在cv上等待的线程收到通知由等待进入阻塞
    // cv.notify_all();

    return 0;
}