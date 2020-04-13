#include <iostream>
using namespace std;

#if 0
int Div(int a, int b)
{
	if (0 == b)
		exit(0);

	return a / b;
}

int main()
{
	int a = 10;
	int b = 5;
	Div(a, 0);
	return 0;
}
#endif

#if 0
/*
错误码-----错误信息
*/
#include <windows.h>

int main()
{
	FILE* pf = fopen("333.txt", "rb");
	if (nullptr == pf)
	{
		// 获取最近发生错误所对应的错误码(windows系统维护)
		size_t errNo = GetLastError();
		cout << "FAILE" << endl;
	}

	// 文件操作

	fclose(pf);
	return 0;
}
#endif

//setjmp和longjmp组合方式

#if 0
// goto: 只能在函数范围内跳转
int Div(int a, int b)
{
	if (0 == b)
		goto L;

	return a / b;
}


int main()
{
	Div(10, 0);
L:
	return 0;
}
#endif

#if 0
int main()
{
    http://www.baidu.com;
	cout << "hello world" << endl;
	return 0;
}
#endif

#if 0
jmp_buf buff;

void TestFunc1()
{
	FILE* pf = fopen("333.txt", "rb");
	if (nullptr == pf)
		longjmp(buff, 1);

	// ...
	fclose(pf);
}

void TestFunc2()
{
	char* p = (char*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		// 让程序跳转到指定位置，buff所标记的位置(setjmp函数调用位置)
		// longjmp：参数1--跳转位置
		//          参数2--用来区分错误类型，state
		longjmp(buff, 2);
	}

	// ...
	free(p);
}

int main()
{
	// setjmp函数在首次调用：设置longjmp的跳转点buff
	// buff: 中记录当前位置程序中寄存器状态信息
	// 第一次调用时，该函数一定返回0
	int state = setjmp(buff);
	if (0 == state)
	{
		// 正常流程
		TestFunc2();
		TestFunc1();
		
	}
	else
	{
		// 非法情况
		switch (state)
		{
		case 1:
			cout << "打开文件失败" << endl;
			break;
		case 2:
			cout << "malloc申请空间失败" << endl;
			break;
		default:
			cout << "未知错误" << endl;
		}
	}

	return 0;
}
#endif

#if 0
void TestFunc1()
{
	FILE* pf = fopen("333.txt", "rb");
	if (nullptr == pf)
	{
		// throw 将该种异常抛出,注意：必须对代码抛出的异常进行捕获，否则：代码会崩溃
		throw 1;
	}

	// ...
	fclose(pf);
}

void TestFunc2()
{
	char* p = (char*)malloc(0x7fffffff);
	if (nullptr == p)
	{
		throw '2';
	}

	// ...
	free(p);
}

int main()
{
	try
	{
		// 对有可能会抛出异常的代码，必须放在try块中
		TestFunc2();
		TestFunc1();
	}
	catch (int err)  // 捕获列表
	{
		// 异常的处理位置
		cout << err << endl;
	}
	catch (char err)
	{
		cout << err << endl;
	}
	
	return 0;
}
#endif


#if 0
// 捕获位置是举例抛出异常位置匹配且最近的一个捕获列表
void TestFunc1()
{
	FILE* pf = fopen("3333.txt", "rb");
	if (nullptr == pf)
	{
		throw 1;
	}
	
	// 。。。
	fclose(pf);
}

void TestFunc2()
{
	int* p = new int[10];

	try
	{
		TestFunc1();
	}
	catch (/*char*/int err)
	{
		delete[] p;
		cout << err << endl;
		return;
	}
	
	// ...
	delete[] p;
}

int main()
{
	try
	{
		TestFunc2();
	}
	catch (int err)
	{
		cout << err << endl;
	}
	
	return 0;
}
#endif

#if 0
void TestFunc()
{
	int e = 10;
	cout << &e << endl;
	throw e; // 抛出异常，相当于代码非法退出
}

int main()
{
	try
	{
		TestFunc();
	}
	catch (int& err)
	{
		cout << &err << endl;
	}
	return 0;
}
#endif

#if 0
class A
{
public:
	A()
	{
		cout << "A():" << this << endl;
	}

	A(const A&)
	{
		cout << "A(const A&):" << this << endl;
	}

	~A()
	{
		cout << "~A():" << this << endl;
	}
};

// 异常抛出时，函数站上的对象全部被销毁掉
void TestFunc()
{
	A a;
	throw a; // 没有直接抛出a，而是用a拷贝构造了一个副本，真正抛出的是a的副本，a对象在函数退出前会销毁掉
}

