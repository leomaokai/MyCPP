#include"myhead.hpp"
#include<iostream>
using namespace std;
inline int stu::getage(int b){
	return b;
}
int main(){
	stu bob;
	cout<<"his id is "<<bob.getid(111)<<endl;
	cout<<"his age is "<<bob.getage(20)<<endl;
	return 0;
}
