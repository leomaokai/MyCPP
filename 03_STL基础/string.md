string和char*的区别：

* char * 是一个指针
* string是一个类，内部封装了char*
* const chat * 为常量字符串,在传参时必须用双引号引用

构造函数原型

```cpp
#include<string>
string();
string(const char* s);
string(const stirng& str);
string(int n,char c);
```

赋值函数原型

```cpp
string& operator=(const char* s);
string& operator=(const string &s);
string& operator=(char c);
string& assign(const char *s);
string& assign(const string &s);
string& assign(const char *s,int n);//把字符串s的前n个字符赋给当前的字符串
string& assign(int n,char c);//用n个字符c赋给当前字符串
```

字符串拼接

```cpp
string& operator+=(const char* s);
string& operator+=(const stirng &s);
string& operator+=(const char c);
string& append(const char* s);
string& append(const string &s);
string& append(const char* s,int n);
string& append(const string &s,int pos,int n);//字符串s从pos开始的n个字符进行拼接 
```

查找与替换

```cpp
int find(const string &s,int pos=0) const;
int find(const char* s,int pos=0) const;
int find(const char c,int pos=0) const;
int find(const char* s,int pos,int n) const;//从pos位置查找s的前n个字符第一次位置
//find 从左往右查找，rfind从右往左，失败返回-1
string& replace(int pos,int n,const string &s);
string& replace(int pos,int n,const char* s);//替换从pos开始的n个字符为字符串s
```

字符串比较

```cpp
int compare(const string &s) const;
int compare(const char* s) const;
//等于返回0 大于返回1 小于返回-1
```

字符存取

```cpp
char& operator[](int n);
char& at(int n);
```

插入与删除

```cpp
string& insert(int pos,const char* s);
string& insert(int pos,const string &s);
string& insert(int pos,int n,char c);
string& erase(int pos,int n=npos);//删除从pos开始的n个字符
```

获取字串

```cpp
string substr(int pos=0,int n=npos) const;//返回从pos开始的n个字符组写的字符串
```

