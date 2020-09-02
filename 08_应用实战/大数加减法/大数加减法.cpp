#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class BigInt
{
public:
    BigInt(string str) : strDigit(str) {}

private:
    string strDigit; //使用字符串存储大整数

    friend ostream &operator<<(ostream &out, const BigInt &src);
    friend BigInt operator+(const BigInt &lhs, const BigInt &rhs);
    friend BigInt operator-(const BigInt &lhs, const BigInt &rhs);
};
//重载cout<<的方法
ostream &operator<<(ostream &out, const BigInt &src)
{
    out << src.strDigit;
    return out;
}
//大数加法,重载+
BigInt operator+(const BigInt &lhs, const BigInt &rhs)
{
    string result;//保存结果
    bool flag = false;//进位标志
    int size1 = lhs.strDigit.length() - 1;
    int size2 = rhs.strDigit.length() - 1;
    int i = size1;
    int j = size2;
    //当两个数字都存在时
    for (; i >= 0 && j >= 0; --i, --j)
    {
        /*
        字符0的ASC码为32 剩下数字以此加一
        '1'-'0'=1  不减'0'也可以,
        但最后的结果一定要加上'0'才能表示那个数字字符
        */
        int ret = lhs.strDigit[i] - '0' + rhs.strDigit[j] - '0';
        //进位操作,考虑前一位是否发生进位
        if (flag)
        {
            ret += 1;
            flag = false;
        }
        if (ret >= 0)
        {
            ret %= 10;
            flag = true;
        }

        result.push_back(ret + '0');
    }
    //一个数字加完,还剩一个数字时
    if (i >= 0)
    {
        while (i >= 0)
        {
            int ret = lhs.strDigit[i] - '0';
            if (flag)
            {
                ret += 1;
                flag = false;
            }
            if (ret >= 0)
            {
                ret %= 10;
                flag = true;
            }
            result.push_back(ret + '0');
            i--;
        }
    }
    else if (j >= 0)
    {
        while (j >= 0)
        {
            int ret = rhs.strDigit[j] - '0';
            if (flag)
            {
                ret += 1;
                flag = false;
            }

            if (ret >= 10)
            {
                ret %= 10;
                flag = true;
            }
            result.push_back(ret + '0');
            j--;
        }
    }

    //考虑最后一位是否发生进位
    if (flag)
    {
        result.push_back('1');
    }

    //反转字符串
    reverse(result.begin(), result.end());
    return result;
}
//大数相减,重载-
BigInt operator-(const BigInt &lhs, const BigInt &rhs)
{
    string result;
    bool flag = false;
    bool minor = false;
    /*
    用比较大的字符串减小的字符串
    若第一个数字小,则交换两个数字,保持大减小,结果前面加负号
    */
    string maxStr = lhs.strDigit;
    string minStr = rhs.strDigit;
    //长字符串的数字一定大于较短字符串的数字
    if (maxStr.length() < minStr.length())
    {
        maxStr = rhs.strDigit;
        minStr = lhs.strDigit;
        minor = false;//标记是否加负号
    }
    //字符串长度相等时也有大小之分
    else if (maxStr.length() == minStr.length())
    {
        if (maxStr < minStr)
        {
            maxStr = rhs.strDigit;
            minStr = lhs.strDigit;
            minor = true;
        }
        else if (maxStr == minStr)
        {
            return string("0");
        }
    }
    //类似于加法操作,注意是否发生借位
    int size1 = maxStr.length() - 1;
    int size2 = minStr.length() - 1;
    int i = size1;
    int j = size2;

    for (; i >= 0 && j >= 0; --i, --j)
    {
        int ret = (maxStr[i]-'0') - (minStr[j]-'0');
        
        if (flag)
        {
            ret -= 1;
            flag = false;
        }
        if (ret < 0)
        {
            ret += 10;
            flag = true;
        }
        result.push_back(ret + '0');
    }
    //因为之前设置第一个数字一定大于第二个,所以只存在一种剩余情况
    while (i >= 0)
    {
        int ret = maxStr[i] - '0';
        if (flag)
        {
            ret -= 1;
            flag = false;
        }
        if (ret < 0)
        {
            ret += 10;
            flag = true;
        }
        result.push_back(ret + '0');
        i--;
    }
    //用另一个字符串记录结果,有效避免反转出现000001的情况
    string retStr;
    auto it = result.rbegin();//反向遍历
    for (; it != result.rend(); ++it)
    {
        if (*it != '0')
        {
            break;
        }
    }
    for (; it != result.rend(); ++it)
    {
        retStr.push_back(*it);
    }
    if (minor)
    {
        retStr.insert(retStr.begin(), '-');
    }
    return retStr;
}

int main()
{
    BigInt int1("88888888888800000000000");
    BigInt int2("88888888888811111100000");
    cout << int1 + int2 << endl;
    cout << int1 - int2 << endl;
    BigInt int3("11111111");
    BigInt int4("11111110");
    cout << int3 - int4 << endl;
    cout << int4 - int3 << endl;
    return 0;
}