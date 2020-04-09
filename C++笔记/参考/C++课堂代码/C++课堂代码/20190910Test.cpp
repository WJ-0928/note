#include <iostream>
using namespace std;


#if 0
#include <list>

void TestList1()
{
	list<int> L1;
	list<int> L2(10, 5);

	//C++98
	int array[] = { 1, 2, 3 };
	list<int> L3(array, array + sizeof(array) / sizeof(array[0]));

	// C++11
	list<int> L4{1,2,3};

	list<int> L5(L4);

	// C++98
	//list<int>::iterator it = L2.begin();

	// C++11
	auto it = L2.begin();
	while (it != L2.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	auto rit = L3.rbegin();
	while (rit != L3.rend())
	{
		cout << *rit << " ";
		++rit;
	}
	cout << endl;

	// auto e : L4--->��e����ֵ�÷�ʽȥȡL4�е�ÿ��Ԫ��---eʵ����L4��ÿ��Ԫ�ص�����
	// auto& e : L4--->��e����L4�е�ÿ��Ԫ��
	for (auto& e : L4)
		e *= 2;

	for (auto e : L4)
		cout << e << " ";
	cout << endl;
}


void TestList2()
{
	list<int> L{ 1, 2, 3, 4, 5, 6 };
	// O(N)
	auto it = find(L.begin(), L.end(), 5);
	if (it != L.end())
		cout << *it << endl;
	else
		cout << "5 is not in list" << endl;
}

void TestList3()
{
	list<int> L{ 1, 2, 3, 4, 5, 6 };
	auto it = L.begin();
	//L.clear();
	it = L.erase(it);
	cout << *it << endl;
}

void TestList4()
{
	list<int> L{ 1, 2, 3, 4, 5, 6 };
	L.reverse();
	for (auto e : L)
		cout << e << " ";
	cout << endl;
}

void TestList5()
{
	list<int> L1{1, 5,2,1};
	L1.unique();

	L1.sort();
	L1.unique();

	list<int> L2{ 9, 1, 0 };
	L2.sort();

	L1.merge(L2);
	for (auto e : L1)
		cout << e << " ";
	cout << endl;

	
}

int main()
{
	//TestList1();
	//TestList3();
	//TestList4();
	TestList5();
	return 0;
}
#endif

#if 0
namespace bite
{
	template<class T>
	struct list_node
	{
		list_node(const T& data = T())
		: prev(nullptr)
		, next(nullptr)
		, _data(data)
		{}

		list_node<T>* prev;
		list_node<T>* next;
		T _data;
	};

	template<class T>
	class list_iterator
	{
		typedef list_node<T> node;
		typedef list_iterator<T> self;
	public:
		list_iterator(node* pNode = nullptr)
			: _pNode(pNode)
		{}

		// �õ���������ָ�����Ʋ���
		T& operator*()
		{
			return _pNode->_data;
		}

		T* operator->()
		{
			return &operator*();
		}

		// �õ����������ƶ�
		self& operator++()
		{
			_pNode = _pNode->next;
			return *this;
		}

		self operator++(int)
		{
			self temp(*this);
			_pNode = _pNode->next;
			return temp;
		}

		self& operator--()
		{
			_pNode = _pNode->prev;
			return *this;
		}

		self operator--(int)
		{
			self temp(*this);
			_pNode = _pNode->prev;
			return temp;
		}

		// ���������бȽϲ���
		bool operator!=(const self& s)const
		{
			return _pNode != s._pNode;
		}

		bool operator==(const self& s)const
		{
			return _pNode == s._pNode;
		}
	
		node* _pNode;
	};


	template<class T>
	class list
	{
		typedef list_node<T> node;
	public:
		typedef list_iterator<T> iterator;

	public:
		list()
		{
			creathead();
		}

		list(int n, const T& data)
		{
			creathead();
			for (int i = 0; i < n; ++i)
				push_back(data);
		}
		
		template<class Iterator>
		list(Iterator first, Iterator last)
		{
			creathead();
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		list(const list<T>& L)
		{
			creathead();

			node* pCur = L._pHead->next;
			while (pCur != L._pHead)
			{
				push_back(pCur->_data);
				pCur = pCur->next;
			}
		}

		/////////////////////////////////////
		// iterator
		iterator begin()
		{
			return iterator(_pHead->next);
		}

		iterator end()
		{
			return iterator(_pHead);
		}

		////////////////////////////////////
		// capacity
		size_t size()const
		{
			size_t count = 0;
			node* pCur = _pHead->next;
			while (pCur != _pHead)
			{
				count++;
				pCur = pCur->next;
			}

			return count;
		}

		bool empty()const
		{
			return _pHead->next == _pHead;
		}

		void resize(size_t newsize, const T& data = T())
		{
			size_t oldsize = size();
			if (newsize > oldsize)
			{
				for (size_t i = oldsize; i < newsize; ++i)
					push_back(data);
			}
			else
			{
				for (size_t i = newsize; i < oldsize; ++i)
					pop_back();
			}
		}

		//////////////////////////////////////
		// access
		T& front()
		{
			return _pHead->next->_data;
		}

		const T& front()const
		{
			return _pHead->next->_data;
		}

		T& back()
		{
			return _pHead->prev->_data;
		}

		const T& back()const
		{
			return _pHead->prev->_data;
		}

		///////////////////////////////////////
		// modify
		void push_back(const T& data)
		{
			insert(end(), data);
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& data)
		{
			insert(begin(), data);
		}

		void pop_front()
		{
			erase(begin());
		}

		iterator insert(iterator pos, const T& data)
		{
			node* pCur = pos._pNode;
			node* pNewNode = new node(data);

			pNewNode->next = pCur;
			pNewNode->prev = pCur->prev;
			
			pCur->prev = pNewNode;
			pNewNode->prev->next = pNewNode;
			
			return iterator(pNewNode);
		}

		iterator erase(iterator pos)
		{
			if (pos == end())
				return;

			node* pDelNode = pos._pNode;
			node* pRetNode = pDelNode->next;

			pDelNode->prev->next = pDelNode->next;
			pDelNode->next->prev = pDelNode->prev;
			delete pDelNode;

			return iterator(pRetNode);
		}

		void clear()
		{
			node* pCur = _pHead->next;
			while (pCur != _pHead)
			{
				_pHead->next = pCur->next;
				delete pCur;
				pCur = _pHead->next;
			}

			_pHead->next = _pHead;
			_pHead->prev = _pHead;
		}

		void swap(const list<T>& l)
		{
			swap(_pHead, l._pHead);
		}

	private:
		void creathead()
		{
			_pHead = new node;
			_pHead->next = _pHead;
			_pHead->prev = _pHead;
		}
	private:
		node* _pHead;
	};
}

#include <vector>

void TestList1()
{
	bite::list<int> L1;
	bite::list<int> L2(10, 5);

	vector<int> v{ 1, 2, 3, 4 };
	bite::list<int> L3(v.begin(), v.end());

	bite::list<int> L4(L3);

	auto it = L2.begin();
	while (it != L2.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : L3)
		cout << e << " ";
	cout << endl;
}

int main()
{
	TestList1();
	return 0;
}
#endif

#if 0
// stack���ǽ�˫�˶������·�װ
// ����������һ�����ݽṹ���з�װ���γ�һ���µĽṹ
// ����������
#include <deque>
namespace bite
{
	template<class T, class Container = deque<T>>
	class stack
	{
	public:
		stack()
			: _con()
		{}

		void push(const T& data)
		{
			_con.push_back(data);
		}

		void pop()
		{
			_con.pop_back();
		}

		T& top()
		{
			return _con.back();
		}

		const T& top()const
		{
			return _con.back();
		}

		size_t size()const
		{
			return _con.size();
		}

		bool empty()const
		{
			return _con.empty();
		}
	private:
		Container _con;
	};
}

#include <vector>

int main()
{
	bite::stack<int> s1;
	bite::stack<int, vector<int>> s2;
	s2.push(1);
	s2.push(2);
	s2.push(3);
	s2.push(4);
	cout << s2.size() << endl;
	cout << s2.top() << endl;

	s2.pop();
	s2.pop();
	cout << s2.size() << endl;
	cout << s2.top() << endl;

	return 0;
}
#endif

#if 0
#include <deque>

namespace bite
{
	template<class T, class Container=deque<T>>
	class queue
	{
	public:
		queue()
			: c()
		{}

		void push(const T& data)
		{
			c.push_back(data);
		}

		void pop()
		{
			c.pop_front();
		}

		T& front()
		{
			return c.front();
		}

		const T& front()const
		{
			return c.front();
		}

		T& back()
		{
			return c.back();
		}

		const T& back()const
		{
			return c.back();
		}

		size_t size()const
		{
			return c.size();
		}

		bool empty()const
		{
			return c.empty();
		}
	private:
		Container c;
	};
}


#include <list>

int main()
{
	bite::queue<int> q1;
	bite::queue<int, list<int>> q2;

	q2.push(1);
	q2.push(2);
	q2.push(3);
	q2.push(4);
	cout << q2.size() << endl;
	cout << q2.front() << endl;
	cout << q2.back() << endl;

	q2.pop();
	q2.pop();
	cout << q2.size() << endl;
	cout << q2.front() << endl;
	cout << q2.back() << endl;
	return 0;
}
#endif


#if 0
// Ĭ�ϰ���С��less��ʽ�Ƚ�--->���
// С�ѣ��û������ṩ�ȽϷ�ʽ--->����--->greater
//      ע�⣺�����Ҫ�ṩ�ȽϹ���ģ������б�ĵڶ�������������ʽ�ṩ
#include <queue>
#include <functional>

int main()
{
	priority_queue<int, vector<int>, greater<int>> q;
	q.push(3);
	q.push(1);
	q.push(9);
	q.push(0);
	q.push(5);
	q.push(7);

	cout << q.top() << endl;

	return 0;
}
#endif

#if 0
// �����Զ������ͣ��������С��--->�������� >
//              ����������--->�������� <
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	bool operator<(const Date& d)const
	{
		if (_year < d._year ||
			_year == d._year && _month < d._month ||
			_year == d._year && _month == d._month && _day < d._day)
		{
			return true;
		}

		return false;
	}


private:
	int _year;
	int _month;
	int _day;
};


#include <queue>
#include <functional>

int main()
{
	Date d1(2019, 9, 15);
	Date d2(2019, 9, 16);
	Date d3(2019, 9, 14);

	priority_queue<Date> q;
	q.push(d1);
	q.push(d2);
	q.push(d3);
	return 0;
}
#endif


#if 0
class Date
{
	friend bool Less(Date* pLeft, Date* pRight);
public:
	
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};


#include <queue>
#include <functional>

// �ú���ָ���ṩ�ȽϵĹ���
bool Less(Date* pLeft, Date* pRight)
{
	if (pLeft->_day < pRight->_day)
		return true;

	return false;
}

typedef bool (*Compare)(Date* pLeft, Date* pRight);

int main()
{
	Date d1(2019, 9, 15);
	Date d2(2019, 9, 16);
	Date d3(2019, 9, 14);

	priority_queue<Date*, vector<Date*>, Compare> q(Less);
	q.push(&d1);
	q.push(&d2);
	q.push(&d3);
	return 0;
}
#endif

#if 0
class Date
{
	friend class Less;
public:

	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};


#include <queue>
#include <functional>

class Less
{
public:
	bool operator()(const Date* pLeft, const Date* pRight)
	{
		return pLeft->_day < pRight->_day;
	}
};


int main()
{
	Date d1(2019, 9, 15);
	Date d2(2019, 9, 16);
	Date d3(2019, 9, 14);

	Less min;
	min(&d1, &d2);  // �º��� || ��������---��������һ���Ķ���
	//min.operator()(&d1, &d2);

	priority_queue<Date*, vector<Date*>, Less> q;
	q.push(&d1);
	q.push(&d2);
	q.push(&d3);
	return 0;
}
#endif

#if 0
#include <vector>

namespace bite
{
	template<class T, class Container = vector<T>, class Compare = less<T>>
	class priority_queue
	{
	public:
		priority_queue()
		{}

		template<class Iterator>
		priority_queue(Iterator first, Iterator last)
			: c(first, last)
		{
			int root = ((c.size() - 2) >> 1);
			for (; root >= 0; --root)
				_AdjustDown(root);
		}

		void push(const T& data)
		{
			c.push_back(data);
			_AdjustUP(c.size()-1);
		}

		void pop()
		{
			if (empty())
				return;

			// ���Ѷ�Ԫ����������һ��Ԫ�ؽ��н���
			swap(c.front(), c.back());
			c.pop_back();
			_AdjustDown(0);
		}

		size_t size()const
		{
			return c.size();
		}

		bool empty()const
		{
			return c.empty();
		}

		const T& top()const
		{
			return c.front();
		}
	private:
		// parent�����������Ѿ�����ѵ�����
		void _AdjustDown(int parent)
		{
			size_t child = parent * 2 + 1;
			while (child < c.size())
			{
				// �����������нϴ�ĺ���
				Compare com;
				if (child + 1 < c.size() && com(c[child], c[child+1]))
					child += 1;

				// ���parent�Ƿ�����ѵ�����
				if (com(c[parent], c[child]))
				{
					swap(c[parent], c[child]);
					parent = child;
					child = parent * 2 + 1;
				}
				else
					return;
			}
		}

		void _AdjustUP(int child)
		{
			int parent = ((child - 1) >> 1);
			while (child)
			{
				Compare com;
				if (com(c[parent], c[child]))
				{
					swap(c[parent], c[child]);
					child = parent;
					parent = ((child - 1) >> 1);
				}
				else
					return;
			}
		}
	private:
		Container c;
	};
}

class Date
{
	friend class Less;
public:

	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

private:
	int _year;
	int _month;
	int _day;
};

class Less
{
public:
	bool operator()(const Date* pLeft, const Date* pRight)
	{
		return pLeft->_day < pRight->_day;
	}
};

#include <functional>

int main()
{
	int array[] = {4,2,8,9,3,7,0,6,5,1};
	bite::priority_queue<int> q1;
	for (auto e : array)
		q1.push(e);

	bite::priority_queue<int, vector<int>, greater<int>> q2(array, array + sizeof(array) / sizeof(array[0]));


	Date d1(2019, 9, 15);
	Date d2(2019, 9, 16);
	Date d3(2019, 9, 14);
	bite::priority_queue<Date*,vector<Date*>,Less> q3;
	q3.push(&d1);
	q3.push(&d2);
	q3.push(&d3);
	return 0;
}
#endif

#if 0
#include <assert.h>

namespace bite
{
	template<class T, size_t N>
	class array
	{
	public:
		T& operator[](size_t index)
		{
			//N = 100;
			assert(index < N);
			return _arr[index];
		}

	private:
		T _arr[N];
		size_t _size;
	};
}


int main()
{
	int N1 = 10;
	int N2 = 20;

	// ����ʧ�ܣ�N1+N2���ʽ�Ľ���ڱ����ڼ��޷�ȷ������
	// ֻ�еȵ����������ڼ����ȷ�ϣ��൱���ڱ����ڼ��array��ʵ����ʧ��
	//bite::array<int, N1+N2> a;
	bite::array<int, 10 + 20> a;
	a[0] = 10;
	return 0;
}
#endif

#if 0
// Max�������ڶ������Ϳ���û�����⣬���Ƕ��ڸ������ʹ���ʱ���ܻ�õ�
// ����������Max����ģ����������ͽ������⴦��
template<class T>
T& Max(T& left, T& right)
{
	if (left > right)
		return left;

	return right;
}


// Max����ģ�����char*���ʹ�������
// Max����ģ���char*�������⻯����---�ػ�

// �ػ���ǰ�᣺��������һ������ģ��--->���������������Ҫ�ػ�
template<>
char*& Max<char*>(char*& left, char*& right)
{
	if (strcmp(left, right) > 0)
		return left;

	return right;
}


int main()
{
	int a = 10;
	int b = 20;

	cout << Max(a, b) << endl;
	cout << Max(b, a) << endl;

	char* p2 = "world";
	char* p1 = "hello";
	
	cout << Max(p1, p2) << endl;
	cout << Max(p2, p1) << endl;
	return 0;
}
#endif

#if 0
template<class T>
T& Max(T& left, T& right)
{
	if (left > right)
		return left;

	return right;
}


// һ���������ģ�岻��Ҫ�ػ���ֱ��д�������Ͷ�Ӧ�ĺ���
char* Max(char* left, char* right)
{
	if (strcmp(left, right) > 0)
		return left;

	return right;
}


int main()
{
	int a = 10;
	int b = 20;

	cout << Max(a, b) << endl;
	cout << Max(b, a) << endl;

	char* p2 = "world";
	char* p1 = "hello";

	cout << Max(p1, p2) << endl;
	cout << Max(p2, p1) << endl;
	return 0;
}
#endif

#if 0
template<class T>
const T& Max(const T& left, const T& right)
{
	if (left > right)
		return left;

	return right;
}



// Max����ģ�����char*���ʹ�������
// Max����ģ���char*�������⻯����---�ػ�

// �ػ���ǰ�᣺��������һ������ģ��--->���������������Ҫ�ػ�
template<>
const char*& Max<const char*>(const char*& left, const char*& right)
{
	if (strcmp(left, right) > 0)
		return left;

	return right;
}


int main()
{
	int a = 10;
	int b = 20;

	cout << Max(a, b) << endl;
	cout << Max(b, a) << endl;

	const char* p2 = "world";
	const char* p1 = "hello";
	//p1[0] = 'H';

	cout << Max(p1, p2) << endl;
	cout << Max(p2, p1) << endl;
	return 0;
}
#endif

#if 0
// ��ģ����ػ���ȫ�ػ� �� ƫ�ػ�
// ȫ�ػ�: ��ģ������б������е�����ȫ���ػ�
template<class T1, class T2>
class Data
{
public:
	Data() 
	{ 
		cout << "Data<T1, T2>" << endl; 
	}

private:
	T1 _d1;
	T2 _d2;
};

// �����Data��ģ�尴��int��double�ķ�ʽ������ʵ����
// �������ͻ�ʹ���ػ��İ汾��������ʹ����ģ��
template<>
class Data<int, double>
{
public:
	Data()
	{
		cout << "Date(int, double)" << endl;
	}
private:
	int _d1;
	double _d2;
};

int main()
{
	Data<int, int> d1;
	Data<int, double> d2;
	return 0;
}
#endif

#if 0
// ƫ�ػ���1. �����ػ�  2. �����͸���ϸ�Ķ���
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}

