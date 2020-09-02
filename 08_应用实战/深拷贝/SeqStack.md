```cpp
class SeqStack//顺序栈
{
    public:
    SeqStack(int size=10)//构造函数
    {
        _pstack=new int[size];
        _top=-1;
        _size=size;
    }
    SeqStack(const SeqStack &src)//拷贝构造
    {
        _pstack=new int[src._size];
        for(int i=0;i<=src._top;++i)
        {
            _pstack[i]=src._pstack[i];
        }
        _top=src._top;
        _size=src._size;
    }
    SeqStack &operator=(const SeqStack &src)//赋值重载
    {
        if(this==&src)
            return *this;
        delete [] _pstack;
        for(int i=0;i<=src._top;++i)
        {
            _pstack[i]=src._pstack[i];
        }
        _top=src._top;
        _size=src._size;
        return *this;
    }
    ~SeqStack()
    {
        delete [] _pstack;
        _pstack=nullptr;
    }
    void push(int val)
    {
        if(full())
            resize();
        _pstack[++_top]=val;
    }
    void pop()
    {
        if(empty())
            return;
        --_top;
    }
    bool empty(){return _top==-1;}
    bool full(){return _top==_size-1;}
    private:
    int *_pstack;//多态开辟数组
    int _top;//指向栈顶元素的位置
    int _size;//数组大小
    void resize()//扩容函数
    {
        int *ptmp=new int[_size * 2];
        for(int i=0;i<_size;++i)
        {
            ptmp[i]=_pstack[i];
        }
        delete [] _pstack;
        _pstack=ptmp;
        size *=2;
    }
};
```

