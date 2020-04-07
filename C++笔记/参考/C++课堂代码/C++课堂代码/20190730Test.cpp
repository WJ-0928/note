#include <iostream>
using namespace std;

// new/delete ������ͷŵ���Ԫ�صĿռ�
// new[]/delete[] ������ͷ�һ�������Ŀռ�


#if 0
int main()
{
	int array[10];
	// C++���ṩ��new��delete����������ռ�
	int* p1 = new int;
	int* p2 = new int(10);
	int* p3 = new int[10];
	int* p4 = new int[10]{1,2,3,4,5,6,7,8,9,0};

	delete p1;
	delete p2;
	delete[] p3;
	delete[] p4;

	return 0;
}
#endif

#if 0
// malloc/free  new/delete new[]/delete[]
// һ��Ҫƥ�䣺������ܻ�����ڴ�й©���ߴ������
// ���������Ͳ������

#if 0
void TestNew()
{
	int* p1 = (int*)malloc(sizeof(int));
	delete p1;

	int* p2 = (int*)malloc(sizeof(int));
	delete[] p2;

	int* p3 = new int;
	free(p3);

	int* p4 = new int;
	delete[] p4;

	int* p5 = new int[10];
	free(p5);

	int* p6 = new int[10];
	delete p6;
}


int main()
{
	TestNew();
	_CrtDumpMemoryLeaks();
	return 0;
}
#endif

class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout << "Test(int):" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};

void TestNew()
{
	Test* p1 = (Test*)malloc(sizeof(Test));
	delete p1;

	Test* p2 = (Test*)malloc(sizeof(Test));
	delete[] p2;

	Test* p3 = new Test;
	free(p3);

	Test* p4 = new Test;
	delete[] p4;

	Test* p5 = new Test[10];
	free(p5);

	Test* p6 = new Test[10];
	delete p6;
}

int main()
{
	TestNew();
	return 0;
}
#endif

#if 0
// new �� delete
class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout << "Test(int):" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};

void TestNew()
{
	// malloc��������ù��캯��---malloc�Ĳ��ܽ����Ϊ����-->������С��һ���ڴ�ռ�
	Test* p1 = (Test*)malloc(sizeof(Test));


	// new��ʵ����ù��캯��--->new���Ľ������һ�������Ķ���
	Test* p2 = new Test;

	// free: ���ͷſռ��ڼ䲻�������������
	free(p1);

	// delete:���ͷſռ��ڼ��������������������е���Դ�����
	delete p2;

	// new[]: ������ռ� + ����N�ι��캯��
	Test* p3 = new Test[10];

	// delete[]�� ���ͷſռ� + ����N������
	delete[] p3;
}

int main()
{
	TestNew();
	_CrtDumpMemoryLeaks();
	return 0;
}
#endif

#if 0
class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout << "Test(int):" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};


int main()
{
	_CrtMemBlockHeader
	Test* p = new Test[10];
	delete[] p;

	return 0;
}
#endif


#if 0
struct ListNode
{
	ListNode* _next;
	ListNode* _prev;
	int _data;

	void* operator new(size_t n)
	{
		void* p = nullptr;
		p = allocator<ListNode>().allocate(1);
		cout << "memory pool allocate" << endl;
		return p;
	}

	void operator delete(void* p)
	{
		allocator<ListNode>().deallocate((ListNode*)p, 1);
		cout << "memory pool deallocate" << endl;
	}
};



class List
{
public:
	List()
	{
		_head = new ListNode;
		_head->_next = _head;
		_head->_prev = _head;
	}

	~List()
	{
		ListNode* cur = _head->_next;
		while (cur != _head)
		{
			ListNode* next = cur->_next;
			delete cur;
			cur = next;
		}
		delete _head;
		_head = nullptr;
	}
private:
	ListNode* _head;
};

int main()
{
	List l;
	return 0;
}
#endif

#if 0
void* operator new(size_t size, char* fileName, char* funcName, size_t lineNo)
{
	cout << fileName << "-" << funcName << "-" << lineNo << "-" << size << endl;
	return malloc(size);
}


#define  new new(__FILE__, __FUNCDNAME__, __LINE__) 
int main()
{
	int* p = new int;
	delete p;

	return 0;
}
#endif

#if 0
class Test
{
public:
	Test(int data = 0)
		: _data(data)
	{
		cout << "Test(int):" << this << endl;
	}

