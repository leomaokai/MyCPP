# 指针和引用的区别

* 初始化要求不同.引用在创建的同时必须初始化,引用在定义的时候不必初始化
* 可修改性不同.引用一旦初始化后就不可更改为另一个对象的引用,指针可以更改指向的对象
* 不存在NULL引用.所以引用比指针安全

#  指针变量引用

```c++
//ptr_1.cpp
#include<iostream>
using namespace std;
int main()
{
    int a=1;
    int* p=&a;//声明指针p指向a
    int* &rp=p;//声明p的一个指针引用rp
    (*rp)++;
    cout<<"a= "<<a<<endl;
    cout<<"*p= "<<*p<<endl;
    cout<<"*rp= "<<*rp<<endl;
    int b=5;
    p = &b;
    cout<<"a= "<<a<<endl;
    cout<<"*p= "<<*p<<endl;
    cout<<"*rp= "<<*rp<<endl;
    return 0;
}
```

```c++
a= 2
*p= 2
*rp= 2
a= 2
*p= 5
*rp= 5
```

# 参数引用

```c++
//ptr_2.cpp
#include<iostream>
using namespace std;
int func1(int &ref)
{
    ref++;
    return ref;
}
int func2(const int &ref)
{
    //ref++;//以常量引用传入后无法修改值
    return ref;
}
int main()
{
    int a = 5;
    int b=func1(a);
    const int c=func2(a);
    //int &b=c;//不能使用常量类型变量定义非常量引用
    const int &e=a;
    //++e;//不能用常量引用修改变量的值
    cout<<b<<endl;
    cout<<c<<endl;
    //cout<<d<<endl;
    cout<<e<<endl;
    return 0;
}
```

```
6
6
6
```

# 复杂指针

```c++
//ptr_3.cpp
#include<iostream>
using namespace std;
int main()
{
    int *p1;//一个普通指针
    int **p2;//一个指向指针地址的指针
    int *p3[5];//一个指针数组
    int (*p4)[5];//一个指向5给整型数组的指针
    int (*p5)(int);//一个指向函数的指针
    int (*p6[5])(int);//一个指向函数的指针数组
    return 0;
}
//上述指针都未赋值,是野指针
```

# 指针操作

```c++
//ptr_4.cpp
#include<iostream>
using namespace std;
int main()
{
    int arr[5]={0,1,2,3,4};
    int *p1=arr;
    cout<<*(p1+4)<<endl;//4
    cout<<*(arr+4)<<endl;//4
    cout<<arr[4]<<endl;//4
    cout<<p1[4]<<endl;//4
    //以上指针指向同一内容arr[4]
    *(p1+4)-=1;//arr[4]=arr[3]
    cout<<arr[4]<<endl;//3
    cout<<*(p1+4)<<endl;//3    
    int *p2=(int *)(&arr+1);//arr[5]
    cout<<*(p2-1)<<endl;//3
    cout<<*(arr+4)<<endl;//3
    cout<<((p2-1)==(arr+4))<<endl;//1,指向同一区域
    char c='a';
    char *p3=&c;
    //strcpy(p3,"hello");//复制失败,指针指向内存不足
    int *p4=NULL;
    //cout<<*p4<<endl;//不要试图获取空指针的值
    return 0;
}
```

* 对指针进行加1操作,得到的是下一个元素的地址,而不是原有地址值直接加1
* 注意普通变量类型与指针类型之间无法隐式转换

# 指针数组与数组指针

指针数组是数组,数组中的每个元素是指针

数组指针是指针,指向一个数组

# 函数指针与指针函数

指针函数是返回指针类型的函数

函数指针是指向函数地址的指针

# 野指针

野指针的成因:

* 指针变量没有被初始化.
* 指针被释放了,没有置为NULL