private:
	T1 _d1;
	T2 _d2;
};

// ���Data��ģ����ʵ�����ڼ䣬ֻҪ�ڶ�����������int��ʽ����ʵ�������ͻ�ִ���ػ��İ汾
template<class T1>
class Data<T1, int>
{
public:
	Data()
	{
		cout << "Data<T1, int>" << endl;
	}

private:
	T1 _d1;
	int _d2;
};


int main()
{
	Data<double, int> d1;
	Data<char, int> d2;
	Data<int, short> d3;
	return 0;
}
#endif

#if 0
template<class T1, class T2>
class Data
{
public:
	Data()
	{
		cout << "Data<T1, T2>" << endl;
	}

private:
	T1 _d1;
	T2 _d2;
};


// ƫ�ػ�����һ�ַ�ʽ�� �����Ͳ������Ƹ����ϸ�
template<class T1, class T2>
class Data<T1*, T2*>
{
public:
	Data()
	{
		cout << "Data<T1*, T2*>" << endl;
	}

private:
	T1* _d1;
	T2* _d2;
};


int main()
{
	Data<int*, char*> d1;
	Data<char*, short*> d2;

	Data<int, char*> d3;
	return 0;
}
#endif

// ���캯�� �������캯��  ��ֵ���������  ��������
// ʲô��ǳ����   �����ʽ:���
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
		: _str(new char[strlen(s._str) + 1])
	{
		strcpy(_str, s._str);
	}

	String& operator=(const String& s)
	{
		if (this != &s)
		{
			char* pStr = new char[strlen(s._str) + 1];
			strcpy(pStr, s._str);
			delete[] _str;
			_str = pStr;
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

#if 0
// дһ��ͨ�����͵Ŀ�������--->Ч�ʾ����ܸ�
template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	// �ŵ㣺һ���������
	// ȱ�ݣ�Ч�ʵ�--->O(N)
	//for (size_t i = 0; i < size; ++i)
	//	dst[i] = src[i];

	// �ŵ㣺Ч�ʸ�--->O(1)
	// ȱ�ݣ�ǳ����
	memcpy(dst, src, size*sizeof(T));
}
#endif

#if 0
// plain old data
bool IsPODType(const char* strType)
{
	const char* strTypes[] = {"char", "short", "int", "long", "double"};
	for (auto e : strTypes)
	{
		if (strcmp(e, strType) == 0)
			return true;
	}

	return false;
}
#endif

#if 0
// ������ȡ---->��ģ���ػ���Ӧ��
// ��������
struct TrueType
{
	static bool Get()
	{
		return true;
	}
};

// �Զ�������
struct FalseType
{
	static bool Get()
	{
		return false;
	}
};

// T--> ��������  �Զ�������
template<class T>
struct TypeTraits
{
	typedef FalseType PODType;
};

// �����е������������ػ�TypeTraitsģ��
template<>
struct TypeTraits<char>
{
	typedef TrueType PODType;
};

template<>
struct TypeTraits<short>
{
	typedef TrueType PODType;
};

template<>
struct TypeTraits<int>
{
	typedef TrueType PODType;
};

// ...

template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	if (TypeTraits<T>::PODType::Get())
	{
		// ��������
		memcpy(dst, src, size*sizeof(T));
	}
	else
	{
		// �Զ�������---���ܻ��漰����ǳ����
		for (size_t i = 0; i < size; ++i)
			dst[i] = src[i];
	}	
}

