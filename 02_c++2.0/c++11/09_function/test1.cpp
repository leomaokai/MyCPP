//test1.cpp
#include <iostream>
#include <functional>
#include <string>
using namespace std;

int testfunc(int a, int b)
{
    return a + b;
}
class test
{
public:
    void mstr(string str) { cout << str << endl; }
};
int main()
{
    function<int(int, int)> func1 = testfunc;
    cout << func1(20, 30) << endl;
    function<int(int, int)> func2 = [](int a, int b) -> int { return a + b; };
    cout << func2(20, 20) << endl;
    function<void(test *, string)> func3 = &test::mstr;
    func3(&test(), "hello function");
    return 0;
}