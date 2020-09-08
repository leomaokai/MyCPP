**vector向量容器:**`vector<int> vec;`

* 底层数据结构:动态开辟的数组,内存是连续的,每次以原来空间大小的2倍进行扩容(0-1-2-4-8...)
* 增加:
  * `vec.push_back(10);`末尾添加元素 O(1)
  * `vec.insert(it,10);`it迭代器指向位置添加一个元素10 O(n)
* 删除:
  * `vec.pop_back();`末尾删除元素 O(1)
  * `vec.erase(it);`删除it迭代器指向的元素 O(n)
* 查询:
  * `vec[5];`下标随机访问 O(1)
  * `iterator`迭代器遍历
  * `find`,`for_each`
* `vec.reserve(20);`预留空间,只给容器底层开辟指定大小的内存空间,并不会添加新的元素
* `vec.resize(20);`容器扩容,不仅给容器底层开辟指定大小的内存空间,还会添加新的元素(20个0)
* 对容器进行连续插入或者删除操作`(insert/erase)`,一定要更新迭代器,否则第一次insert或者erase后迭代器会失效

**deque双端队列容器:**`deque<int> deq;`

* 底层数据结构:动态开辟的二维数组,一维数组从2开始,以2被的方式进行扩容,每次扩容后,原来第二维的数组,从新的第一维数组的下标`oldsize/2`开始存放,上下都预留相同的空行,方便支持`deque`的首位元素添加,每一个第二维是连续的,第二维大小默认为`4096/sizeof(T)`,整体是分段连续的
* 增加:
  * `deq.push_back(20);`从末尾添加元素 O(1)
  * `deq.push_front(20);`从首部添加元素 O(1)
  * `deq.insert(it,10);`it指向的位置添加元素10 O(n)
* 删除:
  * `deq.pop_back();`从末尾删除元素 O(1)
  * `deq.pop_front();`从首部删除元素 O(1)
  * `deq.erase(it);`从it指向的位置删除元素 O(n)
* 查询搜索
  * `iterator`:连续的insert和erase一定要考虑迭代器失效的问题

**list链表容器:**`list<int> mylist;`

* 底层数据结构:双向的循环列表
* 增加:
  * `mylist.push_back(20);`从末尾添加元素 O(1)
  * `mylist.push_front(20);`从首部添加元素 O(1)
  * `mylist.insert(it,10);`it指向的位置添加元素10 O(1)
* 删除:
  * `mylist.pop_back();`从末尾删除元素 O(1)
  * `mylist.pop_front();`从首部删除元素 O(1)
  * `mylist.erase(it);`从it指向的位置删除元素 O(1)
* 查询搜索
  * `iterator`:连续的insert和erase一定要考虑迭代器失效的问题

**vector和deque之间的区别?**

* 底层数据结构
* 前中后插入删除元素的时间复杂度
* 对于内存的使用效率,vector需要的内存空间必须是连续的,`deque`可以分块进行数据存储,不需要内存空间是一片连续的,内存使用效率更高
* 再中间进行insert或者erase,vector和`deque`的效率:时间复杂度都是O(n),但vector内存是完全连续的,元素移动相对方便,`deque`第二维内存空间不是连续的,在`deque`中间进行元素的insert或者erase造成元素移动时比vector慢

**vector和list之间的区别?**

* 底层数据结构:数组  双向循环链表
  * 数组: 增加删除O(n)  查询O(n)  随机访问O(1)
  * 链表: (考虑搜索的时间)增加删除O(1)  查询O(n)  

**怎么理解容器适配器?**`(stack,queue,priority_queue)`

* 适配器底层没有自己的数据结构,它是另外一个容器的封装,它的方法全部依赖底层的容器进行实现的
* 没有实现自己的迭代器
* stack: push入栈 pop出栈 top查看栈顶元素 empty判断栈空 size返回元素大小
* queue:  push入队 pop出队 front队头 back查看队尾元素 empty判断队空 size返回元素大小
  * queue和stack依赖deque,为什么不依赖vector?
    * vector初始内存使用效率太低,而deque第二维有默认大小
    * 对于queue来说,需要支持尾部插入,头部删除,如果queue依赖vector,其出队效率很低
    * vector需要大片连续内存,而deque只需要分段的内存,在存储大量数据时,显然deque对于内存的利用率高
* priority_queue:  push入队 pop出队 top查看队顶元素 empty判断队空 size返回元素大小
  * priority_queue为什么依赖vector?
    * 优先级队列底层默认把数据组成大根堆结构,需要在一个内存连续的数组上构建一个大根堆或者小根堆

**关联容器:**

* 无序关联容器:链式哈希表 增删查O(1)
  * set 集合 只存`key`   map 映射表 `[key,value]`
  * `unordered_set` 单重集合
  * `unordered_multiset` 多重集合
  * `unordered_map` 单重映射表
  * `unordered_multimap` 多重映射表
* 有序关联容器:红黑树   增删查O(`log2n`) 2是底数
  * `set,multiset`
  * `map,multimap`
* 常用增删查方法
  * 增加:`insert(val)`,`insert(pair)`
  * 遍历:`iterator`,`find`算法
  * 删除:`erase(key)`,`erase(it)`
* 应用:查重,去重

**容器的迭代器:**

* `iterator`:普通正向迭代器
* `const_iterator`:常量迭代器,只能读,不能写
* `reverse_iterator`:反向迭代器
  * `rbegin`():返回的是最后一个元素的反向迭代器
  * `rend`():返回的是首元素前驱位置的迭代器
* `const_reverse_iterator`:常量的反向迭代器

**函数对象:**

* 拥有`operator()`小括号运算符重载函数的对象,称作函数对象或者仿函数
* 类似C语言里面的函数指针,但通过函数指针是没办法内联的,存在函数开销,效率很低
* 通过函数对象调用`operator()`可以省略函数的调用开销,比通过函数指针调用函数(不能内联)效率高
* 因为函数对象是用类生成的,所以可以添加相关的成员变量,用来记录函数对象使用时更多的信息

**泛型算法:**

* 泛型算法的参数接收的都是迭代器
* 泛型算法的参数还可以接收函数对象
* 绑定器+二元函数对象=>一元函数对象
  * `bind1st`:把二元函数对象的operator()的第一个形参绑定起来
  * `bind2nd`:把二元函数对象的operator()的第二个形参绑定起来