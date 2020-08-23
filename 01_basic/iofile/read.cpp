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
    cout<<endl;

    char ch1[80]={0};//读取字符串
    while (read>>ch1)
    {
        cout << ch1;
    }
    cout<<endl;

    char ch2[80]={0};
	while (read.getline(ch2,sizeof(ch2)))
	{
		cout << ch2;
	}
    cout<<endl;

	string str;
	while (getline(read, str))
	{
		cout << str << endl;
	}
    return 0;
}