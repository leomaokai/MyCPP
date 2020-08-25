map

* map中所有元素都是pair
* pair中第一个元素为key,起到索引作用,第二个元素为value
* 所有元素会根据元素的键值自动排序
* map/multimap属于**关联式容器**，底层结构是用二叉树实现
* 可以利用key值快速找到value

map不允许有重复key值元素

multimap允许容器中有重复key值元素

构造赋值

```cpp
#include<map>
map<T1,T2> mp;
map(const map &mp);
map& operator=(const map &mp);
```

大小和交换

```cpp
size();
empty();
swap(st);
```

插入和删除

```cpp
insert(elem);
clear();
erase(pos);
erase(beg,end);
erase(key);
//插入方式
map<int, int> m;
//第一种插入方式
m.insert(pair<int, int>(1, 10));
//第二种插入方式
m.insert(make_pair(2, 20));
//第三种插入方式
m.insert(map<int, int>::value_type(3, 30));
//第四种插入方式(常用)
m[4] = 40; 
```

查找和条件

```cpp
find(key);//若key存在,返回迭代器,若不存在,返回set.end();
count(key);//统计key的元素个数, 对于map结果为0或1
```

排序

默认大小按照key值进行从小到大排序,利用函数对象可以改变排序规则