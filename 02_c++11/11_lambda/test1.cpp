//test1.cpp
#include <iostream>

using namespace std;
int main()
{
    auto func1 = []() -> void { cout << "hello lambda" << endl; };
    func1();
    int a = 10, b = 30;
    auto func2 = [&]() {int tmp=a;
                         a=b;
                         b=tmp; };
    func2();
    cout << a << " " << b << endl;
    return 0;
}