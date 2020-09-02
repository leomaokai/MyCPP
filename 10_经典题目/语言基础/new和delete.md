**new和malloc的区别是什么**

* malloc和free称为C的库函数,new和delete称为运算符
* malloc仅仅是开辟内存,需要强转换类型,new不仅可以做内存开辟,还可以做内存初始化操作
* malloc开辟内存失败,是通过返回值和nullptr做比较;而new开辟内存失败,是通过抛出bad_alloc类型的异常来判断的

**delete和free的区别是什么**

* delete先调用析构函数,再free

**new有多少种?**

```cpp
int *p1=new int(20);//抛出异常的new
int *p2=new (nothrow) int;//不抛出异常的new
const int *p3=new const int(40);//生成常量的new

//定位new
int data=0;
int *p4=new (&data) int(50);

```

**底层实现**

```cpp
//new操作先调用operator new开辟内存空间,然后调用对象的构造函数
void* operator new(size_t size)
{
    void *p=malloc(size);
    if(p==nullptr)
        throw bad_alloc();
    return p;
}
//delete先调用p指向对象的析构函数,再调用operator delete释放空间
void operator delete(void *ptr)
{
    free(ptr);
}
```

**new和delete能否混用?**

* 对于普通的编译器内置类型,`new/delete[]  new[]/delete`能混用
* 自定义的类型有析构函数,为了调用正确的析构函数,那么开辟对象数组时会多开辟4个字节,用来记录对象的个数,这就不能混用

