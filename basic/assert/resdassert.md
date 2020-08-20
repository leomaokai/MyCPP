# assert

assert断言,是宏.

> C语言中<assert.h>(C++<sassert>)头文件由assert()宏组成.接受一个整型表达式作为参数,其作用是如果条件返回错误,则终止程序执行,并会显示失败的测试,包含测试的文件名和行号.

# assert的用法

```c++
//test.cpp
#include<iostream>
//#define NDEBUG
#include<cassert>
using namespace std;
int main()
{
    int a=10;
    a=5;
    assert(a==10);
    cout<<"a= "<<a<<endl;
    return 0;
}
```

```
Assertion failed: a==10, file test.cpp, line 9
```

`assert()`自动标识文件和出错的行号.

可以通过定义`#define NDEBUG`关闭`assert()`机制

如上述代码若将`//#define NDEBUG`的注释去掉,则输出`a = 5`
