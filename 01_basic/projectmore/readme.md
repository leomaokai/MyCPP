# 对象优化

关键:

* C++编译器对于对象构造的优化:用临时对象生成新对象时,临时对象就不产生了,直接构造新对象就可以了.
* 在main中有函数对象返回对象时,main栈帧会用一个临时对象接收函数返回对象

总结:

* 函数传参过程中优先按**引用**传递
* 函数返回对象时优先返回**临时对象**
* 接收返回值是对象的函数调用的时候,优先按**初始化**方式接收

```cpp
//test4.cpp 对test3.cpp的优化
#include <iostream>
using namespace std;

class book
{
public:
    book(int a = 10) : m_a(a)
    {
        cout << "book(int)" << endl;
    }
    ~book()
    {
        cout << "~book()" << endl;
    }
    book(const book &t) : m_a(t.m_a)
    {
        cout << "book(const book &)" << endl;
    }
    book &operator=(const book &t)
    {
        cout << "operator=()" << endl;
        m_a = t.m_a;
        return *this;
    }
    friend book getbookma(book &t);

private:
    int m_a;
};

//优化代码关键为编译器对临时变量的自动优化
book getbookma(book &t) //传引用
{
    int val = t.m_a;
    return book(val); //返回临时变量
}
int main()
{
    book b1;
    book b2 = getbookma(b1); //用初始化取代赋值
    return 0;
}
```

```
test(int)
test(int)
~test()
~test()
```

