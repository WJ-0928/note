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
������-----������Ϣ
*/
#include <windows.h>

int main()
{
	FILE* pf = fopen("333.txt", "rb");
	if (nullptr == pf)
	{
		// ��ȡ���������������Ӧ�Ĵ�����(windowsϵͳά��)
		size_t errNo = GetLastError();
		cout << "FAILE" << endl;
	}

	// �ļ�����

	fclose(pf);
	return 0;
}
#endif

//setjmp��longjmp��Ϸ�ʽ

#if 0
// goto: ֻ���ں�����Χ����ת
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
		// �ó�����ת��ָ��λ�ã�buff����ǵ�λ��(setjmp��������λ��)
		// longjmp������1--��תλ��
		//          ����2--�������ִ������ͣ�state
		longjmp(buff, 2);
	}

	// ...
	free(p);
}

int main()
{
	// setjmp�������״ε��ã�����longjmp����ת��buff
	// buff: �м�¼��ǰλ�ó����мĴ���״̬��Ϣ
	// ��һ�ε���ʱ���ú���һ������0
	int state = setjmp(buff);
	if (0 == state)
	{
		// ��������
		TestFunc2();
		TestFunc1();
		
	}
	else
	{
		// �Ƿ����
		switch (state)
		{
		case 1:
			cout << "���ļ�ʧ��" << endl;
			break;
		case 2:
			cout << "malloc����ռ�ʧ��" << endl;
			break;
		default:
			cout << "δ֪����" << endl;
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
		// throw �������쳣�׳�,ע�⣺����Դ����׳����쳣���в��񣬷��򣺴�������
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
		// ���п��ܻ��׳��쳣�Ĵ��룬�������try����
		TestFunc2();
		TestFunc1();
	}
	catch (int err)  // �����б�
	{
		// �쳣�Ĵ���λ��
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
// ����λ���Ǿ����׳��쳣λ��ƥ���������һ�������б�
void TestFunc1()
{
	FILE* pf = fopen("3333.txt", "rb");
	if (nullptr == pf)
	{
		throw 1;
	}
	
	// ������
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
	throw e; // �׳��쳣���൱�ڴ���Ƿ��˳�
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

// �쳣�׳�ʱ������վ�ϵĶ���ȫ�������ٵ�
void TestFunc()
{
	A a;
	throw a; // û��ֱ���׳�a��������a����������һ�������������׳�����a�ĸ�����a�����ں����˳�ǰ�����ٵ�
}

int main()
{
	try
	{
		TestFunc();
	}
	catch (A& aa)// aaʵ�����׳��쳣���󿽱��ı���
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

// catch(...): ���ܲ��񣬼��������͵��쳣�����Բ���
int main()
{
	try
	{
		TestFunc();
	}
	catch (...)  //ʹ�ó����� ��֪���쳣������ || �������쳣������--
	{
		cout << "δ֪�쳣" << endl;
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

	// ������
	fclose(pf);
}

// �쳣�������׳�
void TestFunc2()
{
	int* p = new int[10];

	try
	{
		TestFunc1();
	}
	catch (...) // 1. ���ܲ�֪��TestFunc1()�����׳�ʲô���͵��쳣
	{           // 2. ������TestFunc1()�����׳�ʲô���͵��쳣
		delete[] p;
		
		// ��TestFunc1�е��쳣�����׳�
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
// ջչ��
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
		// ����
		if (nullptr == p)
			p = new Singleton(a);
		// ����
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
// vs2013�������쳣�淶---vs2013�������޷������쳣�淶
// ���������֧���쳣�淶�����´���һ�������ʧ��
// �쳣�淶��ȷ���׳��쳣������
// ���磺Div����������쳣��ֻ���׳����ε��쳣
int Div(int left, int right)throw(int,float)
{
	if (0 == right)
		throw '1';
	return left / right;
}

// ��ȷ���߱��������ú���һ�������׳��쳣
void TestFunc()throw()
{
	throw 1;
}
#endif


#include <string>

// �����ǳ�����Ĵ���ʽ----�쳣

// ����
// ���ݿ�
// ����

// ������---����ʵ��������
class Exception
{
public:
	Exception(int errNo, const string& errInfo)
		: _errNo(errNo)
		, _errInfo(errInfo)
	{}

	// ���麯��
	virtual void what() = 0;

protected:
	int _errNo;
	string _errInfo;
};

// ��������ص��쳣
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


// ��������
void TestFunc1()
{
	// ....
	// �Ƿ�����
	NetException e(404, "��ҳ���ɴ�");
	throw e;
}

// �������ݿ�
void TestFunc2()
{
	// �Ƿ�����
	DBException e(504, "���ݿ�δ��");
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

		// �׳�bad_alloc
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
		cout << "δ֪�쳣" << endl;
	}

	return 0;
}