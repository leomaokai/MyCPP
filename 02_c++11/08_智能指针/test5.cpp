//test5.cpp
#include <iostream>
#include <memory>
#include <functional>
using namespace std;

//智能指针默认资源释放方式:  delete ptr
//并不是所有资源delete
//数组:delete [] ptr;
//文件:fclose(FILE*)
template <typename T>
class Mydeletor
{
public:
    void operator()(T *ptr) const
    {
        delete[] ptr;
        cout << "delete []" << endl;
    }
};

int main()
{
    //自定义类删除器
    unique_ptr<int, Mydeletor<int>> ptr1(new int[10]);

    //通过lambda表达式定义删除器
    unique_ptr<FILE, function<void(FILE *)>> ptr2(fopen("test5.txt", "a"),
                                                  [](FILE *fp) -> void {
                                                      fclose(fp);
                                                      cout << "fclose()" << endl;
                                                  });
    return 0;
}
