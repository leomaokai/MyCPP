```cpp
class Queue//循环队列
{
    public:
    Queue(int size=5)
    {
        _pQue=new int[size];
        _front=0;
        _rear=0;
        _size=size;
    }
    Queue(const Queue &src)
    {
        _size=src._size;
        _front=src._front;
        _rear=src._rear;
        _pQue=new int[_size];
        for(int i=_front;i!=_rear;i=(i+1)%_size)
        {
            _pQue[i]=src._pQue[i];
        }
    }
    Queue& operator=(const Queue &src)
    {
        if(this==&src)
            return *this;
        delete []_pQue;
        _size=src._size;
        _front=src._front;
        _rear=src._rear;
        _pQue=new int[_size];
        for(int i=_front;i!=_rear;i=(i+1)%_size)
        {
            _pQue[i]=src._pQue[i];
        }
        return *this;
    }
    ~Queue()
    {
        delete []_pQue;
        _pQue=nullptr;
	}
    void push(int val)
    {
        if(full())
            resize();
        _pQue[_rear]=val;
        _rear=(_rear+1)%_size;
    }
    void pop()
    {
        if(empty())
            return;
        _front=(_front+1)%_size;
    }
    int front()
    {
        return _pQue[_front];
    }
    bool full(){return (_rear+1)%_size==_front;}
    bool empty(){return _front==_rear;}
    private:
    int *_pQue;
    int _front;
    int _rear;
    int _size;
    
    void resize()
    {
        int *ptmp=new int[_size *2];
        int index=0;
        for(int i=_front;i!=_rear;i=(i+1)%_size)
        {
            ptmp[index++]=_pQue[i];
        }
        delete []_pQue;
        _pQue=ptmp;
        _front=0;
        _rear=index;
        _size*=2;
    }
};
```

