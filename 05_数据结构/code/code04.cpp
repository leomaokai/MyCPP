//顺序表
//元素位置从0开始
#include <iostream>
using namespace std;
//顺序表模板
template <typename T>
class sqlist
{
public:
    sqlist(int size = 2) //构造函数
    {
        _first = new T[size]();
        _last = _first;
        _end = _first + size;
    }
    ~sqlist() //析构函数
    {
        delete[] _first;
    }
    void push_back(const T &val)
    {
        if (full())
            expand();
        *_last++ = val;
    }
    void insert(const int &pos, const T &val) //在pos位置插入元素val
    {
        if (pos < 0 || pos > size()) //判断插入是否合理
        {
            throw "the pos error";
        }
        //从最后一个元素到pos位置的元素后移一位
        for (int i = size() - 1; i >= pos; --i)
            _first[i + 1] = _first[i];
        _first[pos] = val; //插入元素
        ++_last;
        if (full())
            expand();
    }
    void del(const int &pos) //删除pos位置的元素
    {
        if (pos < 0 || pos > size())
        {
            throw "the pos error";
        }
        //从pos之后的元素向前移动一位
        for (int i = pos; i < num(); ++i)
            _first[i] = _first[i + 1];
        _first[num() - 1] = 0;
        --_last;
    }
    void locate(const T &val) //返回元素val的位置
    {
        bool flag = true;
        for (int i = 0; i < size(); ++i)
        {
            if (_first[i] == val)
            {
                cout << i << endl;
                flag = false;
            }
        }
        if (flag)
            cout << "no val" << endl;
    }
    void number(const T &val) //返回元素val的个数
    {
        int count = 0;
        for (int i = 0; i < num(); ++i)
            if (_first[i] == val)
                ++count;
        cout << count << endl;
    }
    void print()
    {
        if (empty())
            cout << "the sqlist is empty" << endl;
        else
        {
            for (int i = 0; i < num(); ++i)
                cout << _first[i] << " ";
            cout << endl;
        }
    }
    bool full() { return _last == _end; }    //判断是否满
    bool empty() { return _first == _last; } //判断是否为空
    int size() { return _end - _first; }     //返回数组大小
    int num() { return _last - _first; }     //返回元素个数
private:
    T *_first;    //指向第一个元素
    T *_last;     //指向最后一个元素的后继位置
    T *_end;      //指向数组空间的后继位置
    void expand() //扩容
    {
        int _size = _end - _first;
        T *temp = new T[2 * _size](); //二倍动态扩容
        for (int i = 0; i < _size; ++i)
            temp[i] = _first[i];
        delete[] _first;
        _first = temp;
        _last = _first + _size;
        _end = _first + 2 * _size;
    }
};
int main()
{
    sqlist<int> sq; //默认开辟2个空间
    sq.push_back(5);
    sq.push_back(5);
    sq.push_back(6);
    sq.push_back(7);
    sq.print(); //5 5 6 7
    sq.del(0);
    sq.print();   //5 6 7
    sq.locate(5); //0
    sq.insert(0, 5);
    sq.print(); //5 5 6 7
    sq.insert(1, 4);
    sq.print();   //5 4 5 6 7
    sq.number(5); //2
    return 0;
}