#endif

#if 0
// ������ȡ---->��ģ���ػ���Ӧ��
// ��������
struct TrueType
{};

// �Զ�������
struct FalseType
{};

// T--> ��������  �Զ�������
template<class T>
struct TypeTraits
{
	typedef FalseType PODType;
};

// �����е������������ػ�TypeTraitsģ��
template<>
struct TypeTraits<char>
{
	typedef TrueType PODType;
};

template<>
struct TypeTraits<short>
{
	typedef TrueType PODType;
};

template<>
struct TypeTraits<int>
{
	typedef TrueType PODType;
};

// ...

template<class T>
void _Copy(T* dst, const T* src, size_t size, TrueType)
{
	// ��������
	memcpy(dst, src, size*sizeof(T));
}

template<class T>
void _Copy(T* dst, const T* src, size_t size, FalseType)
{
	// �Զ�������---���ܻ��漰����ǳ����
	for (size_t i = 0; i < size; ++i)
		dst[i] = src[i];
}

template<class T>
void Copy(T* dst, const T* src, size_t size)
{
	_Copy(dst, src, size, TypeTraits<T>::PODType());
}



void TestCopy()
{
	int array1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };
	int array2[10];
	Copy(array2, array1, 10);


	String s1[3] = { "1111", "2222", "3333" };
	String s2[3];
	Copy(s2, s1, 3);
}

