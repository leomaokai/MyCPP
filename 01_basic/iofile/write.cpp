//write.cpp
#include<iostream>
#include<fstream>
using namespace std;
int main()
{
    ofstream write;
    write.open("test.txt",ios::out);
    write<<"hello write"<<endl;
    write.close();
    return 0;
}