vector与数组相似,可称为单端数组

但是数组是静态空间，而vector可以2倍动态扩展

对容器进行连续的插入或者删除操作,一定要更新迭代器,否则第一次insert或者erase完成后迭代器会失效

构造函数

```cpp
#include<vector>
vector<T> v;
vector(const vector &vec);
vector(v.begin(),v.end());//将v区间中的元素拷贝给本身
vector(n,elem);//构造函数将n个elem拷贝给本身
```

赋值函数

```cpp
vector& operator=(const vector &vec);
assign(beg,end); //将[beg,end)区间中的数据拷贝赋值给本身
assign(n,elem); //将n个elem拷贝赋值给本身
```

容量和大小

```cpp
empty();//判断容器是否为空
capacity();//容器的容量
size();//返回容器中元素的个数

resize(int num);//扩容
//重新指定容器长度为num,若容器变长,则以默认值填充新位置
//如果容器变短,则末尾超出容器长度的元素被删除
resize(int num,elem);
//重新指定容器长度为num,若容器变长,则以elem填充新位置
//如果容器变短,则末尾超出容器长度的元素被删除
```

插入和删除

```cpp
push_back(ele);//尾部插入元素ele
pop_back();//删除最后一个元素
insert(const_iterator pos,ele);//迭代器指向位置pos插入元素ele,返回新的迭代器
insert(const_iterator pos,int n,ele);//迭代器指向位置插入n个元素ele
erase(const_iterator pos);//删除迭代器指向的元素
erase(const_iterator start,const_iterator end);//删除区间中的元素
clear();//删除容器中的所有元素
```

数据存取

```cpp
at(int idx);//返回索引idx所指的数据
operator[];//返回索引idx所指的数据
front();//返回容器中的第一个数据元素
back();//返回容器中最后一个数据元素
```

互换容器

```cpp
swap(vec);//将vec与本身的元素互换
```

预留空间

```cpp
reserve(int len);//容器预留len个元素长度,预留位置不初始化,元素不可访问
```

