#include<iostream>
using namespace std;
int main()
{
    long double a = 3.1415;
    int b = {1};
    int c {2};
    int d (3);
    int e = a;//正确:转换执行,且确实丢失了部分值
    //int f {a};//报错:转换未执行,因为存在丢失信息的危险
    return 0;
}