# const

`const`修饰的常量出现的错误:

* 常量不能再作为左值
* 不能把常量的地址泄露给一个普通的指针或普通的引用变量

```cpp
//const是如何影响形参类型的
void func(int a);//int
void func(const int a);//int
void func(int *a);//int*
void func(int const *a);//int const*
void func(int* const a);//int*
```

C++中的`const`和C中`const`有啥区别:

* C++`const`修饰的量必须初始化,叫做常量,C中`const`修饰的量叫常变量,与普通变量唯一的区别是不能作为左值

* `const`编译方式不同,C中,`const`就是当成一个变量来编译生成指令的,C++中,所有出现`const`常量名字的地方,都被常量的初始化替换了

```cpp
const int a=20;
int *p=(int*)&a;
*p=30;
printf("%d %d %d \n",a,*p,*(&a));
//C  : 30 30 30   a的内存被指针修改为30
//C++: 20 30 20  *(&a)被编译器优化为a,a被指针修改为30之前已经全部替换成20
/*******************************/
int b=20;
const int a=b;//常变量,初始值不是一个立即数,是一个变量,与C中一样
int *p=(int*)&a;
*p=30;
printf("%d %d %d \n",a,*p,*(&a));//30 30 30
```

# const和指针

`const`如果右边没有指针*的话,`const`是不参与类型的

总结`const`和指针的类型转换公式:

```
int*   		<= 	const int*		//错误
const int * <= 	int*			//正确

int**   	<=  const int ** 	//错误
const int** <= 	int**     		//错误
int**   	<=  int*const*   	//错误
int*const* 	<= 	int**		 	//正确
```

```cpp
//1
int a=10;
const int* p=&a;//const int * <= int*	正确
int *q=p;		//int* <= const int*	错误
//2
int a=10;
int *const p=&a;//int* <=int* 正确 
int *q=p;		//int* <=int* 正确 
//3
int a=10;
int *const p=&a;//int* <=int* 正确
int *const q=p;	//int* <=int* 正确 
//4
int a=10;
int *const p=&a;//int* <=int* 正确
const int *q=p;//const int * <= int* 正确
//5
int a=10;
int *p=&a;		//int* <=int* 正确
const int **q=&p;//const int** <=int**  错误
//*q <=> p   相当于把常量地址*q放到普通地址p中
//6
int a=10;
int *p=&a;		//int* <=int* 正确
int *const*q=&p;//int *const* <= int** 正确
//7
int a=10;
int *p=&a;		//int* <=int* 正确
int **const q=&p;//int** <= int** 正确
//8
int a=10;
int* const p=&a;//int* <=int* 正确
int **q=&p;		//int** <= int*const*  错误
//9
int a=10;
const int *p=&a;//const int * <= int* 正确
int *const* q=&p;//int *const* <= const int** 错误
```

 