	~Test()
	{
		cout << "~Test():" << this << endl;
	}

private:
	int _data;
};

void TestFunc()
{
	int* p = new int[10];
	FILE* pf = fopen("1.txt", "rb");
	if (nullptr == pf)
	{
		return;
	}

	// �ļ�����
	fclose(pf);
}

int main()
{
	Test* pt = (Test*)malloc(sizeof(Test));
	new(pt) Test(10);

	pt->~Test();
	free(pt);
	//delete pt;
	_CrtDumpMemoryLeaks();
	return 0;
}
#endif

#if 0
int main()
{
	void* p = new char[0xfffffffful];
	cout << "new:" << p << endl;
	return 0;
}
#endif

#if 0
typedef int DataType;

struct SeqList
{
	DataType* _array;
	size_t _capacity;
	size_t _size;
};
#endif

#if 0
// ͨ�õļӷ��������������޹�
int Add(int left, int right)
{
	return left + right;
}

double Add(double left, double right)
{
	return left + right;
}

char Add(char left, char right)
{
	return left + right;
}



int main()
{
	return 0;
}
#endif

#if 0
// class ����typename T
// ���ģ������б����ж�����ͣ��������֮���ö��Ÿ���
// ÿ������ǰ�����class����typename�Ĺؼ���

// �ӷ�����ģ��
template<class T>
T Add(T left, T right)
{
	cout << typeid(T).name() << endl;
	return left + right;
}

// watch: ����ģ�岻�������ĺ������Ǳ��������ɴ���Ĺ���

int main()
{
	// �Ժ���ģ�����ʵ����
	// �ڱ����ڼ䣬����ʵ����������ʵ�����ͣ�����ģ�庯����T��ʵ�����ͣ�
	// �������ݵ�ʵ���������ɴ���������͵Ĵ���
	Add(1, 2);  // Add<int>
	Add(1.0, 2.0); // Add<double>
	Add('1', '2'); // Add<char>

	return 0;
}
#endif

// template<class T1, class T2>
// T1 Add(const T1& left, const T2& right)
// {
// 	return left + right;
// }

#if 0
class Complex
{
public:
	Complex(double real, double image)
		: _real(real)
		, _image(image)
	{}

// 	Complex operator+(const Complex& c)const
// 	{
// 		Complex ret(_real+c._real, _image+c._image);
// 		return ret;
// 	}

	Complex operator+(const Complex& c)const
	{
		// ��������
		return Complex(_real + c._real, _image + c._image);
	}

private:
	double _real;
	double _image;
};

template<class T>
T Add(const T& left, const T& right)
{
	return left + right;
}


int main()
{
	// ��ʽʵ������û��ֱ��ָ��T��ʵ�����ͣ�T��������Ҫ���в������ݲſ���ȷ��
	// ����������Բ������ݵĽ��������ʽ����ת��
	Add(1, 2);  // Add<int>
	Add(1.0, 2.0); // Add<double>
	Add('1', '2'); // Add<char>
	Add(1, (int)2.0);

	// ��ʽʵ��������ȷָ��T��ʵ�����ͣ� ������ƥ��ʱ�����ܻᷢ����ʽ����ת��
	Add<int>(1, 2.0);
	//Add<int>(1, "123");

	Complex c1(1.0, 2.0);
	Complex c2(3.0, 4.0);

	Add(c1, c2);
	return 0;
}
#endif


#if 0
int Add(int left, int right)
{
	return left + right;
}

template<class T1, class T2>
T1 Add(T1 left, T2 right)
{
	return left + right;
}

int main()
{
	Add(1, 2);

	// �Ժ���ģ����ʽʵ����
	//Add<>(1, 2);  // Add<int>
	Add(1, 2.0);
	return 0;
}
#endif

#if 0
#include <assert.h>


template<class T>
class SeqList
{
public:
	SeqList(size_t capacity = 10)
		: _array(new T[capacity])
		, _capacity(capacity)
		, _size(0)
	{}

	SeqList(size_t n, const T& data = T())
		: _array(new T[n])
		, _capacity(n)
		, _size(n)
	{
		for (size_t i = 0; i < _capacity; ++i)
			_array[i] = data;
	}

	~SeqList()
	{
		if (_array)
		{
			delete[] _array;
			_array = nullptr;
			_capacity = 0;
			_size = 0;
		}
	}

