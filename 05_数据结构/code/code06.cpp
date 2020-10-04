//code06.cpp
//BF算法
#include <iostream>
#include <string>
using namespace std;

int bf(const string &s, const string &t, const int &pos)
{
    int i = pos; //主串开始比较位置
    int j = 1, sum = 0;
    int slen = s.length();
    int tlen = t.length();
    while (i <= slen && j <= tlen)
    {
        sum++;
        if (s[i - 1] == t[j - 1])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2;
            j = 1;
        }
    }
    cout << "sum: " << sum << endl;
    if (j > tlen)
        return i - tlen;
    return -1;
}
int main()
{
    string s, t;
    int pos = 0;
    cin >> s >> t >> pos;
    cout << bf(s, t, pos) << endl;
    return 0;
}