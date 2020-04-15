#include <iostream>
using namespace std;

#if 0
void Test1()
{
	//...
	throw 1;
}

bool Test2()
{
	////成功--->true

	/// 失败----false
	return false;
}

// 缺陷：在TestFunc1所有中途可能会退出的位置，必须释放空间以及关闭文件指针
// 
void TestFunc1()
{
	int* p = new int[10];
	FILE* pf = fopen("4444.txt", "rb");
	if (pf == nullptr)
	{
		delete[] p;
		return; 
	}

	try
	{
		Test1();
	}
	catch (...)
	{
		delete[] p;
		fclose(pf);
		throw;
	}

	// 如果Test2失败(返回false)--->TestFunc1终止
	if (!Test2())
	{
		delete[] p;
		fclose(pf);
		return;
	}
	

	//....
	fclose(pf);
	delete[] p;
}

int main()
{
	return 0;
}
#endif


// 什么是内存泄漏？
// 内存泄漏的危害
// 内存泄漏的检测
// C++中如何预防内存泄漏---智能指针

#if 0
class  A
{
public:
	A(int n)
		: _ptr(new int[n])
	{}

	~A()
	{
		if (_ptr)
		{
			delete[] _ptr;
		}
	}
protected:
	int* _ptr;
};


void TestFunc()
{
	int* p = new int;

	A a(1);
}


int main()
{
	TestFunc();
	return 0;
}
#endif

#if 0
// 让一个类管理原生态指针
// RAII
// 优势：用户不需要关心资源何时去释放
// 缺陷：浅拷贝----不能采用深拷贝的方式解决

// String: 资源是类自己申请的

// SmartPtr可以管理资源，资源由用户申请
template<class T>
class SmartPtr
{
public:
	SmartPtr(T* ptr)
		: _ptr(ptr)
	{
		cout << "SmartPtr()" << endl;
	}

	~SmartPtr()
	{
		cout << "~SmartPtr()" << endl;
		if (_ptr)
		{
			delete _ptr;
		}
	}

	// 让该类的对象具有指针类似的行为
	T& operator*()
	{
		return *_ptr;
	}

	T* operator->()
	{
		return _ptr;
	}
protected:
	T* _ptr;
};

struct A
{
	int a;
	int b;
	int c;
};

void TestFunc1()
{
	//int* p = new int;
	//SmartPtr<int> sp(p);

	SmartPtr<int> sp1(new int);
	*sp1 = 100;
	// 解引用
	// ->
	SmartPtr<A> sp2(new A);
	sp2->a = 10;
	sp2->b = 20;
	sp2->c = 30;
}

void TestFunc2()
{
	SmartPtr<int> sp1(new int);
	SmartPtr<int> sp2(sp1);
}

int main()
{
	//TestFunc1();
	TestFunc2();
	return 0;
}
#endif

#if 0
// 智能指针---SmartPtr中遇到的浅拷贝问题
// 智能指针原理：RAII + 类对象具有类似指针的行为(operator*()/operator->()) + 解决浅拷贝
// C++98版本--auto_ptr: 解决浅拷贝方式--->资源的转移
namespace bite
{
	template<class T>
	class auto_ptr
	{
	public:
		// RAII
		auto_ptr(T* ptr)
			: _ptr(ptr)
		{}

		// ap2(ap1);
		auto_ptr(auto_ptr<T>& ap)
			: _ptr(ap._ptr)
		{
			ap._ptr = nullptr;
		}

		// ap1 = ap2
		auto_ptr<T>& operator=(auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				if (_ptr)
					delete _ptr;

				_ptr = ap._ptr;
				ap._ptr = nullptr;
			}

			return *this;
		}

		~auto_ptr()
		{
			if (_ptr)
			{
				delete _ptr;
			}
		}

		// 让类对象具有指针类似的行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	protected:
		T* _ptr;
	};
}

void TestFunc()
{
	// 常规指针
	int a = 10;
	int* p1 = &a;
	int* p2(p1);

	*p1 = 100;
	*p2 = 200;

	bite::auto_ptr<int> ap1(new int);
	
	// 解决方式：将资源转移
	bite::auto_ptr<int> ap2(ap1);
	*ap1 = 10;   // 会崩溃---ap1已经将资源转移给ap2，自己与资源断开联系
	*ap2 = 20;

	bite::auto_ptr<int> ap3(new int);
	//ap1 = ap2;
	ap3 = ap2;
}


