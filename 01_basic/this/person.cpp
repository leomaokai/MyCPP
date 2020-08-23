//person.cpp
#include<iostream>
using namespace std;
class person
{
    public:
    person(int age):m_age(age){}
    void getage()const
    {
        cout<<"He is "<<this->m_age;
    }
    person &addage(int addage)//person &addage(int addage)const
    {
        m_age+=addage;
        return *this;
    }
    private:
    int m_age;
};
int main()
{
    person Tom(18);
    Tom.addage(2).getage();
    return 0;
}