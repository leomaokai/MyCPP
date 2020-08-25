stack是一种先进后出的数据结构

* 栈中只有顶端的元素才可以被外界使用,因此栈不允许有遍历行为
* 栈中进入数据称为入栈push
* 栈中弹出数据称为出栈pop

构造函数

```cpp
#include<stack>
stack<T> stk;
stack(const stack &stk);
```

赋值操作

```cpp
stack& operator=(const stack &stk);
```

数据存取

```cpp
push(elem);//向栈顶添加数据
pop();//从栈顶移除数据
top();//返回栈顶数据
```

大小操作

```cpp
empty();
size();
```

