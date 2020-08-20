//test01.cpp
#include<iostream>
using namespace std;
enum color {red,orange,yellow,green,blue = 10};
//enum color {red = 2,orange = 3};//显示设置枚举量的值
int main()
{
    color col;
    col = red;
    //++col;//error
    int num = 2+red;
    //col = 2;//error
    //col = red + orange;//error
    col = color(1);//强制类型转换
    col = color(9);//合法.9位于枚举定义的取值范围内
    return 0;
}