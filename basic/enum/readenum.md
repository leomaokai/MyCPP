# enum

`enum`可创建符号常量.

# enum与枚举

`enum`定义的新类型称为枚举.其语法类似于`struct`

```c++
enum color {red,orange,yellow,green,blue};
```

>color为枚举
>
>red,orange,yellow等称为符号常量,对应整数值0~4.
>
>枚举只定义了赋值运算符,无法进行算术运算.
>
>枚举量是整型,可转换为int型,但int型不能自动转换为枚举类型
>
>可以强制类型转换将int转为枚举类型(枚举取值范围内)

```c++
//test01.cpp
#include<iostream>
using namespace std;
enum color {red,orange,yellow,green,blue = 10};
//enum color {red = 2,orange = 3};//显示设置枚举量的值
int main()
{
    color col;
    col = red;
    //++col;//error
    int num = 2+red;//red转换为0
    //col = 2;//error
    //col = red + orange;//error
    col = color(1);//强制类型转换
    col = color(9);//合法.9位于枚举定义的取值范围内
    return 0;
}
```

# enum与struct

```c++
enum color1 {red,orange,yellow};
enum color2 {red,orange}; 
//枚举量冲突,无法通过编译
```

```c++
//enum_struct.cpp
//enum_struct.cpp
#include<iostream>
using namespace std;
enum color1 {red,orange,yellow};
//enum color2 {red,orange}; 
struct color
{
    enum color2 {red,orange}; 
};//用结构体限制枚举的作用域
int main()
{
    return 0;
}
```

# 枚举类

通过`struct`可限制枚举的作用域而消除枚举量冲突.

C++11提供了新的方法枚举类

消除枚举量命名冲突

```c++
enum class color1
{
    red =5,
    orange,
    blue
};
enum class color2
{
    red =10,
    orange,
    blue
};//可以用struct代替class
```

作用域内枚举不能隐式转换为整型

```c++
//enum_class.cpp
#include<iostream>
using namespace std;
enum color1{red = 5,orange,blue};
enum class color2
{
    red=20,
    orange,
    blue
};
int main()
{
    color1 col1=red;
    int a = col1;
    color2 col2=color2::red;//使用枚举类
    //int a=col2;//error无法隐式转换
    int b = int(color2::red);//显示转换
    //int c = static_cast<int>(col2);//强制转
    cout<<a<<b;
    return 0;
}
```

```
520
```

通过指定类型存储enum

```c++
enum class :char color3
{
    RED='r',
    BLUE='b'
};
```

# 类与枚举

在类内声明常量时

可以使用枚举

可通过const,但const只有在创建对象时才表现常量

通过static与const

```c++
class year
{
    public:
    enum {month = 12};
    //static const int month = 12;
    int mon[month];
};
```

