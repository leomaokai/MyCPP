//test1.cpp
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <list>
using namespace std;

class Observer //观察者抽象类
{
public:
    //处理消息的接口
    virtual void handler(int msgid) = 0;
};
class Observer1 : public Observer
{
public:
    void handler(int msgid)
    {
        switch (msgid)
        {
        case 1:
            cout << "Observer1 recv 1 msg!" << endl;
            break;
        case 2:
            cout << "Observer1 recv 2 msg!" << endl;
            break;
        default:
            cout << "Observer1 recv unkonw msg!" << endl;
            break;
        }
    }
};
class Observer2 : public Observer
{
public:
    void handler(int msgid)
    {
        switch (msgid)
        {
        case 1:
            cout << "Observer2 recv 1 msg!" << endl;
            break;
        case 3:
            cout << "Observer2 recv 3 msg!" << endl;
            break;
        default:
            cout << "Observer2 recv unkonw msg!" << endl;
            break;
        }
    }
};

class Subject
{
public:
    //给主题增加观察者对象
    void addobserver(Observer *obser, int msgid)
    {
        _submap[msgid].push_back(obser);
        // auto it=_submap.find(msgid);
        // if(it!=_submap.end())
        // {
        //     it->second.push_back(obser);
        // }
        // else
        // {
        //     list<Observer*> lis;
        //     lis.push_back(obser);
        //     _submap.insert({msgid,lis});
        // }
    }
    //主题检测发生改变,通知相应的观察者对象处理事件
    void dispatch(int msgid)
    {
        auto it = _submap.find(msgid);
        if (it != _submap.end())
        {
            for (Observer *pobser : it->second)
            {
                pobser->handler(msgid);
            }
        }
    }

private:
    unordered_map<int, list<Observer*>> _submap;
};
int main()
{
    Subject subject;
    Observer *p1=new Observer1();
    Observer *p2=new Observer2();

    subject.addobserver(p1, 1);
    subject.addobserver(p1, 2);
    subject.addobserver(p2, 1);
    subject.addobserver(p2, 3);
    int msgid=0;
    for(;;)
    {
        cout<<"input msgid"<<endl;
        cin>>msgid;
        if(msgid==-1)
            break;
        subject.dispatch(msgid);
    }
    return 0;
}