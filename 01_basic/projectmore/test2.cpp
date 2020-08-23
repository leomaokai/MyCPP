//test2.cpp
#include <iostream>
using namespace std;

class book
{
public:
    book(int a = 10, int b = 20) : m_a(a), m_b(b)
    {
        cout << "book(int,int)" << endl;
    }
    ~book()
    {
        cout << "~book()" << endl;
    }
    book(const book &t) : m_a(t.m_a), m_b(t.m_b)
    {
        cout << "book(const book &)" << endl;
    }
    book &operator=(const book &t)
    {
        cout << "operator=()" << endl;
        m_a = t.m_a;
        m_b = t.m_b;
        return *this;
    }

private:
    int m_a;
    int m_b;
};
book b1(10, 10); //1 book(int,int)
int main()
{
    book b2(20, 20);               //3 book(int,int)
    book b3 = b2;                  //4 book(const book &)
    static book b4 = book(30, 30); //5 book(int,int)
    b2 = book(40, 40);             //6 book(int,int) 7 opeartor=() 8 ~book()
    b2 = (book)(50, 50);           //9 book(int,int) 10 opeartor=() 11 ~book()
    b2 = 60;                       //12 book(int,int) 13 opeartor=() 14 ~book()
    book *p1 = new book(70, 70);   //15 book(int,int)
    book *p2 = new book[2];        //16 book(int,int) 17 book(int,int)
    //book *p3=&book(80,80);
    const book &p4 = book(90, 90); //18 book(int,int)
    delete p1;                     //19 ~book()
    delete[] p2;                   //20 ~book() 21 ~book()
}
book b5(100, 100); //2 book(int,int)
