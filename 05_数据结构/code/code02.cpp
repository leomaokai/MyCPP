//code02.cpp
//链表
#include <iostream>
using namespace std;
struct Dlist
{
    int data;
    Dlist *next;
};
class List
{
public:
    List()
    {
        _head = new Dlist();
        _head->data = 0;
        _head->next = nullptr;
        _ptr = _head;
        _size = 0;
    }
    void push_back(int val)
    {
        Dlist *ptmp = new Dlist();
        ptmp->data = val;
        ptmp->next = nullptr;
        _ptr->next = ptmp;
        _ptr = ptmp;
        _size++;
    }
    Dlist *findnode(int pos)
    {
        Dlist *p = _head->next;
        if (pos < 0)
        {
            throw "pos is error";
        }
        if (pos == 0)
        {
            return _head;
        }
        if (p == nullptr)
        {
            throw "list is empty";
        }
        while (--pos)
        {
            p = p->next;
        }
        return p;
    }
    int size() const { return _size; }
    void insert(int index, int val)
    {
        Dlist *p = findnode(index - 1);
        Dlist *ptmp = new Dlist();
        ptmp->data = val;
        ptmp->next = p->next;
        p->next = ptmp;
        _size++;
    }
    void del(int index)
    {
        Dlist *p = findnode(index - 1);
        Dlist *ptmp = new Dlist();
        ptmp = p->next;
        p->next = p->next->next;
        delete ptmp;
        _size--;
    }
    Dlist *_head;

private:
    Dlist *_ptr;
    int _size;
};
int main()
{
    List mylist;
    mylist.push_back(10);
    mylist.push_back(20);
    mylist.push_back(30);
    mylist.push_back(40);
    mylist.push_back(50);
    Dlist *p1 = mylist.findnode(3);
    cout << p1->data << endl;
    Dlist *p2 = mylist._head->next;
    for (int i = 0; i < mylist.size(); ++i)
    {
        cout << p2->data << " ";
        p2 = p2->next;
    }
    cout << endl;
    mylist.insert(2, 100);
    p2 = mylist._head->next;
    for (int i = 0; i < mylist.size(); ++i)
    {
        cout << p2->data << " ";
        p2 = p2->next;
    }
    cout << endl;
    mylist.del(1);
    p2 = mylist._head->next;
    for (int i = 0; i < mylist.size(); ++i)
    {
        cout << p2->data << " ";
        p2 = p2->next;
    }
    cout << endl;
    return 0;
}