#include <iostream>
#include <stack>
#include <string>
using namespace std;
/*
由中缀表达式求后缀表达式的关键
判断栈顶运算符与将要入栈运算符的优先级:(乘除优先于加减)
将要入栈运算符的优先级若小于等于栈顶运算符的优先级,则输出栈顶运算符
循环判断直到栈空或遇到左括号
将将要入栈的运算符入栈
*/
void solution(string s)
{
    stack<char> strstack;
    int len = s.length();
    for (int i = 0; i < len; ++i)
    {
        char t = s[i];
        if ((int)s[i] < 40 || (int)s[i] > 47) //非算术运算符直接输出
            cout << s[i] << " ";
        else if (strstack.empty() || t == '(') //栈为空或字符为 ( 直接入栈
            strstack.push(t);
        //关键
        else
        {
            while (!strstack.empty())
            {
                char temp = strstack.top(); //栈顶运算符赋值给temp
                if (t == '+' || t == '-')
                {
                    if (temp == '(')
                        break;
                    strstack.pop();
                    cout << temp << " ";
                }
                else if (t == '*' || t == '/')
                {
                    if (temp == '*' || temp == '/')
                    {
                        strstack.pop();
                        cout << temp << " ";
                    }
                    else
                        break;
                }
                else if (t == ')')
                {
                    strstack.pop();
                    if (temp == '(')
                        break;
                    cout << temp << " ";
                }
            }
            if (t != ')')
                strstack.push(t);
        }
    }
    while (!strstack.empty()) //将栈中的剩余运算符输出
    {
        char temp = strstack.top();
        cout << temp << " ";
        strstack.pop();
    }
    cout << endl;
}
int main()
{
    solution("A*B*C");
    solution("-A+B-C+D");
    solution("(A+B)*D+E/(F+A*D)+C");
    solution("A*B-C/B^2");
    return 0;
}