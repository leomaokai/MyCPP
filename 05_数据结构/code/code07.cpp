//code07.cpp
//KMP算法
#include <iostream>
#include <string>
using namespace std;

void get_next(int *next, const string &t)
{
    int j = 1, k = 0;
    next[1] = 0;
    while (j < t.length())
    {
        if (k == 0 || t[j - 1] == t[k - 1])
            next[++j] = ++k;
        else
            k = next[k];
    }
}
int kmp(const string &s, const string &t, const int *next, const int &pos)
{
    int i = pos, j = 1;
    while (i <= s.length() && j <= t.length())
    {
        if (s[i - 1] == t[j - 1])
        {
            ++i;
            ++j;
        }
        else
            j = next[j];
    }
    if (j > t.length())
        return i - t.length() + 1;
    return -1;
}
int main()
{
    string s, t;
    cin >> s >> t;
    int *next = new int[t.length() + 1]();
    get_next(next, t);
    cout << kmp(s, t, next, 1) << endl;
    return 0;
}