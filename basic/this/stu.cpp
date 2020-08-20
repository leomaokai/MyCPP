//stu.cpp
#include<iostream>
using namespace std;
class stu
{
    public:
    stu(int score):m_score(score){}
    const stu &compare(const stu &s) const
    {
        if(s.m_score>m_score)
            return s;
        else
            return *this;
    }
    int getscore()const
    {
        cout<<"The most score is "<<this->m_score;
    }
    private:
    const int m_score;
};
int main()
{
    stu stu1(99);
    stu stu2(59);
    stu1.compare(stu2).getscore();
    return 0;
}