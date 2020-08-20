//ptr_4.cpp
#include<iostream>
using namespace std;
int main()
{
    int arr[5]={0,1,2,3,4};
    int *p1=arr;
    cout<<*(p1+4)<<endl;//4
    cout<<*(arr+4)<<endl;//4
    cout<<arr[4]<<endl;//4
    cout<<p1[4]<<endl;//4
    //以上指针指向同一内容arr[4]
    *(p1+4)-=1;//arr[4]=arr[3]
    cout<<arr[4]<<endl;//3
    cout<<*(p1+4)<<endl;//3    
    int *p2=(int *)(&arr+1);//arr[5]
    cout<<*(p2-1)<<endl;//3
    cout<<*(arr+4)<<endl;//3
    cout<<((p2-1)==(arr+4))<<endl;//1,指向同一区域
    char c='a';
    char *p3=&c;
    //strcpy(p3,"hello");
    int *p4=NULL;
    //cout<<*p4<<endl;//不要试图获取空指针的值
    return 0;
}