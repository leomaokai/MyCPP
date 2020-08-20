#include<iostream>
using namespace std;
extern "C"
{
	#include "myhead.h"
}
int main()
{
	hello();
	return 0;
}
