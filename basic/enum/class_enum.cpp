//class_enum.cpp
#include<iostream>
using namespace std;
class year
{
    public:
    enum {month = 12};
    //static const int month = 12;
    int mon[month];
};
int main()
{
    return 0;
}