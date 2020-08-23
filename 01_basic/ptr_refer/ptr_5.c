/*ptr_5.c*/
#include<stdio.h>
int main()
{
    char *str[]={"welcome","to","my","cumt1909"};//指针数组
    char * *p=str+1;//p指向str[1]
    str[0]=*p+1;p=p+1;//(*p++)+1; p指向str[2]
    str[1]=*(p+1);//p+1指向str[3]
    str[2]=p[1]+3;//p[1]指向str[3]
    str[3]=p[0]+(str[2]-str[1]);//p[0]指向str[2]
    printf("%s\n",str[0]);
    printf("%s\n",str[1]);
    printf("%s\n",str[2]);
    printf("%s\n",str[3]);
    return 0;
}
/*  p是指针数组
    *p是数组指针  */
