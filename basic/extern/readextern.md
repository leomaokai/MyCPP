# extern "C"

C++调用C函数时,引用C的头文件时,需要加`extern "C"`

# 应用

```c++
//myhead.h
#ifndef MYHEAD_H_
#define MYHEAD_H_
void hello();
#endif

//hello.c
#include <stdio.h>
#include "myhead.h"
void hello()
{
	printf("hello extern");
}

//hello.cpp
#include<iostream>
using namespace std;
extern "C"
{
	#include "myhead.h"
}
int main()
{
	hello();
	return 0;
}
```

编译:

先通过gcc生成中间文件hello.o,再通过g++编译

```
gcc -c hello.c   
g++ hello.o hello.cpp -o main
```

