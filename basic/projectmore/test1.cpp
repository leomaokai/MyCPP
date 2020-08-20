//test1.cpp

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

private:
    int m_a;
};

int main()
{
    // book b1;      //book(int)
    // book b2(b1);  //book(const book &)
    // book b3 = b1; //book(const book &)
    // //book(20)生成临时对象 生存周期为所在的语句
    // book b4 = book(20); //book(int)
    // //与book b4(20);无区别
    // /*C++编译器对于对象构造的优化:用临时对象生成新对象时,
    // 临时对象就不产生了,直接构造新对象就可以了.*/
    // cout << endl;
    // b4 = b2;       //operator=()
    // b4 = book(40); //book(int) operator=() ~book() 显示生成临时对象赋值
    // cout << endl;
    // b4 = (book)50; //构造函数含有int类型,可显示生成临时对象赋值
    // cout << endl;
    // b4 = 50; //隐式生成临时对象赋值
    // cout << endl;
    // book *p=&book(20);//p指向一个析构的临时变量
    // const book &ref = book(30); //book(int) 引用变量引用临时变量安全
    // cout << endl;

    return 0;
}