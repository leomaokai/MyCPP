//test2.cpp 上例稍作修改
#include<iostream>
using namespace std;
class test
{
    public:
    test(int i):num(i){}
    void get1()const;
    int getnum() const;
    private:
    mutable int num;
};
void test::get1()const
{
     num=2;
    cout<<getnum()<<"调用get1()const"<<endl;
}
int test::getnum()const
{
    return num;
}

int main(){
    test t1(1);
    t1.get1();
    return 0;
}