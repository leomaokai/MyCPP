//#include<iostream>
//using namespace std;
//
//
///*
//空间配置器allocator
//* 内存开辟
//* 内存释放
//* 对象构造
//* 对象析构
//*/
//template<typename T>
//struct Allocator
//{
//	T* allocate(size_t size)//负责内存开辟
//	{
//		return (T*)malloc(sizeof(T) * size);
//	}
//	void deallocate(void* p)//负责内存释放
//	{
//		free(p);
//	}
//	void construct(T* p, const T& val)//负责对象构造
//	{
//		new (p) T(val);//定位new
//	}
//	void destroy(T* p)//负责对象析构
//	{
//		p->~T();//T类型的析构函数
//	}
//};
//
//template<typename T,typename Alloc=Allocator<T>>
//class vector
//{
//public:
//	vector(int size = 10)
//	{
//		//需要把内存的开辟和对象的构造分开处理
//		//_first = new T[size];
//		_first = _allocator.allocate(size);//开辟空间
//
//		_last = _first;
//		_end = _first + size;
//	}
//	~vector()
//	{
//		//析构容器有效的元素,然后释放堆内存
//		//delete[] _first;
//		for (T* p = _first; p != _last; ++p)
//		{
//			_allocator.destroy(p);//析构有效元素
//		}
//		_allocator.deallocate(_first);//释放堆上的内存
//		_first = _last = _end = nullptr;
//	}
//	vector(const vector<T>& rhs)
//	{
//		int size = rhs._end - rhs._first;
//		//_first = new T[size];
//		_first = _allocator.allocate(size);//开辟空间
//		int len = rhs._last - rhs._first;
//		for (int i = 0; i < len; ++i)
//		{
//			//_first[i] = rhs._first[i];
//			_allocator.construct(_first + i, rhs._first[i]);
//		}
//		_last = _first + len;
//		_end = _first + size;
//	}
//	vector<T>& operator=(const vector<T>& rhs)
//	{
//		if (this == rhs)
//			return *this;
//
//		//delete[]_first;
//		for (T* p = _first; p != _last; ++p)
//		{
//			_allocator.destroy(p);//析构有效元素
//		}
//		_allocator.deallocate(_first);//释放堆上的内存
//
//		int size = rhs._end - rhs._first;
//		//_first = new T[size];
//		_first = _allocator.allocate(size);//开辟空间
//		int len = rhs._last - rhs._first;
//		for (int i = 0; i < len; ++i)
//		{
//			//_first[i] = rhs._first[i];
//			_allocator.construct(_first + i, rhs._first[i]);
//		}
//		_last = _first + len;
//		_end = _first + size;
//
//		return *this;
//	}
//	void push_back(const T& val)//向容器末尾添加元素
//	{
//		if (full())
//			expand();
//		//*_last++ = val;
//		_allocator.construct(_last++, val);
//	}
//	void pop_back()//从容器末尾删除元素
//	{
//		//需要析构对象,而不是简单的指针减
//		//要把对象的析构和内存的释放分离开
//		if (empty())
//			return;
//		//--_last;  //不仅要减last指针,还需要析构删除的元素
//		--_last;
//		_allocator.destroy(_last);
//	}
//	T back()const//返回容器末尾的元素值
//	{
//		return *(_last - 1);
//	}
//	bool full()const { return _last == _end; }
//	bool empty()const { return _first == _last; }
//	int size()const { return _last - _first; }
//private:
//	T* _first;	//指向数组起始的位置
//	T* _last;	//指向数组中有效元素的后继位置
//	T* _end;	//指向数组空间的后继位置
//	Alloc _allocator;//定义容器的空间配置器对象
//
//	void expand()//扩容
//	{
//		int size = _end - _first;
//		//T* ptmp = new T[2 * size];
//		T* ptmp = _allocator.allocate(2 * size);
//		for (int i = 0; i < size; ++i)
//		{
//			//ptmp[i] = _first[i];
//			_allocator.construct(ptmp + i, _first[i]);
//		}
//		//delete[]_first;
//		for (T* p = _first; p != _last; ++p)
//		{
//			_allocator.destroy(p);
//		}
//		_allocator.deallocate(_first);
//
//		_first = ptmp;
//		_last = _first + size;
//		_end = _first + 2 * size;
//	}
//};
//
//class Test
//{
//public:
//	Test() { cout << "Test()" << endl; }
//	~Test() { cout << "~Test()" << endl; }
//	Test(const Test& rhs)
//	{
//		cout << "Test(const Test &)" << endl;
//	}
//};
//
//
//int main()
//{
//	Test t1, t2, t3;
//	cout << "-------------------" << endl;
//	vector<Test> vec;
//	vec.push_back(t1);
//	vec.push_back(t2);
//	vec.push_back(t3);
//	cout << "-------------------" << endl;
//	vec.pop_back();
//	cout << "-------------------" << endl;
//
//
//	return 0;
//}