int main()
{
	TestFunc();
	return 0;
}
#endif

#if 0
// 改进：auto_ptr
// 原理：RAII + 具有指针类似行为 + 解决浅拷贝：资环管理权的转移(对资源释放的权利)
namespace bite
{
	template<class T>
	class auto_ptr
	{
	public:
		auto_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _owner(false)
		{
			if (_ptr)
				_owner = true;
		}

		auto_ptr(const auto_ptr<T>& ap)
			: _ptr(ap._ptr)
			, _owner(ap._owner)
		{
			ap._owner = false;
		}

		auto_ptr<T>& operator=(const auto_ptr<T>& ap)
		{
			if (this != &ap)
			{
				// 先处理以前旧资源
				if (_ptr && _owner)
					delete _ptr;

				_ptr = ap._ptr;
				_owner = ap._owner;
				ap._owner = false;
			}

			return *this;
		}

		~auto_ptr()
		{
			if (_ptr && _owner)
			{
				delete _ptr;
			}
		}

		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	protected:
		T* _ptr;
		mutable bool _owner; // 资源真正的拥有者(对资源具有释放权利的对象)
	};
}

void TestFunc()
{
	bite::auto_ptr<int> ap1(new int);
	bite::auto_ptr<int> ap2(ap1);
	bite::auto_ptr<int> ap3;
	ap3 = ap2;

	*ap1 = 10;
	*ap2 = 20;
	*ap3 = 30;
}

int main()
{
	TestFunc();
	return 0;
}

// 建议：什么情况下都不要使用auto_ptr
#endif

#if 0
// C++爱好者
// 在C++11中，更新了几个智能指针的版本
// 智能指针原理：ARII + 具有指针类似行为 + 解决浅拷贝
// unique_ptr: 资源独占的方式(一份资源只能被一个对象管理)
// 方式：禁止拷贝构造和赋值运算符重载调用---防拷贝
namespace bite
{
	template<class T>
	class unique_ptr
	{
		// RAII
	public:
		unique_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{}

		~unique_ptr()
		{
			if (_ptr)
				delete _ptr;
		}

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		// 防止被拷贝--禁止调用拷贝构造&赋值运算符重载
#if 0
		// C++98:只声明不定义 & private
	private:
		unique_ptr(const unique_ptr<T>& up);
		unique_ptr<T>& operator=(const unique_ptr<T>& up);
#endif

		unique_ptr(const unique_ptr<T>& up) = delete;
		unique_ptr<T>& operator=(const unique_ptr<T>& up)=delete;
	protected:
		T* _ptr;
	};
}

// 缺陷：多个unique_ptr的对象之间不能共享资源
void TestFunc()
{
	bite::unique_ptr<int> up1(new int);
	//bite::unique_ptr<int> up2(up1);
	bite::unique_ptr<int> up2;
	//up2 = up1;
}

int main()
{
	return 0;
}
#endif

// shared_ptr: RAII + 指针类似的行为 + 引用计数
#if 0
// 整形计数：不可行
namespace bite
{
	template<class T>
	class shared_ptr
	{
	public:
		// RAII
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _count(0)
		{
			if (_ptr)
				_count = 1;
		}

		shared_ptr(shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _count(++sp._count)
		{}

		~shared_ptr()
		{
			if (_ptr && 0 == --_count)
			{
				delete _ptr;
			}
		}

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	protected:
		T* _ptr;
		int _count;
	};
}
#endif

#if 0
// 引用计数：静态的成员变量
namespace bite
{
	template<class T>
	class shared_ptr
	{
	public:
		// RAII
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
		{
			if (_ptr)
				_count = 1;
		}

		shared_ptr(shared_ptr<T>& sp)
			: _ptr(sp._ptr)
		{
			_count++;
		}

		~shared_ptr()
		{
			if (_ptr && 0 == --_count)
			{
				delete _ptr;
			}
		}

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}
	protected:
		T* _ptr;
		static int _count;
	};

	template<class T>
	int shared_ptr<T>::_count = 0;
}
#endif

