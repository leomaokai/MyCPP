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