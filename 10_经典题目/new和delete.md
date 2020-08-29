**new和malloc的区别是什么**

* malloc和free称为C的库函数,new和delete称为运算符
* malloc仅仅是开辟内存,需要强转换类型,new不仅可以做内存开辟,还可以做内存初始化操作
* malloc开辟内存失败,是通过返回值和nullptr做比较;而new开辟内存失败,是通过抛出bad_alloc类型的异常来判断的

**delete和free的区别是什么**



**new有多少种?**

```cpp
int *p1=new int(20);//抛出异常的new
int *p2=new (nothrow) int;//不抛出异常的new
const int *p3=new const int(40);//生成常量的new

//定位new
int data=0;
int *p4=new (&data) int(50);
```

