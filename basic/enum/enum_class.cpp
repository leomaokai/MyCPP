//enum_class.cpp
#include<iostream>
using namespace std;
enum color1{red = 5,orange,blue};
enum class color2
{
    red=20,
    orange,
    blue
};
int main()
{
    color1 col1=red;
    int a = col1;
    color2 col2=color2::red;//使用枚举类
    //int a=col2;//error无法隐式转换
    int b = int(color2::red);//显示转换
    //int c = static_cast<int>(col2);//强制转
    cout<<a<<b;
    return 0;
}