	void PushBack(const T& data);
	void PopBack();

	size_t Size()const
	{
		return _size;
	}

	size_t Capacity()const
	{
		return _capacity;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	T& operator[](size_t index)
	{
		assert(index < _size);
		return _array[index];
	}

	const T& operator[](size_t index)const
	{
		assert(index < _size);
		return _array[index];
	}

	void PrintSeqList()
	{
		for (size_t i = 0; i < _size; ++i)
		{
			cout << _array[i] << " ";
		}
		cout << endl;
	}

private:
	T* _array;
	size_t _capacity;
	size_t _size;
};


template<class T>
void SeqList<T>::PushBack(const T& data)
{
	// _CheckCapacity();
	_array[_size++] = data;
}

template<class T>
void SeqList<T>::PopBack()
{
	if (0 == _size)
		return;

	--_size;
}


int main()
{
	SeqList<int> s1;
	s1.PushBack(1);
	s1.PushBack(1);
	s1.PushBack(2);
	s1.PushBack(3);
	s1.PushBack(4);

	s1.PrintSeqList();

	s1[0] = 0;
	s1.PrintSeqList();
	cout << s1.Size() << endl;
	cout << s1.Capacity() << endl;
	cout << s1[3] << endl;

	// һ�������ռ�---����֧���漴����



	SeqList<double> s2;
	s2.PushBack(1.0);
	s2.PushBack(2.0);
	s2.PushBack(3.0);
	s2.PushBack(4.0);


	const SeqList<int> s3(10, 5);
	cout << s3[5] << endl;

	s3[5] = 10;

	return 0;
}
#endif


#include <string>


#if 0
int main()
{
	string s1;
	string s2("hello");
	string s3(10, '$');
	string s4(s2);

	// string��֧��C++��׼���������
	cin >> s1;
	cout << s1 << endl;

	// �����ַ����ķ�ʽ
	for (auto e : s2)
		cout << e;
	cout << endl;

	for (size_t i = 0; i < s3.size(); ++i)
		cout << s3[i];
	cout << endl;

	// ���õ���������----����ʹ��
	// ��������������һ��ָ��
	// string: [begin,end)---begin:�������ַ���λ��  end:���һ����Ч�ַ�����һ��λ��('\0')
	//string::iterator it = s4.begin();
	auto it = s4.begin();
	while (it != s4.end())
	{
		cout << *it;
		++it;
	}
	cout << endl;

	return 0;
}
#endif

#if 0
// capacity���:
int main()
{
	string s("hello");
	cout << s.size() << endl;
	cout << s.length() << endl;
	cout << s.capacity() << endl;

	s.clear();
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	if (s.empty())
	{
		cout << "empty" << endl;
	}
	else
	{
		cout << "not empty" << endl;
	}
	return 0;
}
#endif


#if 0
// void resize(size_t n, char ch): ��string������Ч�ַ��ı䵽n���������λ�ò���ch���
// resize����:�ı�string����Ч�ַ��ĸ���
// ����Ч�ַ��������ൽn���������λ����Ҫʹ��ch���(������Ҫ����)
// ����Ч�ַ��������ٵ�n��: ֻ�޸���Ч�ַ�������������С�ռ�
int main()
{
	string s("hello");
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	// ����s����Ч�ַ�����
	s.resize(10, '!');
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.resize(20, '$');
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	// ����s����Ч�ַ��ĸ���
	s.resize(18);
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.resize(6);
	cout << s << endl;
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	return 0;
}
#endif

#if 0
// ���ݣ�
// void reserve(size_t n): �ı�ײ������Ĵ�С�������޸���ЧԪ�صĸ���
// 1. ���������� n <= �ɿռ��С  ��������  n > �ɿռ��С  ����
// 2. ��С����:  n > 15 ������С   n <= 15 ��С����
int main()
{
	string s("hello");
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.reserve(10);
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.reserve(20);
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.reserve(80);
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.reserve(60);
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.reserve(30);
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.reserve(16);
	cout << s.size() << endl;
	cout << s.capacity() << endl;

	s.reserve(8);
	cout << s.size() << endl;
	cout << s.capacity() << endl;
	return 0;
}
#endif

#if 0
int main()
{
	string s1;
	s1.resize(10, '$');
	s1[0] = '%';

	string s2;
	s2.reserve(10);
	s2[0] = '%';
	cout << s2 << endl;
	return 0;
}
#endif

#if 0
int main()
{
	string s("hello");
	cout << s << endl;

	reverse(s.begin(), s.end());
	cout << s << endl;

	return 0;
}
#endif

#if 0
int main()
{
	string s1;
	s1 += 'I';

	string s2(" Love ");
	s1 += s2;

	s1 += "china";

	string s3(" too ");
	s1.append(s3);
	s1.append("!!!");
	s1.append(6, '.');
	cout << s1 << endl;
	return 0;
}
#endif


#if 0
void TestPushBack()
{
	string s;
	//s.reserve(100);
	size_t sz = s.capacity();
	cout << "making s grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		s.push_back('c');
		if (sz != s.capacity())
		{
			sz = s.capacity();
			cout << "capacity changed: " << sz << '\n';
		}
	}
}

