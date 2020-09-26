//search01.cpp
//hash
#include <iostream>
#include <string.h>
#include <cmath>
using namespace std;

const int m = 10;      //哈希表长
const int nullkey = 0; //单元为空的标记

int ht[m], hc[m];
//哈希函数
int hashfun(int key)
{
    return key % 7;
}
//线性探测法
int linedetect(int ht[], int h0, int key, int &count)
{
    int hi=-1;
    for (int i = 1; i < m; ++i)
    {
        count++;
        hi = (h0 + i) % m;
        if (ht[hi] == nullkey)
            return hi;
        else if (ht[hi] == key)
            return hi;
    }
    return -1;
}
//二次探测法
int seconddetect(int ht[], int h0, int key, int &count)
{
    int hi;
    for (int i = 1; i <= m / 2; ++i)
    {
        int i1 = i * i;
        count++;
        hi = (h0 + i1) % m;
        if (ht[hi] == nullkey)
            return hi;
        else if (ht[hi] == key)
            return hi;
        int i2 = -i1;
        count++;
        hi = (h0 + i2) % m;
        if (hi < 0)
            hi += m;
        if (ht[hi] == nullkey)
            return hi;
        else if (ht[hi] == key)
            return hi;
    }
    return -1;
}
//哈希查找
int searchhash(int ht[], int key)
{
    //在哈希表ht中查找关键字为key的元素
    int h0 = hashfun(key);
    int hi = 0;
    int count = 1;
    if (ht[h0] == nullkey)
        return -1;
    else if (ht[h0] == key)
    {
        cout << "ok " << count << endl;
        return h0;
    }
    else
    {
        hi = linedetect(ht, h0, key, count);
        //hi=seconddetect(ht,h0,key,count);
        if (ht[hi] == key)
        {
            cout << "ok " << count << endl;
            return hi;
        }
        else if (hi == -1)
            return -1;
    }
}
//存入哈希表
bool inserthash(int ht[], int key)
{
    int h0 = hashfun(key);
    int hi = -1, count = 1;
    if (ht[h0] == nullkey)
    {
        hc[h0] = 1;
        ht[h0] = key;
        return true;
    }
    else
    {
        hi = linedetect(ht, h0, key, count);
        //hi=seconddetect(ht,h0,key,count);
        if ( ht[hi] == nullkey)
        {
            hc[hi] = count;
            ht[hi] = key;
            return true;
        }
    }
    return false;
}
int main()
{
    memset(ht, nullkey, m);
    memset(hc, 0, m);
    for (int i = 0; i < m; ++i)
    {
        int key = rand() % 10;
        if (inserthash(ht, key))
            cout << "insert " << key << endl;
    }
    if (searchhash(ht, 2) == -1)
        cout << "search no" << endl;
    else
        cout << "search ok" << endl;
    cout << "hash: " << '\t';
    for (int i = 0; i < m; ++i)
        cout << i << '\t';
    cout << endl;
    cout << "key:  " << '\t';
    for (int i = 0; i < m; ++i)
        cout << ht[i] << '\t';
    cout << endl;
    cout << "cout: " << '\t';
    for (int i = 0; i < m; ++i)
        cout << hc[i] << '\t';
    cout << endl;
    return 0;
}