int main()
{
	try
	{
		TestFunc();
	}
	catch (A& aa)// aa实际是抛出异常对象拷贝的别名
	{
		cout << &aa << endl;
	}

	return 0;
}
#endif

#if 0
class A
{};

void TestFunc()
{
	//throw 1;
	//throw '1';

	A a;
	throw a;
}

// catch(...): 万能捕获，即任意类型的异常都可以捕获到
int main()
{
	try
	{
		TestFunc();
	}
	catch (...)  //使用场景： 不知道异常的类型 || 不关心异常的类型--
	{
		cout << "未知异常" << endl;
	}
	return 0;
}
#endif

#if 0
void TestFunc1()
{
	FILE* pf = fopen("3333.txt", "rb");
	if (nullptr == pf)
	{
		throw 1;
	}

	// 。。。
	fclose(pf);
}

// 异常的重新抛出
void TestFunc2()
{
	int* p = new int[10];

	try
	{
		TestFunc1();
	}
	catch (...) // 1. 可能不知道TestFunc1()函数抛出什么类型的异常
	{           // 2. 不关心TestFunc1()到底抛出什么类型的异常
		delete[] p;
		
		// 将TestFunc1中的异常继续抛出
		throw;
	}

	// ...
	delete[] p;
}


int main()
{
	try
	{
		TestFunc2();
	}
	catch (int err)
	{
		cout << err << endl;
	}
	
	return 0;
}
#endif

#if 0
// 栈展开
void TestFunc1()
{
	throw 1;
}

void TestFunc2()
{
	TestFunc1();
}

void TestFunc3()
{
	TestFunc2();
}

void TestFunc4()
{
	TestFunc3();
}

int main()
{
	try
	{
		TestFunc4();
	}
	catch (int err)
	{
		cout << err << endl;
	}
	
	return 0;
}
#endif

#if 0
class Singleton
{
public:
	static Singleton* GetInstance(int a)
	{
		// 加锁
		if (nullptr == p)
			p = new Singleton(a);
		// 解锁
		return p;
	}

private:
	Singleton(int a)
	{}

	Singleton(const Singleton&) = delete;

	static Singleton* p;
};

Singleton* Singleton::p = nullptr;


int main()
{
	//Singleton s;


	Singleton* ps1 = Singleton::GetInstance(10);
	Singleton* ps2 = Singleton::GetInstance(10);
	Singleton* ps3 = Singleton::GetInstance(10);

	//Singleton s(*ps1);
	return 0;
}
#endif

#if 0
// vs2013忽略了异常规范---vs2013编译器无法测试异常规范
// 如果编译器支持异常规范：以下代码一定会编译失败
// 异常规范：确定抛出异常的类型
// 比如：Div函数如果抛异常，只能抛出整形的异常
int Div(int left, int right)throw(int,float)
{
	if (0 == right)
		throw '1';
	return left / right;
}

// 明确告诉编译器：该函数一定不会抛出异常
void TestFunc()throw()
{
	throw 1;
}
#endif


#include <string>

// 遇到非常情况的处理方式----异常

// 网络
// 数据库
// 其他

// 抽象类---不能实例化对象
class Exception
{
public:
	Exception(int errNo, const string& errInfo)
		: _errNo(errNo)
		, _errInfo(errInfo)
	{}

	// 纯虚函数
	virtual void what() = 0;

protected:
	int _errNo;
	string _errInfo;
};

// 与网络相关的异常
class NetException : public Exception
{
public:
	NetException(int errNo, const string& errInfo)
		: Exception(errNo, errInfo)
	{}

	virtual void what()
	{
		cout << _errNo << ":" << _errInfo << endl;
	}
};


class DBException : public Exception
{
public:
	DBException(int errNo, const string& errInfo)
		: Exception(errNo, errInfo)
	{}

	virtual void what()
	{
		cout << _errNo << ":" << _errInfo << endl;
	}
};


// 操作网络
void TestFunc1()
{
	// ....
	// 非法操作
	NetException e(404, "网页不可达");
	throw e;
}

// 操作数据库
void TestFunc2()
{
	// 非法操作
	DBException e(504, "数据库未打开");
	throw e;
}

#include <vector>

int main()
{
	try
	{
		vector<int> v;
		// v[0] = 10;

		v.at(0) = 10;

		// 抛出bad_alloc
		char* p = new char[0x7fffffff];
		TestFunc1();
		TestFunc2();
		delete[] p;
	}
	catch (Exception& e)
	{
		e.what();
	}
	catch (exception& e)
	{
		cout << typeid(e).name() << endl;
		e.what();
	}
	catch (...)
	{
		cout << "未知异常" << endl;
	}

	return 0;
}