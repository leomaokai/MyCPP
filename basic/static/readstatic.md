# static

static关键字可以修饰不同的类型,如普通变量,普通函数,成员变量,成员函数.修饰不同的类型具有不同的含义.

# static与普通变量

当变量声明为static时,修改了变量的存储区域和生命周期,使变量存储在静态区,空间只分配一次.

```c++
//countadd.cpp
#include<iostream>
using namespace std;
void countadd(){
    static int count = 0;//int count = 0;
    cout<<count<<" ";
    count++;
}
int main(){
    for(int i=0;i<5;i++)
        countadd();
    return 0;
}
```

```c++
0 1 2 3 4         // 0 0 0 0 0
```

# static与普通函数

当函数定义为static时,表明该函数的作用范围,仅在定义该函数的文件内才能使用.

```c++
//test.cpp
#include<iostream>
#include"myhead.hpp"
using namespace std;
void test()  //static void test()
{
    cout<<"使用了test()"<<endl;
}
```

```c++
//testmain.cpp
#include<iostream>
#include"myhead.hpp"
using namespace std;
int main(){
    test();
    return 0;
}
```

```c++
//myhead.hpp
#ifndef MYHEAD_H
#define MYHEAD_H
void test();
#endif
```

```
g++ -o testmain testmain.cpp test.cpp #编译成功
#将test()前声明static后编译失败
```

# static与类

## 静态成员变量

静态成员变量使类的所有对象只保存一个该变量,且不需要生成对象就可以访问该成员.静态变量不能使用构造函数初始化.

```c++
//stu.cpp
#include<iostream>
using namespace std;
class stu
{
public:
    static int m_id;
};
int main()
{
    stu stu1;
    stu stu2;
    stu1.m_id=10;
    stu2.m_id=20;
    cout<<stu1.m_id<<" "<<stu2.m_id;
    return 0;
}
```

多个对象对静态成员变量赋值,但编译失败.

```c++
//stu.cpp
#include<iostream>
using namespace std;
class stu
{
public:
    static int m_id;
};
int stu::m_id = 1;
int main()
{
    stu stu1;
    cout<<stu1.m_id;//对象stu1直接调用静态成员变量
}
```

```
输出结果:  1  
```

## 静态成员函数

静态成员函数类似于静态成员变量,他们都不依赖于类的对象.

静态成员函数仅能访问静态成员变量或其他静态成员函数.

```c++
//tch.cpp
#include<iostream>
using namespace std;
class tch
{
    public:
    static int m_score;
    //int m_score;
    static void math()
    {
        cout<<"my math is "<<m_score<<endl;
    }
};
int tch::m_score = 100;
int main()
{
    tch::math();//直接调用静态成员函数
    return 0;
}
```

```
输出: my math is 100
若将成员变量声明为非静态则编译失败.
```

## 静态类对象

静态类对象于静态变量类似,存在于整个程序生命周期.

```c++
//person.cpp
#include<iostream>
using namespace std;
class person
{
    public:
    person()
    {
        cout<<"调用构造函数"<<endl;
    }
    ~person()
    {
        cout<<"调用析构函数"<<endl;
    }
};
int main()
{
    int i=0;
    if(i==0)
        static person p;
        //person p;
    cout<<"结束if()"<<endl;
    return 0;
}
```

```
调用构造函数   //调用构造函数
结束if()      //调用析构函数
调用析构函数   //结束if()
```

