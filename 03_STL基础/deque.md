`deque`可称为双端数组,可以对头端进行插入删除操作

`deque`与vector区别:

* `vector`对于头部的插入删除效率低,数据量越大,效率越低
* `deque`相对而言,对头部的插入删除速度比`vector`快
* `vector`访问元素时的速度比`deque`快,这和两者内部实现有关

`deque`内部工作原理

* `deque`内部有个中控器,维护每段缓冲区的地址,缓冲区中存放真实数据

构造函数

```cpp
#include<deque>
deque<T> deq;
deque(beg,end);
deque(n,elem);
deque(const deque &deq);
```

赋值操作

```cpp
deque& operator=(const deque &deq);
assign(beg,end);
assign(n,elem);
```

大小操作

```cpp
empty();
size();
resize(num);
resize(num,elem);
```

插入和删除

```cpp
push_back(elem);//在容器尾部插入数据
push_front(elem);//在容器头部插入数据
pop_back();//删除容器最后一个数据
pop_front();//删除容器第一个数据

insert(pos,elem);
insert(pos,n,elem);
insert(pos,beg,end);
clear();
erase(beg,end);//删除区间的数据,返回下一个数据的位置
erase(pos);//擅长pos位置的数据,返回下一个数据的位置
```

数据存取

```cpp
at(int idx);
operator[];
front();//返回容器中的第一个数据
back();//返回容器中的最后一个数据
```

排序

```cpp
#include<deque>
#include<algorithm>
sort(iterator beg,iterator end);
```

