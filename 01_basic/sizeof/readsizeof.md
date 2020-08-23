# sizeof

# sizeof与普通变量

```c++
char str[]="cumt";
char* p=str;
int n=10;
sizeof(str);//5
sizeof(p);//4
sizeof(n);//4
void func(char c[10])
{
    sizeof(c);//4
}
void* a=malloc(10);
sizeof(a);//4
```

`sizeof(str)=strlen(str)+1`

指针大小为4

整型大小为4

数组是"传址"的,指针大小为4

32位系统下无论何种指针大小都为4

# sizeof与类对象

```c++
class A
{
    public:
    int i;
    short s;
    char c;
};
class B
{
    public:
    int i;
    char c1;
    char cw;
};
sizeof(int);//4
sizeof(short);//2
sizeof(char);//1
sizeof(A);//8
sizeof(B);//8
```

32位系统中`sizeof(A)=sizeof(B)`这是因为字节对齐引起的.

> 字节对齐的细节和编译器实现有关,结构体的总大小一般为最宽基本类型成员大小的整数倍.

```c++
class A
{
    public:
    virtual void func();
    int a;
};
class B:public A
{
    public:
    virtual void func();
    int b;
    static int c;
};
class C:virtual public B
{};
sizeof(A);//8
sizeof(B);//12
sizeof(C);//16
```

A中由于它有虚函数,所以占用的内存除了一个整型变量之外,还有一个隐含的虚表指针成员,所以一共为8字节

B是A的子类,比A多了一个整型成员,所以12字节

静态成员的空间不在类的实例中,而像全局变量一样在静态存储区中,因此B为12

C是B的子类.因为虚继承了B,编译器为该类安插了一个指向父类的指针,指针大小为4,所以C为16

# sizeof与strlen有哪些区别

* sizeof是运算符,计算对象所占的字节大小,其值在编译,参数可以是数组,指针,类型,对象,函数等
* strlen是函数,计算字符串的具体长度即字符个数,参数必须是字符型指针(char*).
* strlen计算的是字符串的实际长度，遇到`\0`即停止；sizeof 计算整个字符串所占内存字节数的大小，当然`\0`也要+1计算

```c++
#include<string.h>
char str1[10]="cumt";
sizeof(str1);//10
strlen(str1);//4
char str2[]="hello\\0";
sizeof(str2);//8
strlen(str2);//7
str3[]="hello\\\0";
sizeof(str3);//8
strlen(str3);//6   
```

**sizeof**不能计算字符串的长度,尤其是按指针传入,需要计算字符串长度时最好用**strlen**替换.

# 总结

* 在32位系统中,无论何种指针大小总为4
* 一个类中，虚函数本身、成员函数（包括静态与非静态）和静态数据成员都是不占用类对象的存储空间
* 对于包含虚函数的类,会有一个虚指针
* 虚继承会包含一个指向父类的指针
* 求结构体大小时注意对齐方式
* 求字符串大小时注意是否传入指针