int main()
{
	string s("IYOU");
	s.insert(1, " LOVE ");
	cout << s << endl;

	TestPushBack();

	return 0;
}
#endif

#if 0
int main()
{
	string s("hello wrold");
	cout << s << endl;

	s.erase(s.begin()+s.find(' '), s.end());
	cout << s << endl;
	return 0;
}
#endif

#if 0
int main()
{
	string s("11sda.sdas1.txt");

	string ret = s.substr(s.rfind('.')+1);
	cout << ret << endl;


	string strNet("https://www.baidu.com/s?wd=retrieved&rsv_spt=1&rsv_iqid=0xdd3d1d550000b6c9&issp=1&f=8&rsv_bp=1&rsv_idx=2&ie=utf-8&tn=62095104_15_oem_dg&rsv_enter=1&rsv_dl=ib&rsv_sug3=2&rsv_sug1=1&rsv_sug7=001&rsv_n=2");
	size_t pos = strNet.find(':') + 3;
	if (pos != string::npos)
		cout << "is in" << endl;
	else
		cout << "is not in" << endl;

	size_t len = strNet.find('/', pos) - pos;

	ret = strNet.substr(pos, len);
	cout << ret << endl;
	return 0;
}

int main()
{
	string s;

	// �е�ѭ������
	// while(cin>>s)

	while (getline(cin, s))
	{
		cout << s.substr(s.rfind(' ') + 1).size() << endl;
	}
	return 0;
}
#endif

#if 0
int main()
{
	string s1("hello");
	string s2("Hello");

	if (s1 > s2)
		cout << s1 << endl;
	else
		cout << s2 << endl;
	return 0;
}
#endif


#if 0
// ���һ�������漰����Դ�����û�������ʽ�ṩ�������캯���Լ���ֵ���������

// �����ÿ���������Լ���������Դ������������Դ�е�����
// ��ͳ��
class String
{
public:
	// String s("hello");
	String(const char* str = "")
	{
		/*
		if (nullptr == str)
		{
			_str = new char[1];
			*_str = '\0';
		}
		else
		{
			_str = new char[strlen(str) + 1];
			strcpy(_str, str);
		}
		*/

		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		: _str(new char[strlen(s._str)+1])
	{
		strcpy(_str, s._str);
	}

	// C++11
	// �ƶ�����
	// �ƶ���ֵ
	// s3 = s2;
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* str = new char[strlen(s._str) + 1];
			strcpy(str, s._str);
			delete[] _str;
			_str = str;

// 			delete[] _str;
// 			_str = new char[strlen(s._str) + 1];
// 			strcpy(_str, s._str);
		}

		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	String s2(s1);

	// ϵͳ�ṩ��Ĭ�ϵĸ�ֵ��������أ�1. ǳ����   2. ��Դй©
	String s3("world");
	s3 = s2;
}

int main()
{
	TestString();
	return 0;
}
#endif


#if 0
// ���:����--�ִ�д��
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
	}

	String(const String& s)
		: _str(nullptr)
	{
		String strTtemp(s._str);
		swap(_str, strTtemp._str);
	}

	String& operator=(String s)
	{
		swap(_str, s._str);
		return *this;
	}

	~String()
	{
		if (_str)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	String s2(s1);
}

int main()
{
	TestString();
	return 0;
}
#endif