int main()
{
	TestCopy();
	return 0;
}
#endif

#include "a.h"

#include "a.hpp"

/*
int Add(int left, int right);


template<class T>
T Sub(const T& left, const T& right);

*/

#if 0
int main()
{
	Add(10, 20);
	Sub(10, 20);

	Sub(10.0, 20.0);
	Sub('a', 'b');
	return 0;
}
#endif

#if 0
int main()
{
	int a = 0;
	double d = 0.0;
	scanf("%d %lf",&d);
	scanf("%d %lf", a, &d);

	printf("%d, %lf", 10, 12.34);
	printf("%d, %lf", 10);

	return 0;
}
#endif


#if 0
int main()
{
	cout << "error";
	cerr << "error";

	cerr << "error" << endl;
	clog << "log" << endl;

	int a;
	double d;
	cin >> a;
	cout << a << endl;
	cin >> a >> d;

	cout << 10 << endl;
	cout << 10 << " " << 12.34 << endl;
	return 0;
}
#endif

#if 0
int main()
{
	//EOF;
	int a, b, c;
	//c = scanf("%d %d", &a, &b);
	//cin >> a >> b >> c;
	char ch;
	cin >> ch;
	//ch = getchar();
	cin >> a;
	cin >> b;
	cin >> c;
	cout << a << " " << b << " " << c << endl;
	return 0;
}
#endif

