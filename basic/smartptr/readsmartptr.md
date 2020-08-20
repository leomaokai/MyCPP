# 智能指针

为了更容易地使用动态内存,新的标准库提供了两种智能指针类型来管理动态内存.

智能指针的行为类似常规指针,重要的区别是它负责自动释放所指的对象.

`shared_ptr` 允许多个指针指向同一个对象

`unique_ptr` 独占所指向的对象

智能指针定义在`memory`头文件中

更为详细的智能指针见c++11文件夹

# shared_ptr

智能指针是模板

```c++
shared_ptr<string> p1;//shared_ptr,可以指向string
shared_ptr<list<int>> p2;//shared_ptr,可以指向int的list
```

智能指针的使用方式与普通指针类似

# make_shared函数

最安全的分配和使用动态内存的方法是调用一个名为`make_shared`的标准库函数.此函数在动态内存中分配一个对象并初始化它,返回指向此对象的`shared_ptr`.

```c++
//指向一个值为42的int的shared_ptr
shared_ptr<int> p3 = make_shared<int>(42);
//p4指向一个值为"99999"的string
shared_ptr<string> p4 = make_shared<string>(5,'9');
//p5指向一个值初始化为0的int
shared_ptr<int> p5 = make_shared<int>();
```

我们通常用`auto`定义一个对象来保存`make_shared`的结果

```c++
//p6指向一个动态分配的空vector<string>
auto p6 = make_shared<vector<string>>();
```

# shared_ptr的拷贝和赋值

当进行拷贝或赋值操作时,每个`shared_ptr`都会记录有多少个其它的`shared_ptr`指向相同的对象

```c++
auto p = make_shared<int>(42);
auto q(p);//p和q指向相同的对象
```

我们可以认为每个`shared_ptr`都有一个关联的计数器,通常称其为引用计数.无论何时我们拷贝一个`shared_ptr`,计数器都会递增.

当我们给`shared_ptr`赋予一个新值或是被销毁时,计数器会递减

# shared_ptr的销毁

一旦一个`shared_ptr`的计数器变为0,它就会自动释放它所管理的对象

`shared_ptr`通过析构函数完成销毁工作.

当动态对象不再被使用时,`shared_ptr`类会自动释放动态对象,这一特性使得动态内存的使用变得非常容易.

# unique_ptr

一个`unique_ptr`"拥有"它所指向的对象,与`shared_ptr`不同,某个时刻只能有一个`unique_ptr`指向一个给定的对象.当`unique_ptr`被销毁时,它所指向的对象也被销毁.

```c++
unique_ptr<double> p1;//可以指向一个double的unique
unique_ptr<int> p2(new int(42));//p2指向一个值为42的int
```

由于一个`unique_ptr`拥有它所指向的对象,因此它不支持普通的拷贝与赋值操作.

# weak_ptr

`weak_ptr`是一种不控制所指向对象生存期的智能指针,它指向由一个`shared_ptr`管理的对象.将一个`weak_ptr`绑定到一个`shared_ptr`不会改变`shared_ptr`的引用计数.