#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
		_count = 1;
	}

	String(String& s)
		: _str(s._str)
		, _count(++s._count)
	{}

	~String()
	{
		if (_str && 0 == --_count)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
	int _count;
};
#endif

#if 0
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
		_count = 1;
	}

	String(String& s)
		: _str(s._str)
	{
		++_count;
	}

	~String()
	{
		if (_str && 0 == --_count)
		{
			delete[] _str;
			_str = nullptr;
		}
	}
private:
	char* _str;
	static int _count;
};

int String::_count = 0;
#endif

#if 0
// ǳ���� + ���ü���
// дʱ������copy on write--cow
class String
{
public:
	String(const char* str = "")
	{
		if (nullptr == str)
			str = "";

		_str = new char[strlen(str) + 1];
		strcpy(_str, str);
		_pCount = new int(1);
	}

	String(const String& s)
		: _str(s._str)
		, _pCount(s._pCount)
	{
		++(*_pCount);
	}

	// s1 = s2;
	// s1�����õ�ǰ��Դ����s2����ͬһ����Դ
	String& operator=(const String& s)
	{
		if (this != &s)
		{
			Release();

			_str = s._str;
			_pCount = s._pCount;
			++*_pCount;
		}

		return *this;
	}

	~String()
	{
		Release();
	}

	// s1��s3�������ͬһ����Դ
	// s1[0] = 'W';
	// s1
	char& operator[](size_t index)
	{
		if (GetRef() > 1)
		{
			String strTemp(_str);
			Swap(strTemp);
		}
		return _str[index];
	}

	const char& operator[](size_t index)const
	{
		return _str[index];
	}

	void Swap(String& s)
	{
		swap(_str, s._str);
		swap(_pCount, s._pCount);
	}
private:
	void Release()
	{
		if (_str && 0 == --*_pCount)
		{
			delete[] _str;
			_str = nullptr;

			delete _pCount;
			_pCount = nullptr;
		}
	}

	int& GetRef()
	{
		return *_pCount;
	}

private:
	char* _str;
	int* _pCount;
};

void TestString()
{
	String s1("hello");
	String s2(s1);
	String s3("world");

	s1 = s3;
	s1[0] = 'W';

	const String s4("hellowrold"); 
	s4[0];
}

// ��--->����ѧ  �������ⲻ�ܻر�---�� ��ʦ
// ���
int main()
{
	TestString();
	return 0;
}
#endif

#if 0
#include <assert.h>

namespace bite
{
	class string
	{
	public:
		typedef char* iterator;

	public:
		string(char* str = "")
		{
			if (nullptr == str)
				str = "";

			_size = strlen(str);
			_str = new char[_size + 1];
			strcpy(_str, str);
			_capacity = _size;
		}

		string(const string& s)
			: _size(s._size)
			, _capacity(s._size)
		{
			_str = new char[_size + 1];
			strcpy(_str, s._str);
		}

		string(size_t n, char ch)
			: _str(new char[n + 1])
			, _size(n)
			, _capacity(n)
		{
			memset(_str, ch, _size);
			_str[_size] = '\0';
		}

		string& operator=(const string& s)
		{
			if (this != &s)
			{
				char* str = new char[s._size + 1];
				strcpy(str, s._str);

				delete[] _str;
				_str = str;
				_size = s._size;
				_capacity = _size;
			}

			return *this;
		}

		~string()
		{
			if (_str)
			{
				delete[] _str;
				_str = nullptr;
			}
		}

		/////////////////////////////////
		// iterator
		iterator begin()
		{
			return _str;
		}

		iterator end()
		{
			return _str + _size;
		}

		/////////////////////////////////
		// capacity
		size_t size()const
		{
			return _size;
		}

		size_t capacity()const
		{
			return _capacity;
		}

		bool empty()const
		{
			return 0 == _size;
		}

		void resize(size_t newSize, char ch = char())
		{
			size_t oldsize = _size;
			if (newSize > oldsize)
			{
				// 20  10  ---��15
				if (newSize > _capacity)
				{
					reserve(_capacity);
				}

				memset(_str + _size, ch, newSize - oldsize);
			}

			_size = newSize;
			_str[_size] = '\0';
		}

		void reserve(size_t newCapacity)
		{
			if (newCapacity > _capacity)
			{
				// �����¿ռ�
				char* str = new char[newCapacity + 1];
			
				// ����Ԫ��
				strcpy(str, _str);

				// �ͷžɿռ�
				delete[] _str;
				_str = str;
				_capacity = newCapacity;
			}
		}

