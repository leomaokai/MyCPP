//test2.cpp
#include<memory>
#include<iostream>
using namespace std;

int main()
{
    unique_ptr<int> ptr1(new int);
    unique_ptr<int> ptr2(std::move(ptr1));//使用了右值引用的拷贝构造
    ptr2=std::move(ptr1);//使用了右值引用的operator=赋值重载函数
    return 0;
}