# 智能指针

智能指针其实就是一个模板类，将原始指针封装到类中，可由析构函数自动释放资源。

C++11提供了两种智能指针

不带引用计数的智能指针：auto_ptr  scoped_ptr  unique_ptr

带引用计数的智能指针：shared_ptr   weak_ptr

智能指针浅拷贝问题：多个智能指针多次释放同一个资源

**不带引用计数的智能指针:**

* auto_ptr在处理浅拷贝的问题上，直接把前一个指针置为nullptr，只让最后一个指针持有资源
* scoped_ptr与unique_ptr则直接删除了拷贝构造函数和赋值重载函数
* unique_ptr提供了带右值引用参数的拷贝构造和赋值

**带引用计数的智能指针：**

当多个智能指针指向同一个资源的时候，每个智能指针都会给资源的引用计数加1，当一个智能指针析构时，会使资源的引用计数减1，因此，只有最后一个智能指针析构时，资源的引用计数才能减到0，说明该资源可以释放了。

* shared_ptr智能指针的资源引用计数器在内存的heap堆上，一般称为强智能指针，可改变资源的引用计数
* weak_ptr被称为弱智能指针，不能改变资源的引用计数也不能直接使用资源
* 定义对象的时用强智能指针，引用对象时用弱智能指针

# 交叉引用问题

```cpp
//test3.cpp
#include <iostream>
#include <memory>
using namespace std;

class B;
class A
{
public:
    A() { cout << "A()" << endl; };
    ~A() { cout << "~A()" << endl; }
    void testa() { cout << "使用A" << endl; }
    weak_ptr<B> _ptrb; //引用B的智能指针
};
class B
{
public:
    B() { cout << "B()" << endl; }
    ~B() { cout << "~B()" << endl; }
    void testb()
    {
        //_ptra->testa();//弱智能指针无法直接使用资源
        shared_ptr<A> sp = _ptra.lock(); //将弱智能指针提升为强智能指针
        if (sp != nullptr)
            sp->testa();
    }
    weak_ptr<A> _ptra; //引用A的智能指针
};
int main()
{
    shared_ptr<A> pa(new A()); //定义A对象的智能指针
    shared_ptr<B> pb(new B()); //定义B对象的智能指针
    pa->_ptrb = pb;
    pb->_ptra = pa;
    pb->testb();
    cout << pa.use_count() << endl;
    cout << pb.use_count() << endl;
    return 0;
}
```

```
A()
B()
使用A
1
1
~B()
~A()
```

# 线程安全问题

```cpp
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
```

# 自定义删除器
```cpp
//test5.cpp
#include <iostream>
#include <memory>
#include <functional>
using namespace std;

//智能指针默认资源释放方式:  delete ptr
//并不是所有资源delete
//数组:delete [] ptr;
//文件:fclose(FILE*)
template <typename T>
class Mydeletor
{
public:
    void operator()(T *ptr) const
    {
        delete[] ptr;
        cout << "delete []" << endl;
    }
};

int main()
{
    //自定义类删除器
    unique_ptr<int, Mydeletor<int>> ptr1(new int[10]);

    //通过lambda表达式定义删除器
    unique_ptr<FILE, function<void(FILE *)>> ptr2(fopen("test5.txt", "a"),
                                                  [](FILE *fp) -> void {
                                                      fclose(fp);
                                                      cout << "fclose()" << endl;
                                                  });
    return 0;
}
```