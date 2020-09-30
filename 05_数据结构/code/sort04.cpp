//sort04.cpp
//顺序队列实现基数排序
#include <iostream>
using namespace std;

//求待排序序列最大元素位数
int Maxbit(const int *A, const int &n)
{
    int maxvalue = A[0], digits = 0; //初始化最大元素为A[0],最大位数为0
    for (int i = 1; i < n; ++i)      //找序列中最大元素
        if (A[i] > maxvalue)
            maxvalue = A[i];
    while (maxvalue != 0) //分解得到最大元素的位数
    {
        ++digits;
        maxvalue /= 10;
    }
    return digits;
}
//求x第bit位上的数字
int bitnumber(const int &x, const int &bit)
{
    int temp = 1;
    for (int i = 1; i < bit; ++i)
        temp *= 10;
    return (x / temp) % 10;
}
//基数排序
void radixsort(int *A,const int &n)
{
    int i, j, k, bit, maxbit;
    maxbit = Maxbit(A, n); //求最大元素位数
    cout<<"the bigest bit:"<<endl;
    cout << maxbit << endl;
    int **B = new int *[10]();
    for (i = 0; i < 10; ++i)
        B[i] = new int[n + 1]();
    //从个位到高位,对不同的位数进行桶排序
    for (bit = 1; bit <= maxbit; ++bit)
    {
        for (j = 0; j < n; ++j) //分配到桶
        {
            int num = bitnumber(A[j], bit); //取A[j]第bit位上的数字
            int index = ++B[num][0];
            B[num][index] = A[j];
        }
        for (i = 0, j = 0; i < 10; ++i) //收集
        {
            for (k = 1; k <= B[i][0]; ++k) //每次从桶低处往高处读
                A[j++] = B[i][k];
            B[i][0] = 0; //收集后位置清零
        }
    }
    for (i = 0; i < 10; ++i)
        delete[] B[i];
    delete B;
}
int main()
{
    int n = 0;
    cout << "input n" << endl;
    cin >> n;
    int *A = new int[n]();
    cout << "input val" << endl;
    for (int i = 0; i < n; ++i)
        cin >> A[i];
    radixsort(A, n);
    cout << "sort:" << endl;
    for (int i = 0; i < n; ++i)
        cout << A[i] << " ";
    cout << endl;
    delete[] A;
    return 0;
}