#if 0
// 缺陷
namespace bite
{
	template<class T>
	class shared_ptr
	{
	public:
		// RAII
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
		{
			if (_ptr)
				_pCount = new int(1);
		}

		// shared_ptr<int> sp2(sp1);
		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
		{
			if (_pCount)
				++*_pCount;
		}

		// sp1  sp2(sp1);
		// sp3  sp4(sp3);
		// sp3 = sp1;
		// sp4 = sp1;
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 让当前对象与资源断开
				Release();

				// 与sp共享
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_pCount)
					++*(_pCount);
			}

			return *this;
		}

		~shared_ptr()
		{
			Release();
		}

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		void Release()
		{
			if (_ptr && 0 == --*_pCount)
			{
				delete _ptr;
				delete _pCount;
			}
		}
	protected:
		T* _ptr;
		int* _pCount;
	};
}

void TestSharedPtr()
{
	bite::shared_ptr<int> sp1(new int);
	bite::shared_ptr<int> sp2(sp1);
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	bite::shared_ptr<int> sp3(new int);
	bite::shared_ptr<int> sp4(sp3);
	cout << sp3.use_count() << endl;
	cout << sp4.use_count() << endl;

	sp3 = sp1;
	cout << sp1.use_count() << endl;

	sp4 = sp1;
	cout << sp1.use_count() << endl;
}

int main()
{
	TestSharedPtr();
	return 0;
}
#endif

#if 0
#include <mutex>

// 1. 不是线程安全
// 2. 只能管理new的资源
namespace bite
{
	template<class T>
	class shared_ptr
	{
	public:
		// RAII
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
			, _pMutex(nullptr)
		{
			if (_ptr)
			{
				_pMutex = new mutex;
				_pCount = new int(1);
			}
		}

		// shared_ptr<int> sp2(sp1);
		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
			, _pMutex(sp._pMutex)
		{
			if (_pCount)
				AddRef();
		}

		// sp1  sp2(sp1);
		// sp3  sp4(sp3);
		// sp3 = sp1;
		// sp4 = sp1;
		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 让当前对象与资源断开
				Release();

				// 与sp共享
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_pCount)
					AddRef();
			}

			return *this;
		}

		~shared_ptr()
		{
			Release();
		}

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		void AddRef()
		{
			_pMutex->lock();
			++(*_pCount);
			_pMutex->unlock();
		}

		int SubRef()
		{
			_pMutex->lock();
			--(*_pCount);
			_pMutex->unlock();

			return *_pCount;
		}

		void Release()
		{
			if (_ptr && 0 == SubRef())
			{
				delete _ptr;
				delete _pCount;
			}
		}
	protected:
		T* _ptr;
		int* _pCount;
		mutex* _pMutex;  // 保证计数的安全性
	};
}

// mutex: 可以保证计数的安全性 || 可以保证shared_ptr类本身的安全性
//        但不能保证shared_ptr管理资源中内容的安全性
struct A
{
	A()
	: a(0)
	, b(0)
	, c(0)
	{}

	int a;
	int b;
	int c;
};


void TestThread(bite::shared_ptr<A>& sp, int N)
{
	for (size_t i = 0; i < N; ++i)
	{
		sp->a++;
		sp->b++;
		sp->c++;
	}
}



#include <thread>
int main()
{
	bite::shared_ptr<A> sp(new A);
	thread t1(TestThread, sp, 100000);
	thread t2(TestThread, sp, 100000);

	t1.join();
	t2.join();
	return 0;
}
#endif


#if 0
// 《Effective C++》
// C++: 一定要多总结
// 仿函数(函数对象)

// 定制删除器
template<class T>
class DelRef
{
public:
	void operator()(T*& ptr)
	{
		if (ptr)
		{
			delete ptr;
			ptr = nullptr;
		}
	}
};

template<class T>
class Free
{
public:
	void operator()(T*& ptr)
	{
		if (ptr)
		{
			free(ptr);
			ptr = nullptr;
		}
	}
};

class FClose
{
public:
	void operator()(FILE*& pf)
	{
		if (pf)
		{
			fclose(pf);
			pf = nullptr;
		}
	}
};

#include <mutex>

