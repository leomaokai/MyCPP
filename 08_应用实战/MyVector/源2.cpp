#include<iostream>
using namespace std;

/*
vector������ʵ��
*/

//�ռ�������allocator
template<typename T>
struct Allocator
{
	T* allocate(size_t size)//�����ڴ濪��
	{
		return (T*)malloc(sizeof(T) * size);
	}
	void deallocate(void* p)//�����ڴ��ͷ�
	{
		free(p);
	}
	void construct(T* p, const T& val)//���������
	{
		new (p) T(val);//��λnew
	}
	void destroy(T* p)//�����������
	{
		p->~T();//T���͵���������
	}
};

template<typename T, typename Alloc = Allocator<T>>
class vector
{
public:
	vector(int size = 10)
	{
		//��Ҫ���ڴ�Ŀ��ٺͶ���Ĺ���ֿ�����
		//_first = new T[size];
		_first = _allocator.allocate(size);//���ٿռ�

		_last = _first;
		_end = _first + size;
	}
	~vector()
	{
		//����������Ч��Ԫ��,Ȼ���ͷŶ��ڴ�
		//delete[] _first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destroy(p);//������ЧԪ��
		}
		_allocator.deallocate(_first);//�ͷŶ��ϵ��ڴ�
		_first = _last = _end = nullptr;
	}
	vector(const vector<T>& rhs)
	{
		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);//���ٿռ�
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len;
		_end = _first + size;
	}
	vector<T>& operator=(const vector<T>& rhs)
	{
		if (this == rhs)
			return *this;

		//delete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destroy(p);//������ЧԪ��
		}
		_allocator.deallocate(_first);//�ͷŶ��ϵ��ڴ�

		int size = rhs._end - rhs._first;
		//_first = new T[size];
		_first = _allocator.allocate(size);//���ٿռ�
		int len = rhs._last - rhs._first;
		for (int i = 0; i < len; ++i)
		{
			//_first[i] = rhs._first[i];
			_allocator.construct(_first + i, rhs._first[i]);
		}
		_last = _first + len;
		_end = _first + size;

		return *this;
	}
	void push_back(const T& val)//������ĩβ���Ԫ��
	{
		if (full())
			expand();
		//*_last++ = val;
		_allocator.construct(_last++, val);
	}
	void pop_back()//������ĩβɾ��Ԫ��
	{
		//��Ҫ��������,�����Ǽ򵥵�ָ���
		//Ҫ�Ѷ�����������ڴ���ͷŷ��뿪
		if (empty())
			return;
		//--_last;  //����Ҫ��lastָ��,����Ҫ����ɾ����Ԫ��
		--_last;
		_allocator.destroy(_last);
	}
	T back()const//��������ĩβ��Ԫ��ֵ
	{
		return *(_last - 1);
	}
	bool full()const { return _last == _end; }
	bool empty()const { return _first == _last; }
	int size()const { return _last - _first; }

	T& operator[](int index)
	{ 
		if (index < 0 || index >= size())
		{
			throw "index is out";
		}
		return _first[index]; 
	}

	//������һ��ʵ�ֳ�������Ƕ������
	class iterator
	{
	public:
		iterator(T* ptr = nullptr)
			:_ptr(ptr)
		{}
		bool operator!=(const iterator& it)const
		{
			return _ptr != it._ptr;
		}
		void operator++()
		{
			_ptr++;
		}
		T& operator*() { return *_ptr; }
		const T& operator*()const { return *_ptr; }
	private:
		T* _ptr;
	};
	//�������ṩbegin��end����
	iterator begin() { return iterator(_first); }
	iterator end() { return iterator(_last); }
private:
	T* _first;	//ָ��������ʼ��λ��
	T* _last;	//ָ����������ЧԪ�صĺ��λ��
	T* _end;	//ָ������ռ�ĺ��λ��
	Alloc _allocator;//���������Ŀռ�����������

	void expand()//����
	{
		int size = _end - _first;
		//T* ptmp = new T[2 * size];
		T* ptmp = _allocator.allocate(2 * size);
		for (int i = 0; i < size; ++i)
		{
			//ptmp[i] = _first[i];
			_allocator.construct(ptmp + i, _first[i]);
		}
		//delete[]_first;
		for (T* p = _first; p != _last; ++p)
		{
			_allocator.destroy(p);
		}
		_allocator.deallocate(_first);

		_first = ptmp;
		_last = _first + size;
		_end = _first + 2 * size;
	}


};


int main()
{
	vector<int> vec;
	for (int i = 0; i < 20; ++i)
	{
		vec.push_back(rand() % 100 + 1);
	}
	//���õ���������
	//vector<int>::iterator it = vec.begin();
	auto it = vec.begin();
	for (; it != vec.end(); ++it)
	{
		cout << *it << " ";
	}
	cout << endl;
	//������������������ر���
	int size = vec.size();
	for (int i = 0; i < size; ++i)
	{
		cout << vec[i] << " ";
	}
	cout << endl;
	//����C++11�ṩ��foreach����,�ײ�Ϊ������
	for (int v : vec)
	{
		cout << v << " ";
	}
	cout << endl;
	return 0;
}