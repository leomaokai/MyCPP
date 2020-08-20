//square.cpp
#include<iostream>
using namespace std;
inline double square(double a){return a*a;}
int main(){
    double a=0.5;
    cout<<"The first square's area is "
        <<square(1.5)<<endl;
    //square(1.5);==1.5*1.5;
    cout<<"The second square's area is "
        <<square(1+0.5)<<endl;
    //square(1+0.5);==(1+0.5)*(1+0.5);
    cout<<"The third square's area is "
        <<square(++a)<<endl;
    //square(++a);==(0.5+1)*(0.5+1);
    cout<<"now a = "<<a<<endl;
    return 0;
}