#include <fstream>


// ʹ���ļ�IO�����ı��������Ʒ�ʽ��ʾ��д�����ļ�
struct ServerInfo
{
	char _ip[32]; // ip
	int _port; // �˿�
};


struct ConfigManager
{
public:
	ConfigManager(const char* configfile = "bitserver.config")
		:_configfile(configfile)
	{}

	void WriteBin(const ServerInfo& info)
	{
		// ����ע��ʹ�ö����Ʒ�ʽ��д
		ofstream ofs(_configfile, ifstream::out | ifstream::binary);
		ofs.write((const char*)&info, sizeof(ServerInfo));
		ofs.close();
	}

	void ReadBin(ServerInfo& info)
	{
		// ����ע��ʹ�ö����Ʒ�ʽ�򿪶�
		ifstream ifs(_configfile, ifstream::in | ifstream::binary);
		ifs.read((char*)&info, sizeof(ServerInfo));
		ifs.close();
	}

	void WriteText(const ServerInfo& info)
	{
		// ����ᷢ��IO��д���α�C�������׾ͼ򵥶��ˣ�
		// C ���Ե��Ȱ�����itoa��д
		ofstream ofs(_configfile);
		ofs << info._ip << endl;
		ofs << info._port << endl;
		ofs.close();
	}
	void ReadText(ServerInfo& info)
	{
		// ����ᷢ��IO�������α�C�������׾ͼ򵥶��ˣ�
		// C ���Ե��ȶ��ַ�������atoi
		ifstream ifs(_configfile);
		ifs >> info._ip;
		ifs >> info._port;
		ifs.close();
	}
private:
	string _configfile; // �����ļ�
};

int main()
{
	ConfigManager cfgMgr;
	ServerInfo wtinfo;
	ServerInfo rdinfo;
	strcpy(wtinfo._ip, "127.0.0.1");
	wtinfo._port = 80;
	// �����ƶ�д
	cfgMgr.WriteBin(wtinfo);
	cfgMgr.ReadBin(rdinfo);
	cout << rdinfo._ip << endl;
	cout << rdinfo._port << endl;

	// �ı���д
	cfgMgr.WriteText(wtinfo);
	cfgMgr.ReadText(rdinfo);
	cout << rdinfo._ip << endl;
	cout << rdinfo._port << endl;
	return 0;
}

