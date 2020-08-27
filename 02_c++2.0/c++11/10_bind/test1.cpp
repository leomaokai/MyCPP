//test1.cpp
#include <iostream>
#include <string>
#include <functional>
using namespace std;
//bind特殊用法，参数占位符
using namespace placeholders;

void teststr(string str) { cout << str << endl; }
int testsum(int a, int b) { return a + b; }
class test
{
public:
    void testbind(string str) { cout << str << endl; }
};
int main()
{
    //一般用法
    bind(teststr, "hello bind")();
    cout << bind(testsum, 10, 20)() << endl;
    bind(&test::testbind, test(), "test::testbind()")();
    //参数占位符
    bind(teststr, _1)("hello placeholders");
    cout << bind(testsum, _1, _2)(30, 40) << endl;
    //通过function将绑定器保存
    function<void(string)> func1 = bind(teststr, _1);
    func1("hello bind");
    func1("hello function");
    function<void(test, string)> func2 = bind(&test::testbind, _1, _2);
    func2(test(), "hello test::testbind");
    function<void()> func3 = bind(&test::testbind,test(), "123456");
    func3();
    return 0;
}
