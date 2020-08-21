//test2.cpp
#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <thread>
using namespace std;
using namespace placeholders;

//线程类
class Thread
{
public:
    //用function接收绑定器
    Thread(function<void()> func) : _func(func) {}
    thread start()
    {
        thread t(_func);
        return t;
    }

private:
    function<void()> _func;
};
//线程池类
class ThreadPool
{
public:
    ThreadPool() {}
    ~ThreadPool()
    {
        //释放Thread对象的堆资源
        for (int i = 0; i < _pool.size(); ++i)
        {
            delete _pool[i];
        }
    }
    void startPool(int size)
    {
        for (int i = 0; i < size; ++i)
        {
            //new线程类型并绑定成员函数为线程函数
            _pool.push_back(new Thread(bind(&ThreadPool::runInThread, this, i)));
        }

        for (int i = 0; i < size; ++i)
        {
            _handler.push_back(_pool[i]->start());
        }

        for (thread &t : _handler)
        {
            t.join();
        }
    }

private:
    //定义线程类型的容器
    vector<Thread *> _pool;
    vector<thread> _handler;
    //线程函数
    void runInThread(int id)
    {
        cout << "call runInThread  id " << id << endl;
    }
};
int main()
{
    ThreadPool pool;
    pool.startPool(10);
    return 0;
}