		////////////////////////////////
		// acess
		char& operator[](size_t index)
		{
			assert(index < _size);
			return _str[index];
		}

		const char& operator[](size_t index)const
		{
			assert(index < _size);
			return _str[index];
		}


		//////////////////////////////
		// modify
		string& operator+=(char ch)
		{
			if (_size == _capacity)
				reserve(2 * _capacity);

			_str[_size++] = ch;
			_str[_size] = '\0';

			return *this;
		}

		string& operator+=(char* str)
		{
			size_t len = strlen(str);
			size_t newSize = size() + len;
			if (capacity() < newSize)
			{
				reserve(newSize);
			}

			strcat(_str, str);
			_size = newSize;
			return *this;
		}

		string& operator+=(const string& s)
		{
			*this += s._str;
			return *this;
		}

		void swap(string& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		const char* c_str()const
		{
			return _str;
		}

		size_t find(char ch)
		{
			for (size_t i = 0; i < _size; ++i)
			{
				if (_str[i] == ch)
					return i;
			}

			return npos;
		}

		size_t rfind(char ch)
		{
			for (int i = _size-1; i >= 0; --i)
			{
				if (_str[i] == ch)
					return i;
			}

			return npos;
		}

		string substr(size_t pos = 0, size_t n = npos)
		{
			if (n == npos)
				n = size() - pos;

			string strRet;
			strRet.reserve(n);
			// hello    
			strncpy(strRet._str, _str + pos, n);
			strRet._size = n;
			strRet._str[n] = '\0';

			return strRet;
		}

		friend ostream& operator<<(ostream& _cout, const string& s)
		{
			_cout << s.c_str();
			return _cout;
		}

		bool operator>(const string& s)const;
		bool operator>=(const string& s)const;
		bool operator<(const string& s)const;
		bool operator<=(const string& s)const;
		bool operator==(const string& s)const;
		bool operator!=(const string& s)const;

	private:
		char* _str;
		size_t _capacity;
		size_t _size;

		static size_t npos;
	};

