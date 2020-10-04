//code11.cpp
//最长公共子序列
#include <iostream>
#include <string>
using namespace std;

int dp[100][100]{};
int c[100][100]{};
int solution(const string &s, const string &t)
{
    for (int i = 1; i <= s.length(); ++i)
        for (int j = 1; j <= t.length(); ++j)
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                c[i][j] = 1;
            }
            else
            {
                if (dp[i][j - 1] >= dp[i - 1][j])
                {
                    dp[i][j] = dp[i][j - 1];
                    c[i][j] = 2;
                }
                else
                {
                    dp[i][j] = dp[i - 1][j];
                    c[i][j] = 3;
                }
            }
}
void func1(int i, int j, string &s)
{
    if (i == 0 || j == 0)
        return;
    if (c[i][j] == 1)
    {
        func1(i - 1, j - 1, s);
        cout << s[i - 1] << " ";
    }
    else if (c[i][j] == 2)
        func1(i, j - 1, s);
    else
        func1(i - 1, j, s);
}
int main()
{
    string s, t;
    cin >> s >> t;
    solution(s, t);
    cout << dp[s.length()][t.length()] << endl;
    func1(s.length(), t.length(), s);
    return 0;
}