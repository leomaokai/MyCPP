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





