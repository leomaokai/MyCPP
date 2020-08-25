list是一种物理存储单元上非连续的存储结构

* 链表由一系列结点组成
* 结点中一个存储数据元素的数据域,另一个是存储下一个结点地址的指针域
* `STL`中的链表是一个双向循环链表

list优点:

* 采用动态存储分配,不会造成内存浪费和溢出
* 链表执行插入和删除操作十分方便

缺点:

* 空间和时间额外耗费较大

构造函数

```cpp
#include<list>
list<T> lst;
list(beg,end);
list(n,elem);
list(const list &lst);
```

赋值和交换

```cpp
assign(beg,end);
assign(n,elem);
list& operator=(const list &lst);
swap(lst);
```

大小操作

```cpp
size();
empty();
resize(num);
resize(num,elem);
```

插入和删除

```cpp
push_back(elem);
pop_back();
push_front(elem);
pop_front();
insert(pos,elem);
insert(pos,n,elem);
insert(pos,beg,end);
clear();
erase(beg,end);
erase(pos);
remove(elem);
```

数据存取

```cpp
front();
back();
```

反转和排序

```cpp
reverse();//反转链表
sort();//链表排序默认从小到大
```

