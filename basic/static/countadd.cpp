#include<iostream>
using namespace std;
void countadd(){
    static int count = 0;
    cout<<count<<' ';
    count++;
}
int main(){
    for(int i=0;i<5;i++)
        countadd();
    return 0;
}