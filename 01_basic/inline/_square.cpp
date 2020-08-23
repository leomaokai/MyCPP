//SQUARE.cpp
#include<iostream>
using namespace std;
#define SQUARE(X) ((X)*(X))
int main(){
    double a=1.5;
    cout<<"The first = "<<SQUARE(2.5)<<endl;
    //(2.5)*(2.5)
    cout<<"The second = "<<SQUARE(1+1.5)<<endl;
    //(1+1.5)*(1+1.5)
    cout<<"The third = "<<SQUARE(a++)<<endl;
    //(1.5+1+1)*(1.5+1+1)
    cout<<"now a = "<<a<<endl;
    return 0;
}