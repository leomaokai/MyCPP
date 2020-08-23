//tch.cpp
#include<iostream>
using namespace std;
class tch
{
    public:
    static int m_score;
    //int m_score;
    static void math()
    {
        cout<<"my math is "<<m_score<<endl;
    }
};
int tch::m_score = 100;
int main()
{
    tch::math();//直接调用静态成员函数
    return 0;
}