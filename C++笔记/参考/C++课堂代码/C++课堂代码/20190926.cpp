#include <iostream>
using namespace std;

// �滮���ҹ���
// �������---- 

#include <string>


class WashRoom
{
public:
	void GoToManRoom()
	{
		cout << "��ǰһС��������һ��" << endl;
	}

	void GoToLadyRoom()
	{
		cout << "����һС����shaoziЬ�Ϳ�" << endl;
	}

};


// ������
class Person
{
public:
	// ���麯��
	virtual void GoToWC(WashRoom& wc) = 0;

protected:
	string _name;
	int _age;
};

#if 0
// ���������б�����д����Ĵ��麯��
// ��������Ҳ�ǳ�����
class Man : public Person
{
public:
};
#endif

#if 0
class Man : public Person
{
public:
	virtual void GoToWC(WashRoom& wc)
	{
		wc.GoToManRoom();
	}
};

class Woman : public Person
{
public:
	virtual void GoToWC(WashRoom& wc)
	{
		wc.GoToLadyRoom();
	}
};

#include <windows.h>

void TestWC(size_t n)
{
	Person* p;
	WashRoom wc;
	for (size_t i = 0; i < n; ++i)
	{
		if (rand() % 2)
		{
			p = new Man;
		}
		else
		{
			p = new Woman;
		}

		p->GoToWC(wc);
		delete p;

		Sleep(3000);
	}
}

int main()
{
	// Person p; // �����಻��ʵ��������
	//Man m;

	TestWC(10);
	return 0;
}
#endif

#if 0
class Base
{
public:
// 	Base()
// 	{}

	virtual void TestFunc3()
	{
		cout << "Base::TestFunc3()" << endl;
	}

	virtual void TestFunc1()
	{
		cout << "Base::TestFunc1()" << endl;
	}

	virtual void TestFunc2()
	{
		cout << "Base::TestFunc2()" << endl;
	}


	int _b;
};

class Derived : public Base
{
public:
	virtual void TestFunc5()
	{
		cout << "Derived::TestFunc5()" << endl;
	}

	virtual void TestFunc3()
	{
		cout << "Derived::TestFunc3()" << endl;
	}

	virtual void TestFunc2()
	{
		cout << "Derived::TestFunc2()" << endl;
	}

	virtual void TestFunc4()
	{
		cout << "Derived::TestFunc4()" << endl;
	}
public:
	int _d;
};




// ����ָ�����
//void (*PVFT)();

// ����ָ������
typedef void(*PVFT)();

int main()
{
	cout << sizeof(Base) << endl;

	cout << sizeof(Derived) << endl;

	Base b;
	b._b = 1;


	Derived d;
	d._b = 1;
	d._d = 2;

	// ��Ҫ��ȡ���ĵ�ַ������ǰ4���ֽ�
	//&d;  // ������׵�ַ
	//(int*)(&d)  // ����ָ��--->ָ������ǰ4���ֽ�
	// *(int*)(&d)--->������ǰ4���ֽ��е�����ȡ��--->�������ݡ�===������ַ--�����������
	PVFT* pVFT = (PVFT*)(*(int*)(&d));
	while (*pVFT)
	{
		(*pVFT)();
		++pVFT;
	}

	return 0;
}
#endif

#if 0
// ��̬�ĵ���ԭ��
class Base
{
public:
	virtual void TestFunc1()
	{
		cout << "Base::TestFunc1()" << endl;
	}

	virtual void TestFunc2()
	{
		cout << "Base::TestFunc2()" << endl;
	}

	virtual void TestFunc3()
	{
		cout << "Base::TestFunc3()" << endl;
	}

	int _b;
};

class Derived : public Base
{
public:
	virtual void TestFunc1()
	{
		cout << "Derived::TestFunc1()" << endl;
	}

	virtual void TestFunc3()
	{
		cout << "Derived::TestFunc3()" << endl;
	}

	virtual void TestFunc4()
	{
		cout << "Derived::TestFunc4()" << endl;
	}

	virtual void TestFunc5()
	{
		cout << "Derived::TestFunc5()" << endl;
	}

	int _d;
};


typedef void(*PVFT)();

void PrintVFT(Base& b, const string& s)
{
	cout << s << endl;
	PVFT* pVFT = (PVFT*)(*(int*)&b);
	while (*pVFT)
	{
		(*pVFT)();
		++pVFT;
	}
	cout << endl;
}

void TestVirtual(Base b)
{
	b.TestFunc1();
	b.TestFunc2();
	b.TestFunc3();
}

int main()
{
	Base b;
	b._b = 1;

	Derived d;
	d._b = 1;
	d._d = 2;

	TestVirtual(b);
	TestVirtual(d);

	Base* pb = (Base*)&d;  //Derived*
	pb->TestFunc1();

	return 0;
}
//int main()
//{
//	Base b;
//	b._b = 1;
//
//	Derived d;
//	d._b = 1;
//	d._d = 2;
//
//	PrintVFT(b, "Base VFT:");
//	PrintVFT(d, "Base VFT:");
//	return 0;
//}
#endif

// ����
// ����ģ�ͣ���ͬ�̳з�ʽ�¶����ģ�� + �����麯���̳���ϵ

// ���̳�
// ��̳�
#if 0
class B1
{
public:
	virtual void TestFunc1()
	{
		cout << "B1::TestFunc1()" << endl;
	}

