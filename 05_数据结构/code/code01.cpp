//code01.cpp
//顺序表
#include <iostream>
using namespace std;
template <typename T>
class SqList
{
public:
    SqList(int size = 20)
    {
        _first = new T[size];
        _last = _first;
        _end = _first + size;
    }
    ~SqList()
    {
        delete[] _first;
    }
    void push_back(const T &val)
    {
        if (full())
            expand();
        *_last++ = val;
    }
    T &operator[](int index)
    {
        if (index < 0 || index >= size())
        {
            throw "index is error";
        }
        return _first[index];
    }
    void insert(int index, const T &val)
    {
        if (index < 0 || index >= size())
        {
            throw "index is error";
        }
        for (int i = size() - 1; i >= index; --i)
            _first[i + 1] = _first[i];
        _first[index] = val;
        ++_last;
        if (full())
            expand();
    }
    void del(int index)
    {
        if (index < 0 || index >= size())
        {
            throw "index is error";
        }
        for (int i = index; i < size() - 1; ++i)
            _first[i] = _first[i + 1];
    }
    int size() { return _end - _first; }
    bool empty() { return _last == _first; }
    bool full() { return _last == _end; }

private:
    T *_first;
    T *_last;
    T *_end;
    void expand()
    {
        int size = _end - _first;
        T *ptmp = new T[2 * size];
        for (int i = 0; i < size; ++i)
            ptmp[i] = _first[i];
        delete[] _first;
        _first = ptmp;
        _last = _first + size;
        _end = _first + 2 * size;
    }
};
int main()
{
    SqList<int> sqlist;
    for (int i = 0; i < 10; ++i)
        sqlist.push_back(rand() % 20 + 1);
    for (int i = 0; i < sqlist.size(); ++i)
        cout << sqlist[i] << " ";
    cout << endl;
    sqlist.insert(2, 20);
    for (int i = 0; i < sqlist.size(); ++i)
        cout << sqlist[i] << " ";
    cout<<endl;
    sqlist.del(3);
    for (int i = 0; i < sqlist.size(); ++i)
        cout << sqlist[i] << " ";
}