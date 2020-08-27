# constexpr

常量表达式是指值不会改变并且在编译过程中就能得到计算结果的表达式

用常量表达式初始化的const对象也是常量表达式

如何分辨一个初始值是不是常量表达式?

C++11新标准规定:允许将变量声明为`constexpr`类型以便由编译器来验证变量的值是否是一个常量表达式.

声明为`constexpr`的变量一定是一个常量

```c++
constexpr int a = 10;
constexpr int b = a+1;
```

不能使用普通函数作为`constexpr`变量的初始值,但新标准允许定义一种特殊的`constexpr`函数,这种函数应该足够简单以使得编译时就可以计算其结果,这样就能用`constexpr`函数去初始化`constexpr`变量.

```c++
constexpr int getsize(){return 10;}
constexpr int c=getsize();
```

`constexpr`声明中如果定义了一个指针,限定符`constexpr`仅对指针有效,与指针所指的对象无关.