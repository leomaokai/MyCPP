//code09.cpp
//爬楼梯问题
#include <iostream>
#include <ctime>
using namespace std;
//递归求解,时间复杂度大
long func1(int n)
{
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;
    if (n == 3)
        return 2;
    return func1(n - 1) + func1(n - 2);
}
//动态规划,使用一个数组
void func2(const int &n, int *dp)
{
    dp[1] = 0;
    dp[2] = 1;
    dp[3] = 2;
    for (int i = 4; i <= n; ++i)
        dp[i] = dp[i - 1] + dp[i - 2];
}
int main()
{
    time_t begin, end;
    double ret;
    int n = 0;
    cin >> n;
    int *arry = new int[n + 1]();
    begin = clock();
    int func1ret = func1(n);
    end = clock();
    ret = double(end - begin) / CLOCKS_PER_SEC;
    cout << "func1:" << func1ret << "  time:" << ret << endl;
    begin = clock();
    func2(n, arry);
    end = clock();
    ret = double(end - begin) / CLOCKS_PER_SEC;
    for (int i = 1; i <= n; ++i)
        cout << arry[i] << " ";
    cout << endl;
    cout << "func2 time:" << ret << endl;
    delete[] arry;
    return 0;
}