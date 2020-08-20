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