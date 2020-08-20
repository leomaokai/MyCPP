# new/delete

`malloc/free`是C/C++的标准库函数,`new/delete`是C++的运算符,它们都用于申请动态内存和释放内存

对于非内部数据类型的对象而言,使用`malloc/free`无法满足动态对象的要求.

因此,C++需要一个能完成动态内存分配和初始化工作的运算符`new`,以及一个能清理于释放内存工作的运算符`delete`.

# 使用new与delete

```c++
//通过new分配的内存
int* a=new int;
//通过将变量地址赋给指针
int b;
int* c=&b;
```

着两种情况都是将int变量的地址赋给指针.

我们称a指向一个数据对象,通过new分配内存的方法使程序在管理内存方面有更大的控制权.

```c++
//使用new创建动态数组
int* arr1=new int[10];
//10个未初始化的int
int* arr2=new int[10]();
//10个初始化为0的int
```

```c++
//使用delete释放内存
delete a;
delete [] arr;
```

注意规则:

* 不要使用delete来释放不是new分配的内存
* 不要使用delete释放同一块内存两次
* 如果使用new[]为数组分配内存,则应使用delete[]来释放内存
* 如果使用new[]为一个实体分配内存,则应使用delete释放
* 对空指针使用delete是安全的

# 重载new和delete

为了实现某些应用程序对内存分配的特殊需求,比如使用关键字new将对象放置在特定的内存空间中,应用程序需要重载new运算符和delete运算符以控制内存分配的过程

```c++
string *str=new string("cumt");//分配并初始化一个string对象
string *arr=new string[10];//分配10个默认初始化的string对象
```

`new`实际执行了三步操作:

* `new`表达式调用一个名为`operator new`(或者`operator new[]`)的标准库函数.该函数分配一块足够大的,原始的,未命名的内存空间以便存储特定的对象或对象数组
* 编译器运行相应的构造函数以构造这些对象,并为其传入初始值
* 对象被分配了空间并构造完成,返回一个指向该对象的指针

```c++
delete str;//销毁*str,然后释放str指向的内存空间
delete [] arr;//销毁数组中的元素,然后释放对应的内存空间
```

`delete`执行两步操作:

* 对指针所指的对象或数组中的元素执行对应的析构函数
* 编译器调用名为`operator delete`(或者`operator delete[]`)的标准库函数释放内存空间

如果应用程序希望控制内存分配的过程,则它们需要定义自己的`operator new`函数和`operator delete`函数.

# 问题

* 忘记delete内存
* 使用已经释放掉的对象
* 同一块内存释放两次

使用智能指针可避免这些问题