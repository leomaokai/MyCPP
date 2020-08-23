//test3.cpp
#include <iostream>
#include <string>
using namespace std;
//自己实现一个function
//原理：在类中用函数指针保存需要实例化的函数
void testfunc(string str);
int testsum(int a, int b);

template <typename FTy>
class myfunction
{
};

template <typename R, typename... T>
//R为函数返回类型，T...可变参的类型参数
class myfunction<R(T...)>
{
public:
    using PFUNC = R (*)(T...);
    myfunction(PFUNC pfunc) : _pfunc(pfunc) {}
    R operator()(T... arg)
    {
        return _pfunc(arg...);
    }

private:
    PFUNC _pfunc;
};

int main()
{
    myfunction<void(string)> func1(testfunc);
    func1("hello myfunction");
    myfunction<int(int, int)> func2(testsum);
    cout << func2(15, 10) << endl;
    return 0;
}

void testfunc(string str)
{
    cout << str << endl;
}
int testsum(int a, int b)
{
    return a + b;
}
