# this

每个非静态成员函数(包括构造函数和析构函数)都有一个`this`指针,`this`指针指向用来调用成员函数的对象.

# this与对象

当对象调用成员函数时,该对象的地址会被作为隐藏参数传给`this`.

在类的非静态成员函数中返回对象本身时,直接使用`return *this`

在成员函数内使用`this`可方便实现函数内操作该对象.

```c++
//stu.cpp
#include<iostream>
using namespace std;
class stu
{
    public:
    stu(int score):m_score(score){}
    const stu &compare(const stu &s) const
    {
        if(s.m_score>m_score)
            return s;
        else
            return *this;
    }
    int getscore()const
    {
        cout<<"The most score is "<<this->m_score;
    }
    private:
    const int m_score;
};
int main()
{
    stu stu1(99);
    stu stu2(59);
    stu1.compare(stu2).getscore();
    return 0;
}
```

```c++
输出:The most score is 99
//stu1.compare(stu2).getscore();
//stu1.compare(stu2)中的return *this返回了自身对象stu1
//stu1.getscore()中return this->m_score返回了自身m_score的值.
```

```c++
const stu &compare(const stu &s) const;
//该对象隐式地访问一个对象(stu1)而显示地访问另一个对象(stu2),并返回其中一个对象的引用.
//括号中的const表明该对象不会修改被显示访问的对象
//括号外的const表明该对象不会修改被隐式访问的对象
//因为返回const对象的引用,因此返回类型也应为const引用.
```

# this与const

当对象调用成员函数时,编译器会**优先**把对象赋值给`this`指针.

对于`非const函数`,`this = A * const`,这意味着`this`是一个指针常量,我们无法对`this`进行修改.

对于`const函数`,`this = const  A * const`,这意味着我们不仅不能修改`this`,也不能修改`*this`

```c++
//person.cpp
#include<iostream>
using namespace std;
class person
{
    public:
    person(int age):m_age(age){}
    void getage()const
    {
        cout<<"He is "<<this->m_age;
    }
    person &addage(int addage)//person &addage(int addage)const
    {
        m_age+=addage;
        return *this;
    }
    private:
    int m_age;
};
int main()
{
    person Tom(18);
    Tom.addage(2).getage();
    return 0;
}
```

```c++
输出:He is 20   //若addage()函数后加const则编译失败
```



