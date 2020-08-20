# inline

函数调用都有一定的开销(建立调用,传递参数,跳转到函数代码并返回).

使用宏使代码内联,可以避免这样的开销.另一种方法则是内联函数.

内联函数的编译代码与其他程序代码"内联"起来.

当调用内联函数时,程序使用内联代码代替函数调用.

# inline与常规函数

内联函数的运行速度比常规函数稍快.(代价是占用更多内存)

```c++
//square.cpp
#include<iostream>
using namespace std;
inline double square(double a){return a*a;}
int main(){
    double a=0.5;
    cout<<"The first square's area is "
        <<square(1.5)<<endl;
    //square(1.5){return 1.5*1.5;}
    cout<<"The second square's area is "
        <<square(1+0.5)<<endl;
    //square(1+0.5){return (1+0.5)*(1+0.5;)}
    cout<<"The third square's area is "
        <<square(++a)<<endl;
    //square(++a){return (a+1)*(a+1);}
    cout<<"now a = "<<a<<endl;
    return 0;
}
```

```
The first square's area is 2.25
The second square's area is 2.25
The third square's area is 2.25
now a = 1.5
```

>将函数作为内联函数时要注意,编译器一般不内联包含循环,递归等复杂操作的内联函数.

# inline与宏

C语言使用预处理器语句`#define`来提供宏,这是内联代码的原始实现.

但是,宏不能按值传递,而是通过文本替换来实现的.

```c++
//SQUARE.cpp
#include<iostream>
using namespace std;
#define SQUARE(X) ((X)*(X))
int main(){
    double a=1.5;
    cout<<"The first = "<<SQUARE(2.5)<<endl;
    //(2.5)*(2.5)
    cout<<"The second = "<<SQUARE(1+1.5)<<endl;
    //(1+1.5)*(1+1.5)
    cout<<"The third = "<<SQUARE(a++)<<endl;
    //(1.5+1+1)*(1.5+1+1)
    cout<<"now a = "<<a<<endl;
    return 0;
}
```

```
The first = 6.25
The second = 6.25
The third = 3.75//1.5*2.5
now a = 3.5
```

> 宏SQUARE(++a)中a递增了两次,而内联函数中a只递增一次

# inline与类

在类声明中定义的的函数,**除了虚函数**其他函数都会自动隐式地当成内联函数.类外定义的函数需要显示内联.类声明常将短小地成员函数作为内联函数.

内联函数的特殊规则要求每个使用它们的文件中都对其进行定义.将内联定义放在定义类的头文件中即可实现.

```c++
//myhead.hpp
#ifndef MYHEAD_H
#define MYHEAD_H
class stu
{
	public:
	int getid(int a){return a;}//定义即内联
	inline int getage(int b);//声明内联
};
#endif
```

```c++
//stu.cpp
#include"myhead.hpp"
#include<iostream>
using namespace std;
inline int stu::getage(int b){
	return b;
}
int main(){
	stu bob;
	cout<<"his id is "<<bob.getid(111)<<endl;
	cout<<"his age is "<<bob.getage(20)<<endl;
	return 0;
}
```

```
his id is 111
his age is 20
```

## virtual与inline

虚函数在不表现多态性时可以内联

内联发生在编译期,而虚函数的多态性表现在运行时.

当编译器知道所调用的对象是哪个类时,虚函数可以内联

```c++
//person.cpp
#include<iostream>
using namespace std;
class person
{
    public:
    inline virtual void who()
    {
        cout<<"he is a person"<<endl;
    }
    virtual ~person(){}//为多态基类声明virtual析构函数
};
class stu : public person
{
    public:
    void who() //隐式内联
    {
        cout<<"he is a student"<<endl;
    }
};
int main(){
    person bob;
    bob.who();//bob属于person,可以内联
    person *tom = new stu();
    tom->who();//虚函数通过指针调用,不可内联
    delete tom;
    tom = nullptr;
    return 0;
}
```

