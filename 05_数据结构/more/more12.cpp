//字典树
#include <iostream>
#include <string>
#include <string.h>
using namespace std;
const int maxn = 10000;
const int maxz = 26; //26个字母
int trie[maxn][maxz];
bool endflag[maxn]; //标记结束
int n, tot;         //字符串数,下标

void inserts(string s) //将字符串s插入到字典树中
{
    int len = s.length(), p = 1;
    for (int i = 0; i < len; ++i)
    {
        int ch = s[i] - 'a'; //将字符转换为数字
        if (!trie[p][ch])
            trie[p][ch] = ++tot; //记录下标
        p = trie[p][ch];
    }
    endflag[p] = true;
}
bool searchs(string s)
{
    int len = s.length(), p = 1;
    for (int i = 0; i < len; ++i)
    {
        p = trie[p][s[i] - 'a'];
        if (!p)
            return false;
    }
    return endflag[p];
}
int main()
{
    string s;
    memset(trie, 0, sizeof(trie));
    memset(endflag, false, sizeof(endflag));
    tot = 1;
    cin >> n;
    while (n--)
    {
        cin >> s;
        inserts(s);
    }
    while (1)
    {
        cout << "input query s" << endl;
        cin >> s;
        if (searchs(s))
            cout << "query ok" << endl;
        else
            cout << "query no" << endl;
    }
    return 0;
}