	virtual void TestFunc2()
	{
		cout << "B1::TestFunc2()" << endl;
	}

	int _b1;
};

class B2
{
public:
	virtual void TestFunc3()
	{
		cout << "B2::TestFunc3()" << endl;
	}

	virtual void TestFunc4()
	{
		cout << "B2::TestFunc4()" << endl;
	}

	int _b2;
};

class D : public B1, public B2
{
public:
	virtual void TestFunc1()
	{
		cout << "D::TestFunc1()" << endl;
	}

	virtual void TestFunc4()
	{
		cout << "D::TestFunc4()" << endl;
	}

	virtual void TestFunc5()
	{
		cout << "D::TestFunc5()" << endl;
	}

	int _d;
};

typedef void (*PVFT)();

void PrintVFT1(B1& b, const string& str)
{
	cout << str << endl;

	PVFT* pVFT = (PVFT*)(*(int*)&b);
	while (*pVFT)
	{
		(*pVFT)();
		++pVFT;
	}
	cout << endl;
}

void PrintVFT2(B2& b, const string& str)
{
	cout << str << endl;

	PVFT* pVFT = (PVFT*)(*(int*)&b);
	while (*pVFT)
	{
		(*pVFT)();
		++pVFT;
	}
	cout << endl;
}


int main()
{
	cout << sizeof(D) << endl;

	D d;
	d._b1 = 1;
	d._b2 = 2;

	PrintVFT1(d, "override B1:");

	PrintVFT2(d, "override B2:");
	return 0;
}
#endif

#if 0
// ��������̳�
// 8
class B
{
public:
	virtual void TestFunc1()
	{
		cout << "B::TestFunc1()" << endl;
	}

	virtual void TestFunc2()
	{
		cout << "B::TestFunc2()" << endl;
	}

	int _b;
};

// 
class C1 : virtual public B
{
public:
	virtual void TestFunc1()
	{
		cout << "C1::TestFunc1()" << endl;
	}

	virtual void TestFunc3()
	{
		cout << "C1::TestFunc3()" << endl;
	}

	int _c1;
};

class C2 : virtual public B
{
public:
	virtual void TestFunc2()
	{
		cout << "C2::TestFunc2()" << endl;
	}

	virtual void TestFunc4()
	{
		cout << "C2::TestFunc4()" << endl;
	}

	int _c2;
};

class D : public C1, public C2
{
public:
	virtual void TestFunc1()
	{
		cout << "D::TestFunc1()" << endl;
	}

	virtual void TestFunc3()
	{
		cout << "D::TestFunc3()" << endl;
	}

	virtual void TestFunc4()
	{
		cout << "D::TestFunc4()" << endl;
	}

	virtual void TestFunc5()
	{
		cout << "D::TestFunc5()" << endl;
	}

	int _d;
};


typedef void(*PVFT)();

void PrintVFT1(C1& b, const string& str)
{
	cout << str << endl;

	PVFT* pVFT = (PVFT*)(*(int*)&b);
	while (*pVFT)
	{
		(*pVFT)();
		++pVFT;
	}
	cout << endl;
}

void PrintVFT2(C2& b, const string& str)
{
	cout << str << endl;

	PVFT* pVFT = (PVFT*)(*(int*)&b);
	while (*pVFT)
	{
		(*pVFT)();
		++pVFT;
	}
	cout << endl;
}

void PrintVFT3(B& b, const string& str)
{
	cout << str << endl;

	PVFT* pVFT = (PVFT*)(*(int*)&b);
	while (*pVFT)
	{
		(*pVFT)();
		++pVFT;
	}
	cout << endl;
}

int main()
{
	cout << sizeof(D) << endl;

	D d;
	d._b = 1;
	d._c1 = 2;
	d._c2 = 3;
	d._d = 4;

	PrintVFT1(d, "override C1");
	PrintVFT2(d, "override C2");
	PrintVFT3(d, "override B");
	return 0;
}
#endif


#if 0
class B
{
public:
	// ���캯��������Ϊ�麯��
	// ���캯������Ҫ�ǹ������������а������麯�������������ڹ��캯���н����ĵ�ַ���ڶ����ǰ4���ֽ���
	// ���캯��û��ִ�У�����Ͳ����������ĵ�ַ���ܻ�û�зŵ������ǰ4���ֽ���
	/*virtual*/ B()
	{}

	//virtual inline void TestFunc()
	//{}

	// ��̬��Ա����������Ϊ�麯��
	/*virtual*/ static void TestFunc()
	{}
};

class D : public B
{
public:
	// ���ܣ�ԭ�����������ڱ������Ѿ��ú������滻�˺�������
	//  �Ͳ���Ҫ��������Ҹú���
	// inline void TestFunc()
	//{}
};

void TestVirtual(B& b)
{
	//b.TestFunc();
	//B::TestFunc();
}

int main()
{
	B b;
	TestVirtual(b);
	return 0;
}
#endif


class B
{
public:
	virtual ~B()
	{}

	int _b;
};

class D : public B
{
public:
	D()
	{
		cout << "D()" << endl;
		_p = new int[10];
	}

	~D()
	{
		cout << "~D()" << endl;
		delete[] _p;
	}

	int* _p;
};

// 
int g_a = 10;
int main()
{
	B b1, b2;

	const char* p = "hello";

	B* pb = new D;
	delete pb;

	return 0;
}