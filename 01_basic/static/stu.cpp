//stu.cpp
#include<iostream>
using namespace std;
class stu
{
public:
    static int m_id;
};
int stu::m_id=1;
int main()
{
    stu stu1;
    //stu stu2;
    //stu1.m_id=10;
    //stu2.m_id=20;
    cout<<stu1.m_id;//<<" "<<stu2.m_id;
    return 0;
}