//code10.cpp
//最长上升子序列
#include <iostream>
using namespace std;

int solution(const int &n, int *dp, int *a)
{
    int ret = 0;
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = 1;
        for (int j = 1; j < i; ++j)
            if (a[j] < a[i])
                dp[i] = max(dp[i], dp[j] + 1);
        if (dp[i] > ret)
            ret = dp[i];
    }
    return ret;
}
int main()
{
    int n = 0;
    cin >> n;
    int *dp = new int[n + 1]();
    int *a = new int[n + 1]();
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    cout << solution(n, dp, a) << endl;
    delete[] dp, a;
    return 0;
}