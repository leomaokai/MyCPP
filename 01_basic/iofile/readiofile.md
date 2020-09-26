# I/O

通过文件操作将数据持久化

c++中对文件操作需要包含头文件`<fstream>`

操作文件分为写,读,读写三类:`ofstream`  `istream`  `fstream`

# ofstream

```c++
//write.cpp
#include<iostream>
#include<fstream>//必须包含头文件
using namespace std;
int main()
{
    ofstream write;//创建文件流对象
    write.open("test.txt",ios::out);//打开文件
    //ofstream write("test.txt",ios::out);//两步合一步
    write<<"hello write"<<endl;//写入数据
    write.close();//关闭文件
    return 0;
}
```

`write.open("文件路径",打开方式);`

文件打开方式：

| 打开方式    | 解释                       |
| ----------- | -------------------------- |
| ios::in     | 为读文件而打开文件         |
| ios::out    | 为写文件而打开文件         |
| ios::ate    | 初始位置：文件尾           |
| ios::app    | 追加方式写文件             |
| ios::trunc  | 如果文件存在先删除，再创建 |
| ios::binary | 二进制方式                 |

文件打开方式可以利用`|`配合使用

# ifstream

读取文件与写入文件相似

```c++
//read.cpp
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main()
{
    ifstream read;
    read.open("test.txt",ios::in);
    if (!read.is_open())//判断是否打开成功
	{
		cout << "文件打开失败" << endl;
		return 0;
	}

    char c;
	while ((c = read.get()) != EOF)
	{
		cout << c;
	}

    char ch1[80]={0};//读取字符串
    while (read>>ch1)
    {
        cout << ch1;
    }

    char ch2[80]={0};
	while (read.getline(ch2,sizeof(ch2)))
	{
		cout << ch2;
	}

	string str;
	while (getline(read, str))
	{
		cout << str << endl;
	}
    return 0;
}
```

# C文件操作

## 文件指针

头文件`stdio.h`

包含文件信息的结构体`FILE`,`FILE`结构体指针称为文件指针

`fopen`函数会动态分配一个`FILE`结构体大小的内存空间,并返回`FILE`结构体内存的地址

`fclose`函数会关闭文件,并且会释放`FILE`结构体占用的内存空间

## 打开文件

```c
FILE *fopen(const char *filename,const char *mode);
/*成功返回文件指针,失败返回NULL*/
```

| mode方式 | 含义     | 说明                                                       |
| -------- | -------- | ---------------------------------------------------------- |
| r        | 只读     | 文件必须存在,否则打开失败                                  |
| w        | 只写     | 如果文件存在，则清除原文件内容；如果文件不存在，则新建文件 |
| a        | 追加只写 | 如果文件存在，则打开文件，如果文件不存在，则新建文件       |
| r+       | 读写     | 文件必须存在。在只读 r 的基础上加 '+' 表示增加可写的功能   |
| w+       | 读写     | 在只写w的方式上增加可读的功能                              |
| a+       | 读写     | 在追加只写a的方式上增加可读的功能                          |

Linux环境下,打开文本文件和二进制文件的方式没有区别

## 关闭文件

```c
int fclose(FILE *fp);
/*成功返回0,出错返回EOF*/
```

必须在合适时间调用`fclose`关闭文件指针

## 文本文件的读写

文本文件以行的形行存放字符串

```c
//向文件中写入数据
int fprintf(FILE *fp,const char *format,...);
//fprintf与printf用法类似,第一个参数为文件指针,表示将数据输出到文件

//向文件中读取数据
char *fgets(char *buf,int size,FILE *fp);
/*
fgets从文件中读取一行,buf用于保存从文件中读到的数据
size是文件读取内容的长度,如果文件中将要读取的这一行的内容的长度小于size，fgets函数就读取一行，如果这一行的内容大于等于size，fgets函数就读取size-1字节的内容,可以将 size 的值设置地足够大，确保每次都能读取到一行完整的数据。
成功返回BUF,若到达文件尾端或出错,返回NULL
*/
```

## 二进制文件的读写

二进制文件没有行和字符串的概念

```c
//向文件中写入数据
size_t fwrite(const void *ptr,size_t size,size_t nobj,FILE *fp);
/*
ptr为内存块的指针,存放要写入的数据的地址
size为数组或结构体的长度sizeof()
nobj为要写入的元素或对象的个数
*/

//从文件中读取数据
size_t fread(void *ptr,size_t size,size_t nobj,FILE *fp);
//与fwrite类似
//两个函数的返回值为读或写的对象数
```

## 文件定位

```c
long ftell(FILE *fp);//返回当前文件位置相当于文件开始位置的字节数
void rewind(FILE *fp);//将位置指针移动到文件开头
int fseek(FILE *fp,long offset,int origin);//将位置指针移动到任意位置
/*
fp为文件指针,也就是被移动的文件
offset为偏移量,也就是要移动的字节数,offset为正时,向后移动,offset为负时,向前移动
origin为起始位置,也就是从何处开始计算偏移量
C语言规定的起始位置有三种，分别为：0文件开头;1当前位置;2文件末尾
成功返回0,失败返回-1
*/
```

## 文件缓冲区

```c
//把缓冲区的数据立即写入文件
int fflush(FILE *fp);
//fclose也会把缓冲区中的数据写入文件
```

