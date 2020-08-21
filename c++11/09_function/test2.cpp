//test2.cpp
#include <iostream>
#include <functional>
#include <map>
using namespace std;
void dosignin() { cout << "登录成功" << endl; }
void doregister() { cout << "注册成功" << endl; }
void dosignout() { cout << "退出成功" << endl; }
int main()
{
    int choice = 0;
    map<int, function<void()>> action;
    action.insert({1, dosignin});
    action.insert({2, doregister});
    action.insert({3, dosignout});
    while (1)
    {
        cout << "*********" << endl;
        cout << "1.登录" << endl;
        cout << "2.注册" << endl;
        cout << "3.退出" << endl;
        cout << "*********" << endl;
        cin >> choice;

        auto it = action.find(choice);
        if (it == action.end())
        {
            cout << "选择无效" << endl;
        }
        else
        {
            it->second();
        }
    }
}