	size_t string::npos = 0;
}

int main()
{
	bite::string s1;
	bite::string s2("hello");
	bite::string s3(10, 'a');
	bite::string s4(s2);

	for (size_t i = 0; i < s2.size(); ++i)
		cout << s2[i];
	cout << endl;

	auto it = s4.begin();
	while (it != s4.end())
	{
		cout << *it;
		++it;
	}
	cout << endl;

	for (auto e : s4)
		cout << e;
	cout << endl;

	return 0;
}
#endif

#if 0
#include <vector>

void TestVector1()
{
	vector<int> v1;
	vector<int> v2(10, 5);

	string s("hello");
	// STL�涨��[begin, end)
	vector<char> v3(s.begin(), s.end());
	vector<int> v4(v2);

	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	vector<int> v5(array, array+sizeof(array)/sizeof(array[0]));

	vector<int> v6{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	for (size_t i = 0; i < v2.size(); ++i)
		cout << v2[i] << " ";
	cout << endl;

	//vector<char>::iterator it = v3.begin();
	auto it = v3.begin();
	while (it != v3.end())
	{
		cout << *it;
		++it;
	}

	for (auto e : v5)
		cout << e << " ";
	cout << endl;
}

// resize/reserve

// resize: �ı���ЧԪ�ظ�����sz�������Ԫ��ʹ��x���
//         sz < ��ЧԪ�ظ����� ��vector����ЧԪ�ؼ��ٵ�sz���ײ�������С����
//  sz > ��ЧԪ�ظ���
//   1. sz < capacity: ����ЧԪ�ظ����ı䵽sz������x���
//   2. sz > capacity: ����---�������

// reserve: ���ݣ�ע�⣺����ı���ЧԪ�ظ���
// 1. newcapacity <= oldcapacity  ֱ�ӷ���
// 2. newcapacity > oldcapacity ���ݣ� �����¿ռ䡢����Ԫ�ء��ͷžɿռ�
void TestVector2()
{
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(20, 8);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(22, 9);
	cout << v.size() << endl;
	cout << v.capacity() << endl;

	v.resize(10);
	cout << v.size() << endl;
	cout << v.capacity() << endl;
}

void TestVector3()
{
	vector<int> v;

	v.reserve(10);
	//v.resize(10);
	//v[0] = 5;
	v.at(0) = 5;
}

int main()
{
	//TestVector1();
	//TestVector2();
	TestVector3();
	return 0;
}
#endif

#if 0
// 1. vs��ʹ��STL�汾��vector���ݷ�ʽ��1.5��  linux:SGI-STL vector: 2��
// 2. �������push_back��vector�в���Ԫ��ʱ�����ͨ��reserve()�������ռ����룬����Ч�ʾͱȽϸ�

#include <vector>
int main()
{
	size_t sz;
	std::vector<int> foo;
	foo.reserve(100);
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i) 
	{
		foo.push_back(i);
		if (sz != foo.capacity()) 
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	return 0;
}
#endif


#include <vector>

#if 0
// ������ʧЧ����������ָ��Ŀռ�Ƿ�---�Ѿ����ͷ���
// vector�е�����ʧЧ������
//    1. ���п��ܻᵼ�µײ�ռ�ı�Ĳ�����push_back/resize/reserve/insert
//    2. erase(it): it������ʧЧ
// �����������ʹ�õ�����ǰ�������������¸�ֵ
int main()
{
	vector<int> v{ 1, 2, 3, 4, 5 };
	auto it = v.begin();

// 	v.push_back(6);
// 	v.push_back(7);
// 	v.push_back(8);
// 	v.push_back(9);

	//v.resize(10);
	//v.reserve(10);

	//it = v.begin();
	while (it != v.end())
	{
		cout << *it<<" ";
		++it;
	}
	cout << endl;
	return 0;
}
#endif

#if 0
int main()
{
	vector<int> v{ 1, 2, 3, 4, 5 };
	auto it = v.begin();
	//v.clear();
	//v.erase(v.begin(), v.end());

	while (it != v.end())
	{
		it = v.erase(it);
		//++it;
	}
	return 0;
}
#endif

#if 0
int main()
{
	vector<int> v1;
	vector<vector<int>> v2;
	v2.resize(5);
	return 0;
}
#endif


namespace bite
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;

	public:
		vector();
		vector(size_t n, const T& data);
		
		template<class Iterator>
		vector(Iterator first, Iterator last);
		vector(const vector<T>& v);

		//////////////////////////////////
		// iterator
		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		////////////////////////////////
		// capacity
		size_t size()const
		{
			return _finish - _start;
		}

		size_t capacity()const
		{
			return _endofstorage - _start;
		}

		bool empty()const
		{
			return _start == _finish;
		}

		void resize(size_t newSize, const T& data = T())
		{
			size_t oldSize = size();
			if (newSize <= oldSize)
				_finish = _start + newSize;
			else
			{
				size_t cap = capacity();
				if (newSize > cap)
					reserve(newSize);

				for (size_t i = oldSize; i < newSize; ++i)
					*_finish++ = data;
			}
		}

		void reserve(size_t newCapacity)
		{
			size_t oldCapacity = capacity();
			if (newCapacity > oldCapacity)
			{
				T* ptemp = new T[newCapacity];

				if (_start)
				{
					size_t n = size();
					for (size_t i = 0; i < n; ++i)
						ptemp[i] = _start[i];

					delete[] _start;
					_start = ptemp;
					_finish = _start + n;
					_endofstorage = _start + newCapacity;
				}
			}
		}

		///////////////////////////////////
		// access
		T& operator[](size_t index)
		{
			assert(index < size());
			return _start[index];
		}

		const T& operator[](size_t index)const
		{
			assert(index < size());
			return _start[index];
		}

		T& front()
		{
			return *_start;
		}

		const T& front()const
		{
			return *_start;
		}

		T& back()
		{
			return *(_finish-1);
		}

		const T& front()const
		{
			return *(_finish - 1);
		}

		///////////////////////////////
		// modify
		void push_back(const T& data)
		{
			if (size() == capacity())
				reserve(2 * capacity());

			*_finish++ = data;
		}

		void pop_back()
		{
			--_finish;
		}

		void insert(iterator pos, const T& data);
		iterator erase(iterator pos);

		void clear()
		{
			_finish = _start;
		}
	private:
		T* _start;
		T* _finish;
		T* _endofstorage;
	};
}
int main()
{
	return 0;
}


