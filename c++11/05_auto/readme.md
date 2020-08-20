# auto

新标准引入了auto类型说明符,能让编译器替我们去分析表达式所属的类型

* auto让编译器通过初始值来推算变量的类型,所以其定义的变量必须有初始值

* 使用auto声明多个变量其初始基本类型必须一样

* 使用引用时编译器以引用对象的类型作为auto的类型

* auto一般会忽视掉顶层const,保留底层const

  ```c++
  auto i=0,*p=&i,&r=i;//正确,i是整数,p是整型指针,r是整数
  auto sz=0,pi=3.14;//错误,sz和pi的类型不一致
  auto r1=r;//r1是一个整数
  const int ci=i;
  auto b = ci;//ci的顶层const特性被忽略掉
  const auto c = ci;
  ```

  



