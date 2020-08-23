//test3.cpp
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
    friend book getbookma(book t);

private:
    int m_a;
};
book getbookma(book t)
{
    int val = t.m_a;
    book tmp(val);
    return tmp;
}
int main()
{
    book b1;
    book b2;
    b2=getbookma(b1);
}