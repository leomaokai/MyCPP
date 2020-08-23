#include<iostream>
using namespace std;
using ld = long double;
//#define isNs1 1
//#define isGlobal 2
void func() 
{
    cout<<"::func"<<endl;
}
namespace ns1 {
    void func()
    {
        cout<<"ns1::func"<<endl; 
    }
}
namespace ns2 {
#ifdef isNs1 
    using ns1::func;    /// ns1中的函数
#elif isGlobal
    using ::func; /// 全局中的函数
#else
    void func() 
    {
        cout<<"other::func"<<endl; 
    }
#endif
}
int main() 
{
    ns2::func(); // 会根据当前环境定义宏的不同来调用不同命名空间下的func()函数
    cout<<sizeof(ld);
    return 0;
}