#include <iostream>
using namespace std;

// 规划：找工作
// 自曝其短---- 

#include <string>


class WashRoom
{
public:
	void GoToManRoom()
	{
		cout << "往前一小步，文明一大步" << endl;
	}

	void GoToLadyRoom()
	{
		cout << "往后一小步，shaozi鞋和裤" << endl;
	}

};


// 抽象类
class Person
{
public:
	// 纯虚函数
	virtual void GoToWC(WashRoom& wc) = 0;

protected:
	string _name;
	int _age;
};

#if 0
// 在派生类中必须重写基类的纯虚函数
// 否则：子类也是抽象类
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
	// Person p; // 抽象类不能实例化对象
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




// 函数指针变量
//void (*PVFT)();

// 函数指针类型
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

	// 需要获取虚表的地址：对象前4个字节
	//&d;  // 对象的首地址
	//(int*)(&d)  // 整形指针--->指向对象的前4个字节
	// *(int*)(&d)--->将对象前4个字节中的内容取出--->整形数据《===》虚表地址--在数据上相等
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
// 多态的调用原理
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

// 储能
// 对象模型：不同继承方式下对象的模型 + 带有虚函数继承体系

// 单继承
// 多继承
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
// 菱形虚拟继承
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
	// 构造函数不能作为虚函数
	// 构造函数最主要是构造对象，如果类中包含有虚函数，编译器会在构造函数中将虚表的地址放在对象的前4个字节中
	// 构造函数没有执行，对象就不完整，虚表的地址可能还没有放到对象的前4个字节中
	/*virtual*/ B()
	{}

	//virtual inline void TestFunc()
	//{}

	// 静态成员函数不能作为虚函数
	/*virtual*/ static void TestFunc()
	{}
};

class D : public B
{
public:
	// 不能，原因：内联函数在编译器已经用函数体替换了函数调用
	//  就不需要到虚表中找该函数
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