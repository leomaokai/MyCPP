#include<iostream>
using namespace std;
int main()
{
    int *p1;//一个普通指针
    int **p2;//一个指向指针地址的指针
    int *p3[5];//一个指针数组
    int (*p4)[5];//一个指向5给整型数组的指针
    int (*p5)(int);//一个指向函数的指针
    int (*p6[5])(int);//一个指向函数的指针数组
    return 0;
}
//上述指针都未赋值,是野指针