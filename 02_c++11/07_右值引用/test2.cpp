//test2.cpp

#include <iostream>
#include <string.h>
using namespace std;

class book
{
public:
    book(const char *name = nullptr)
    {

        cout << "book()" << endl;
        if (name != nullptr)
        {
            m_name = new char[strlen(name) + 1];
            strcpy(m_name, name);
        }
        else
        {
            m_name = new char[1];
            *m_name = '\0';
        }
    }
    ~book();
    //带左值引用参数的拷贝构造函数
    book(const book &tmp);
    //带右值引用参数的拷贝构造函数
    book(book &&tmp);
    //带左值引用参数的赋值重载函数
    book &operator=(const book &tmp);
    //带右值引用参数的赋值重载函数
    book &operator=(book &&tmp);
    const char *c_str() const { return m_name; }

private:
    char *m_name;
};
book getbookname(book &bookname)
{
    const char *name = bookname.c_str();
    book tmp(name);
    return tmp;
}

int main()
{
    book b1("计算机网络");
    book b2;
    b2=getbookname(b1);
    cout << b2.c_str() << endl;
    return 0;
}

book::~book()
{
    cout << "~book()" << endl;
    delete[] m_name;
    m_name = nullptr;
}
//带左值引用参数的拷贝构造函数
book::book(const book &tmp)
{
    cout << "book(const book &)" << endl;
    m_name = new char[strlen(tmp.m_name) + 1];
    strcpy(m_name, tmp.m_name);
}
//带右值引用参数的拷贝构造函数
book::book(book &&tmp)
{
    cout << "book(book &&)" << endl;
    m_name = tmp.m_name;
    tmp.m_name = nullptr;
}
//带左值引用参数的赋值重载函数
book &book::operator=(const book &tmp)
{
    cout << "operator=(const book &)" << endl;
    if (this == &tmp)
        return *this;

    delete[] m_name;

    m_name = new char[strlen(tmp.m_name) + 1];
    strcpy(m_name, tmp.m_name);
    return *this;
}
//带右值引用参数的赋值重载函数
book &book::operator=(book &&tmp)
{
    cout << "operator=(book &&)" << endl;
    if (this == &tmp)
        return *this;

    delete[] m_name;

    m_name = tmp.m_name;
    tmp.m_name = nullptr;
    return *this;
}