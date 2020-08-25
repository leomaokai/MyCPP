queue是一种先进先出的数据结构

* 队列容器允许从一端插入元素,从另一端移除元素
* 队列只有队头和队尾才可以被外界使用,因此队列不允许遍历

构造函数

```cpp
#include<queue>
queue<T> que;
queue(const queue &que);
```

赋值操作

```cpp
queue& operator=(const queue &que);
```

数据存取

```cpp
push(elem);//向队尾添加元素
pop();//从队头移除元素
back();//返回最后一个元素
front();//返回第一个元素
```

大小操作

```cpp
empty();
size();
```