// 只能管理new的资源
namespace bite
{
	template<class T, class DF = DelRef<T>>
	class shared_ptr
	{
	public:
		shared_ptr(T* ptr = nullptr)
			: _ptr(ptr)
			, _pCount(nullptr)
			, _pMutex(nullptr)
		{
			if (_ptr)
			{
				_pMutex = new mutex;
				_pCount = new int(1);
			}
		}

		shared_ptr(const shared_ptr<T>& sp)
			: _ptr(sp._ptr)
			, _pCount(sp._pCount)
			, _pMutex(sp._pMutex)
		{
			if (_pCount)
				AddRef();
		}

		shared_ptr<T>& operator=(const shared_ptr<T>& sp)
		{
			if (this != &sp)
			{
				// 让当前对象与资源断开
				Release();

				// 与sp共享
				_ptr = sp._ptr;
				_pCount = sp._pCount;
				if (_pCount)
					AddRef();
			}

			return *this;
		}

		~shared_ptr()
		{
			Release();
		}

		// 具有指针类似行为
		T& operator*()
		{
			return *_ptr;
		}

		T* operator->()
		{
			return _ptr;
		}

		int use_count()
		{
			return *_pCount;
		}

	private:
		void AddRef()
		{
			_pMutex->lock();
			++(*_pCount);
			_pMutex->unlock();
		}

		int SubRef()
		{
			_pMutex->lock();
			--(*_pCount);
			_pMutex->unlock();

			return *_pCount;
		}

		void Release()
		{
			if (_ptr && 0 == SubRef())
			{
				// 用户资源正确的释放方式：应该根据资源的类型
				//delete _ptr;
				DF d;
				d(_ptr);  // d.operator()(_ptr);
				delete _pCount;
			}
		}
	protected:
		T* _ptr;
		int* _pCount;
		mutex* _pMutex;  // 保证计数的安全性
	};
}

void TestSharedPtr()
{
	bite::shared_ptr<int> sp1(new int);
	bite::shared_ptr<int, Free<int>> sp2((int*)malloc(sizeof(int)));
	bite::shared_ptr<FILE, FClose> sp3(fopen("1.txt", "rb"));
}


int main()
{
	TestSharedPtr();
	return 0;
}
#endif

#if 0
// shared_ptr缺陷：存在循环引用问题
#include <memory>

struct ListNode
{
	//ListNode* next;
	//ListNode* pre;

	ListNode(int d)
	: next(nullptr)
	, pre(nullptr)
	, data(d)
	{
		cout << "ListNode(int):" << this << endl;
	}

	~ListNode()
	{
		cout << "~ListNode():" << this << endl;
	}

	shared_ptr<ListNode> next;
	shared_ptr<ListNode> pre;
	int data;
};

void TestList()
{
	shared_ptr<ListNode> sp1(new ListNode(10));
	shared_ptr<ListNode> sp2(new ListNode(20));
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	sp1->next = sp2;
	sp2->pre = sp1;
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
}

int main()
{
	// weak_ptr<int> wp(new int); // 编译报错：weak_ptr对象不能独立管理资源
	TestList();
	return 0;
}
#endif

#if 0
// 循环引用的解决方式：weak_ptr
#include <memory>

struct ListNode
{
	//ListNode* next;
	//ListNode* pre;

	ListNode(int d)
	: data(d)
// 	: next(nullptr)
// 	, pre(nullptr)
// 	, data(d)
	{
		cout << "ListNode(int):" << this << endl;
	}

	~ListNode()
	{
		cout << "~ListNode():" << this << endl;
	}

	//shared_ptr<ListNode> next;
	//shared_ptr<ListNode> pre;
	weak_ptr<ListNode> next;
	weak_ptr<ListNode> pre;

	int data;
};

void TestList()
{
	shared_ptr<ListNode> sp1(new ListNode(10));
	shared_ptr<ListNode> sp2(new ListNode(20));
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;

	sp1->next = sp2;
	sp2->pre = sp1;
	cout << sp1.use_count() << endl;
	cout << sp2.use_count() << endl;
}

int main()
{
	// weak_ptr<int> wp(new int); // 编译报错：weak_ptr对象不能独立管理资源
	TestList();
	return 0;
}
#endif

int main()
{
	return 0;
}


