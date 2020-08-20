//test1.cpp
#include <iostream>  
using namespace std;

template <typename T>
class mysmartptr
{
public:
    mysmartptr(T *ptr = nullptr) : mptr(ptr)
    {
        cout << "mysmartptr()" << endl;
    }
    ~mysmartptr()
    {
        delete mptr;
        cout << "~mysmartptr()" << endl;
    }
    T &operator*() { return *mptr; }
    T *operator->() { return mptr; }

private:
    T *mptr;
};
int main()
{
    mysmartptr<int> ptr1(new int);
    *ptr1 = 20;
    return 0;
}