# 函数模板

模板的意义:类型参数化

模板类型参数:`typename/class`

```cpp
template<typename T>
bool compare(T a,T b)//函数模板
{
    return a>b;
}
//const char * 模板特例化
template<>
bool compare<const char*>(const char *a,const char *b)
{
    return strcmp(a,b)>0;
}
int main()
{
    //函数调用点,编译器用用户指定的类型从原模版示例化一份代码
    compare<int>(30,40);//实例化了一个int模板函数
    compare<double>(3.24,3.14);//实例化另一个double模板函数
    
    //模板的实参推演,根据用户传入的实参类型,推导处模板类型参数
    commpare(30,50);//因为之前实例化了int类型,所以不用重新再生成函数
    
    //compare(40.3.14);// T不明确产生错误
    compare<int>(40,3,14);//将double转换为int
    
    //对于某些类型,依赖编译器默认实例化的模板代码,会发生逻辑错误
    //需要模板的特例化(不是编译器提供,而是用户提供)
    //编译器优先把compare处理成函数名字,之后才依赖模板
    compare("qqq","eee");//函数模板实参推演 T=>const char *
    return 0;
}
```

函数模板,模板特例化,非模板函数可以共存,类似于函数重载

模板代码是不能在一个文件中定义,在另一个文件中使用,模板代码要放在头文件中

模板非类型:

```cpp
//模板非类型参数都是常量 size
template<typename T,int size>
void sort(T *arr)
{
    for(int i=0;i<size-1;++i)
        for(int i=0;j<size-i-1;++j)
            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
}
int main()
{
    int arr[]={3,4,2,1,5};
    sort<int,5>(arr);//size指定为5
    for(int val:arr)
        cout<<val<<" ";
    cout<<endl;
}
```



