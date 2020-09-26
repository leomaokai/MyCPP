//单向链表
//第0个位置为头结点
#include <iostream>
using namespace std;

template <typename T>
struct listnode
{
    T data;
    listnode *next;
};
template <typename T>
class linklist
{
public:
    linklist()
    {
        _head = new listnode<T>();
        _head->next = nullptr;
        _ptr = _head;
        _size = 0;
    }
    ~linklist()
    {
        listnode<T> *p = _head->next;
        for (int i = 0; i < _size; ++i)
        {
            if (p != nullptr)
                delete p;
            p = p->next;
        }
    }
    void push_back(const T &val) //尾插
    {
        listnode<T> *temp = new listnode<T>();
        temp->data = val;
        temp->next = nullptr;
        _ptr->next = temp;
        _ptr = temp;
        _size++;
    }
    listnode<T> *findnode(int pos) //返回pos位置的结点
    {
        listnode<T> *p = _head->next;
        if (pos < 0)
            throw "pos is error";
        if (empty())
            throw "list is empty";
        if (pos == 0)
            return _head;
        while (--pos)
            p = p->next;
        return p;
    }
    void insert(const int &pos, const T &val) //在pos位置插入元素val
    {
        if (pos <= 0 || pos > _size + 1)
            throw "pos id error";
        listnode<T> *p = findnode(pos - 1);
        listnode<T> *temp = new listnode<T>();
        temp->data = val;
        temp->next = p->next;
        p->next = temp;
        _size++;
    }
    void del(const int &pos) //删除pos位置的结点
    {
        if (pos <= 0 || pos > _size)
            throw "pos id error";
        listnode<T> *p = findnode(pos - 1);
        listnode<T> *temp = findnode(pos);
        p->next = temp->next;
        delete temp;
        --_size;
    }
    void locate(const T &val) //返回某元素的位置
    {
        listnode<T> *p = _head->next;
        bool flag = true;
        for (int i = 1; i <= _size; ++i)
        {
            if (p->data == val)
            {
                cout << i << endl;
                flag = false;
            }
            p = p->next;
        }
        if (flag) //没有找到
            cout << "no val" << endl;
    }
    void number(const T &val) //返回元素val的个数
    {
        listnode<T> *p = _head->next;
        int count = 0;
        for (int i = 0; i < _size; ++i)
        {
            if (p->data == val)
                count++;
            p = p->next;
        }
        cout << count << endl;
    }
    void exchange(const int &pos) //交换pos位置和next的位置
    {
        if (pos <= 0 || pos > _size)
            throw "pos id error";
        listnode<T> *p1 = findnode(pos - 1); //pos前一个结点
        listnode<T> *p2 = findnode(pos);     //pos位置的结点
        listnode<T> *p3 = findnode(pos + 1); //pos后一个结点
        p1->next = p2->next;
        p2->next = p3->next;
        p3->next = p2;
    }
    void print()
    {
        if (!empty())
        {
            listnode<T> *p = _head->next;
            for (int i = 0; i < _size; ++i)
            {
                cout << p->data << " ";
                p = p->next;
            }
            cout << endl;
        }
        else
        {
            cout << "the linklist is empty" << endl;
        }
    }
    bool empty() { return _head->next == nullptr; }

private:
    listnode<T> *_head; //头结点
    listnode<T> *_ptr;  //指向最后一个结点
    int _size;          //链表大小
};
int main()
{
    linklist<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    list.push_back(2);
    list.print(); //1 2 3 2
    list.insert(1, 5);
    list.print(); //5 1 2 3 2
    list.del(1);
    list.print();   //1 2 3 2
    list.locate(1); //1
    list.number(2); //2
    list.exchange(2);
    list.print(); //1 3 2 2
    return 0;
}