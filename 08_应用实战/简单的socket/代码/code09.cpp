#include"myhead.h"

int main()
{
	servers server;
	if(server.initserver()==false)
		return 1;
	while(1)
	{
		
