# 运算符重载

运算符重载:使对象的运算表示得和编译器内置类型一样

```cpp
//复数类
class ccomplex
{
public:
    ccomplex(int r=0,int i=0):mreal(r),mimage(i){}
    // ++  单目运算符 operator++() 前置++  operator++(int) 后置++
    ccomplex operator++(int)  //后置++
    {
        return ccomplex(mreal++,mimage++);//先返回后++
    }
    ccomplex& operator++()	//前置++
    {
        mreal+=1;
        mimage+=1;
        return *this;
    }
private:
    int mreal;
    int mimage;
    // + 友元运算符函数重载
    friend ccomplex operator+(const ccomplex &t1,const ccomplex &t2);
    // += 
    friend void operator+=(const ccomplex &t1,const ccomplex &t2);
    // <<
    friend ostream& operator<<(ostream &out,const ccomplex &t);
};
// + 算术运算符重载
ccomplex operator+(const ccomplex &t1,const ccomplex &t2)
{
    return ccomplex(t1->mreal+t2->mreal,t1->mimage+t2->mimage);
}
// += 复合赋值
void operator+=(const ccomplex &t1,const ccomplex &t2)
{
    t1.mreal+=t2.mreal;
    t1.mimage+=t2.mimge;
}
// << 输出运算符
ostream& operator<<(ostream &out,const ccomplex &t)
{
    out<<t.mreal<<"+"<<t.mimage<<<"i"<endl;
    return out;
}
```

编译器做对象运算时,会优先调用成员方法中得对象运算符重载函数,如果没有成员方法,就在全局作用域找合适得运算符重载函数,

* 一般情况下,单目运算符定义为成员方法,双目运算符定义为类的友元函数

* C++要求: 赋值`=`,下标`[]`,调用`()`,成员访问箭头`->`这几个操作符必须被定义为类成员操作符,否则会出现编译错误

* 不能被重载得运算符: `::` ,`:` ,`.*` ,`.?` `sizeof`

* 不能为内置数据类型定义重载运算符
* 重载不改变运算符得优先级和结合性
* 重载时不能有默认参数
* 重载运算符必须与类共同使用

# 附:优先级

常用运算符优先级

| 运算符 | 功能                   |
| ------ | ---------------------- |
| ()     | 调用优先级的括号运算符 |
| !      | 逻辑非                 |
| -      | 一元取负               |
| *      | 解引用                 |
| new    | 分配对象               |
| +      | 算术加                 |
| !=     | 不等于                 |
| &      | 按位与                 |
| =      | 赋值                   |

