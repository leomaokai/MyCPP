`set/multiset`属于关联式容器,底层结构是用二叉树实现

* set不允许容器中有重复的元素
* `multiset`允许容器中有重复的元素

构造和赋值

```cpp
#include<set>
set<T> st;
set(const set &st);
set& operator=(const set &st);
```

大小和交换

```cpp
size();
empty();
swap(st);
```

插入和删除

```cpp
insert(elem);//插入数据自动排序
clear();
erase(pos);
erase(beg,end);
erase(elem);
```

查找和统计

```cpp
find(key);//若key存在,返回迭代器,若不存在,返回set.end();
count(key);//统计key的元素个数, 对于set结果为0或1
```

如果不允许插入重复数据可以利用set

如果需要插入重复数据利用`multiset`

set容器默认排序从小到大,利用函数对象可以改变排序规则

