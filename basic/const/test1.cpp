#include<iostream>
using namespace std;

class test
{
    public:
    test(int i):num(i){}
    void get1() const;
    void get2();
    int getnum()const;
    private:
    const int num;
};
void test::get1() const
{
    cout<<getnum()<<"get1()const"<<endl;
}
void test::get2()
{
    cout<<getnum()<<"get2()"<<endl;
}
int test::getnum() const
{
    return num;
}

int main(){
    test t1(1);
    t1.get2();
    t1.get1();
    const test t2(2);
    t2.get2();
    t2.get1();
    return 0;
}