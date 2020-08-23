# const
const用于限定一个变量为只读。
# const定义常量
`const double Pi= 3.14;`

相对于#define,const更加灵活并且可以节省空间.必须初始化.

# const与指针

> 区分常量指针与指针常量(const在`*`前为常量指针),常量指针对象不能变,指针常量指针不能变.

```c++
int a= 10;
int *p=&a;
const int *p=&a;//non-const pointer,const data,常量指针
int* const p=&a;//const pointer,non-const data,指针常量
const int * const p=&a;//const pointer,const data
```

将p看成指针，而`*`为数据，const在p前，则const pointer，const在`*`前，则const data

> 不能使用`void *`指针保存const对象的地址

```c++
const int a=10;
const void* cp=&a; //yes
void* p=&a;        //error
```

> const与迭代器

```c++
const std::vector<int>::iterator iter=v.begin();       //==T* const,const iter
std::vector<int>::const_iterator iter=v.begin(); //==const T*,const data
```

# const与函数
> 令函数返回一个常量值，往往可以降低因人为错误而造成的意外

```c++
const int func();  //无意义
const int* func(); //const data
int* const func(); //const pointer
```

> const修饰函数参数

```c++
void func1(const int a);
void func1(int *const a);
//无意义,以值传入,函数复制参数,本身不会发生变化
```

```c++
void func2(const int* a);
//以地址传入,const data,在函数体内无法修改a
```

```c++
void func3(const int &a);
//以引用传入,const data,在函数体内无法修改a
```

# const与类

> 用const修饰成员函数可操作常量和常对象
>
> 常对象只能访问常成员函数,普通对象可任意访问成员函数
>
> const成员变量必须通过初始化列表初始化

```c++
//test1.cpp
#include<iostream>
using namespace std;

class test
{
    public:
    test(int i):num(i){}//常成员变量通过初始化列表初始化
    void get1()const;//get1是常成员函数
    void get2();     //get2是普通成员函数
    int getnum() const;//常成员函数getnum得到常成员变量
    private:
    const int num;
};
void test::get1()const
{
    cout<<getnum()<<"调用get1()const"<<endl;
}
void test::get2()
{
    cout<<getnum()<<"调用get2()"<<endl;
}
int test::getnum()const
{
    return num;
}

int main(){
    test t1(1);//普通对象t1
    t1.get2();//正确
    t1.get1();//正确
    const test t2(2);//常对象t2
    //t2.get2();//错误
    t2.get1();//正确
    return 0;
}
```

> 常函数内不可修改成员属性
>
> 成员属性前加mutable,在常函数内仍可修改

```c++
//test2.cpp 上例稍作修改
#include<iostream>
using namespace std;
class test
{
    public:
    test(int i):num(i){}
    void get1()const;
    int getnum()const;
    private:
    mutable int num;//mutable int const num报错
};
void test::get1()const
{
    num=2;
    cout<<getnum()<<"调用get1()const"<<endl;
}
int test::getnum()const
{
    return num;
}

int main(){
    test t1(1);
    t1.get1();
    return 0;
}
```

