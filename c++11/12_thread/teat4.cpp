//test4.cpp
//线程间同步通信机制
//生产者,消费者线程模型
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
//C++ STL容器都是线程不安全的
//我们需要重新定义一个类将其改为线程安全
using namespace std;

std::mutex mtx;//定义互斥锁,互斥操作
std::condition_variable cv;//定义条件变量,通信操作

//生产者生产一个物品,通知消费者消费一个
//消费者消费一个物品,再通知生产者继续生产
class Queue
{
public:
    void put(int val) //生成物品
    {
        unique_lock<std::mutex> lck(mtx);
        while (!que.empty())
        {
            //que 不为空,生产者应通知消费者去消费
            //生产者线程应该进入等待状态,并且把mtx互斥锁释放
            cv.wait(lck);
        }
        que.push(val);
        //通知其它所有线程消费
        //其它线程得到该通知就会从等待状态进入阻塞状态,获取锁才能继续执行
        cv.notify_all();
        cout << "生产者生产:" << val << "号物品" << endl;
    }
    int get() //消费物品
    {
        unique_lock<std::mutex> lck(mtx);
        while (que.empty())
        {
            //消费者线程发现que为空,通知生产者线程生产物品
            //消费者线程进入等待状态,并且释放互斥锁
            cv.wait(lck);
        }
        int val = que.front();
        que.pop();
        //通知其它线程生产
        cv.notify_all();
        cout << "消费者消费:" << val << "号物品" << endl;
        return val;
    }

private:
    queue<int> que;
};

void producer(Queue* que)
{
    for (int i = 1; i <= 10; ++i)
    {
        que->put(i);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
void consumer(Queue* que)
{
    for (int i = 1; i <= 10; ++i)
    {
        que->get();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main()
{
    Queue que;
    std::thread t1(producer, &que);
    std::thread t2(consumer, &que);

    t1.join();
    t2.join();
    return 0;
}