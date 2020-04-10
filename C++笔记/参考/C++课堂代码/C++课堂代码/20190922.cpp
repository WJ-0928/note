#include <iostream>
using namespace std;


#if 0
// 基类/父类
class Base
{
public:
	void SetBase(int b)
	{
		_b = b;
	}

	void PrintBase()
	{
		cout << _b << endl;
	}
public:
	int _b;
};


// 派生类/子类
class Derived : public Base
{
public:
	int _d;
};


int main()
{
	// 派生类继承了基类中的成员变量
	cout << sizeof(Derived) << endl;

	// 派生类继承了基类中的成员函数
	Derived d;
	d.SetBase(10);
	d.PrintBase();
	return 0;
}
#endif

#if 0
// 三种继承方式之间的区别：基类中不同访问权限的成员在子类中的权限
// public
// 基类/父类
class Base
{
public:
	void SetBase(int pub, int pro, int pri)
	{
		_pub = pub;
		_pro = pro;
		_pri = pri;
	}

	void PrintBase()
	{
		cout << _pub << " " << _pro << " " << _pri << endl;
	}

public:
	int _pub;
protected:
	int _pro;
private:
	int _pri;
};


// 派生类/子类---一定要对基类进行扩展
// public继承方式：基类中public和protected访问权限修饰的成员在子类中的权限不变
//               基类中private修饰的成员在子类中不能直接访问 || 不可见---已经被继承到子类中
class Derived : public Base
{
public:
	void SetDerived(int pubD, int proD, int priD)
	{
		_pub = pubD;

		// 基类中protected修饰的成员，在子类中的权限：protected
		_pro = proD;

		// public继承方式，基类中private成员在派生类中不能直接访问---不可见
		//_pri = priD;
	}

public:
	int _pubD;
protected:
	int _proD;
private:
	int _priD;
};

class D : public Derived
{
public:
	void TestFunc()
	{
		_pro = 10;
	}
};


int main()
{
	cout << sizeof(Derived) << endl;

	Derived d;
	d._pub = 10;
	//d._pro = 20;
	return 0;
}
#endif

#if 0
// public
// 基类/父类
class Base
{
public:
	void SetBase(int pub, int pro, int pri)
	{
		_pub = pub;
		_pro = pro;
		_pri = pri;
	}

	void PrintBase()
	{
		cout << _pub << " " << _pro << " " << _pri << endl;
	}

public:
	int _pub;
protected:
	int _pro;
private:
	int _pri;
};


// 派生类/子类---一定要对基类进行扩展
// protected继承方式：基类中被public修饰的成员在子类中的权限降为protected
//                  基类中被protected修饰的成员在子类中的权限不变
//                  基类中private修饰的成员在子类中不能直接访问 || 不可见---已经被继承到子类中
class Derived : protected Base
{
public:
	void SetDerived(int pubD, int proD, int priD)
	{
		_pub = pubD;
		_pro = proD;

		//_pri = priD;
	}
};

class D : public Derived
{
public:
	void TestFunc()
	{
		_pro = 10;
		_pub = 20;
	}
};


int main()
{
	Derived d;
	//d._pub = 10;
	return 0;
}
#endif

#if 0
class Base
{
public:
	void SetBase(int pub, int pro, int pri)
	{
		_pub = pub;
		_pro = pro;
		_pri = pri;
	}

	void PrintBase()
	{
		cout << _pub << " " << _pro << " " << _pri << endl;
	}

public:
	int _pub;
protected:
	int _pro;
private:
	int _pri;
};


// 派生类/子类---一定要对基类进行扩展
// private继承方式：基类中被public和protected修饰的成员在子类中的权限降为private
//                  基类中private修饰的成员在子类中不能直接访问 || 不可见---已经被继承到子类中
class Derived : private Base
{
public:
	void SetDerived(int pubD, int proD, int priD)
	{
		_pub = pubD;
		_pro = proD;

		//_pri = priD;
	}
};

class D : public Derived
{
public:
	void TestFunc()
	{
		//_pub = 10;
		//_pro = 10;
	}
};
#endif


#if 0
class Base
{
public:
	void SetBase(int pub, int pro, int pri)
	{
		_pub = pub;
		_pro = pro;
		_pri = pri;
	}

	void PrintBase()
	{
		cout << _pub << " " << _pro << " " << _pri << endl;
	}

public:
	int _pub;
protected:
	int _pro;
private:
	int _pri;
};


// class默认继承权限---private
// struct默认继承权限---public
struct Derived : Base
{
public:
	void SetDerived(int pubD, int proD, int priD)
	{
		_pub = pubD;
		_pro = proD;

		//_pri = priD;
	}
};

class D : public Derived
{
public:
	void TestFunc()
	{
		_pub = 10;
		_pro = 20;
	}
};

int main()
{
	Derived d;
	d._pub = 10;
	return 0;
}
#endif

#if 0
// 赋值兼容规则---public

class Base
{
public:
	void SetBase(int b)
	{
		_b = b;
	}

	void PrintBase()
	{
		cout << _b << endl;
	}

protected:
	int _b;
};


/*
public继承方式: 基类中成员在派生类中访问权限不会发生改变
*/
struct Derived : public Base
{
public:
	void SetDerived(int b, int d)
	{
		_b = b;
		_d = d;
	}


	int _d;
};

// 如果是public的继承方式，子类与基类的关系： is-a
// is-a: 可以将子类对象看成是一个基类对象
//      函数调用(在类外)：在类外所有用到基类对象的位置，都可以使用派生类对象代替
//      对象模型：对象中各个成员变量在内存中的布局方式


// 1. 可以将子类对象直接赋值给基类对象
// 2. 可以让基类的指针或者引用直接指向子类的对象
int main()
{
	Base b;
	b.SetBase(10);

	Derived d;
	d.SetDerived(20, 30);

	/*b.SetBase(40);
	b.PrintBase();*/

	d.SetBase(40);
	d.PrintBase();

	b = d;

	//d = b;

	Base* pb = &b;
	pb = &d;

	Base& rb = d;

	Derived* pd = &d;
	pd = (Derived*)&b;
	pd->_d = 30;
	return 0;
}
#endif

#if 0
// 同名隐藏
// 基类与派生类中具有相同名称的成员（成员变量，成员函数）时
// 如果通过派生类对象调用相同名称的成员时，优先调用派生类自己
// 如果是成员变量同名，与成员变量的类型是否相同无关
// 如果是成员函数同名，与成员函数的原型是否相同无关
// 都优先调用派生类自己的同名成员
// 如果想要调用基类的同名成员，只需在同名成员前增加基类的名称以及作用域限定符
class Base
{
public:
	void SetBase(int b)
	{
		_b = b;
	}

	void TestFunc(int)
	{}

	void PrintBase()
	{
		cout << _b << endl;
	}

	int _b;
};


struct Derived : public Base
{
public:
	void SetDerived(int b, int d)
	{
		_b = b;
	}

	void TestFunc()
	{}

	char _b;
};

int main()
{
	cout << sizeof(Derived) << endl;

	Derived d;
	d._b = 1;
	d.Base::_b = 2;

	d.Base::TestFunc(10);
	return 0;
}
#endif

// 
#if 0
// 如果基类没有定义构造函数 或者 基类具有默认的构造函数（无参和全缺省的构造函数）
// 1. 派生类可以不用定义
// 2. 如果派生类需要做其他事情，将自己的构造函数显式给出
class Base
{
public:
	Base(int b = 10)
		: _b(b)
	{}

	void SetBase(int b)
	{
		_b = b;
	}

	void TestFunc(int)
	{}

	void PrintBase()
	{
		cout << _b << endl;
	}

	int _b;
};


struct Derived : public Base
{
public:
	// 编译器给派生类生成的默认构造函数
	//Derived()
	//	: Base()
	//{}

	void SetDerived(int b, int d)
	{
		_b = b;
		_d = d;
	}

	void TestFunc()
	{}

	char _d;
};
#endif

/*
1. 预习---60%
2. 课堂代码----回顾本节所讲的内容
3. 做好总结：   思维导图
              写博客
4. 看下
*/
#if 0
class Base
{
public:
	Base(int b)
		: _b(b)
	{}

	Base(const Base& b)
		: _b(b._b)
	{}

	Base& operator=(const Base& b)
	{
		if (this != &b)
		{
			_b = b._b;
		}

		return *this;
	}

	void SetBase(int b)
	{
		_b = b;
	}

	void TestFunc(int)
	{}

	void PrintBase()
	{
		cout << _b << endl;
	}

	~Base()
	{
		cout << "Base::~Base()" << endl;
	}

	int _b;
};


// 如果基类具有无参的构造函数时，派生类必须显式定义自己的构造函数
// 并且必须在其初始化列表的位置显式调用基类的构造函数完成派生类对象
// 中基类部分成员的初始化
struct Derived : public Base
{
public:
	Derived(int b, int d)
		: Base(b)
		, _d(d)
 	{}

	// 编译器给派生类生成的默认构造函数
	//Derived()
	//	: Base()
	//{}

	// 如果基类没有显式定义自己的拷贝构造函数，派生类是否定义都可以
	// 如果基类显式定义自己的拷贝构造函数，派生类必须显式定义拷贝构造函数
	// 并且需要在其拷贝构造初始化列表的位置显式调用基类的拷贝构造函数
	Derived(const Derived& d)
		: Base(d)
		, _d(d._d)
	{}

	/*
	没有涉及到资源管理时：如果派生类没有显式定义自己的赋值运算符重载，编译器会生成一份默认的，
	该默认的赋值运算符重载可以完整的赋值

	如果类中涉及到资源管理：派生类需要将自己的拷贝构造函数显式给出，必须在其内部显式调用基类的
	赋值运算符重载完成基类部分的赋值，在完成自己特有成员的赋值
	*/
	Derived& operator=(const Derived& d)
	{
		if (this != &d)
		{
			Base::operator=(d);
			_d = d._d;
		}

		return *this;
	}

	void SetDerived(int b, int d)
	{
		_b = b;
		_d = d;
	}

	void TestFunc()
	{}

	// 派生类对象：基类部分 + 派生类特有
	~Derived()
	{
		// 派生类清理自己的资源
		cout << "Derived::~Derived()" << endl;

		// 编译器在拍摄类最后一条语句之后插入一条调用基类析构函数的汇编语句
		// 清理派生类对象中属于基类部分的资源
		// call Base::~Base();
	}

	char _d;
};

void TestDerived()
{
	Derived d1(10, 20);
	Derived d2(30, 40);

	d1 = d2;
}

int main()
{
	TestDerived();
	return 0;
}
#endif

#if 0
class Base
{
public:
	Base(int b)
		: _b(b)
	{
		cout << "Base::Base()" << endl;
	}

	~Base()
	{
		cout << "Base::~Base()" << endl;
	}

	int _b;
};

struct Derived : public Base
{
public:
	Derived(int b, int d)
		: Base(b)
		, _d(d)
	{
		cout << "Derived::Derived()" << endl;
	}

	// 派生类对象：基类部分 + 派生类特有
	~Derived()
	{
		// 派生类清理自己的资源
		cout << "Derived::~Derived()" << endl;

		// 编译器在拍摄类最后一条语句之后插入一条调用基类析构函数的汇编语句
		// 清理派生类对象中属于基类部分的资源
		// call Base::~Base();
	}

	char _d;
};

// 
/*
1. 打印结果
    Base::Base()
	Derived::Derived()
	Derived::~Derived()
	Base::~Base()
*/
// 2. 函数调用次序
/*
      基类构造
	  派生类构造
	  派生类析构
	  基类析构

	  创建那个类的对象，调用那个类的构造函数
	  析构那个类的对象，调用那个类的析构函数

	  Derived  d(10, 20);
	  调用派生类的构造函数
	      : 调用基类的构造函数
	  {}

	  调用派生类的析构函数
	  {
	      // 析构派生类自己的资源
		  // call 基类的析构函数
	  }
*/

void TestDerived()
{
	Derived d(10, 20);
}

int main()
{
	TestDerived();
	return 0;
}
#endif

#if 0
// C++98
// 要求：A类不能被继承
class A
{
public:
	static A GetA(int a)
	{
		return A(a);
	}

private:
	A(int a = 10)
		: _a(a)
	{}

protected:
	int _a;
};

class B : public A
{
public:
	//B()
	//	: A(10)
	//{}
};


int main()
{
	//B b;

	A a = A::GetA(10);
	return 0;
}
#endif

#if 0
// C++11 final作用：修饰类时，表明该类不能被继承
class A final
{
public:
	A(int a = 10)
		: _a(a)
	{}

protected:
	int _a;
};

class B : public A
{};

int main()
{
	A a;
	return 0;
}
#endif

#if 0
// 家族：稀世珍宝

class B
{
public:
	void Test()
	{
		cout << "B:" << &_count << endl;
	}
	static int _count;
};

int B::_count = 0;

class D1 : public B
{
public:
	void TestFunc()
	{
		cout << "D1:" << &_count << endl;
		_count = 10;
	}
};

class D2 : public B
{
public:
	void TestFunc()
	{
		cout << "D2:" << &_count << endl;
		_count = 10;
	}
};

int main()
{
	B b;
	b.Test();

	D1 d1;
	d1.TestFunc();

	D2 d2;
	d2.TestFunc();
	return 0;
}
#endif

#if 0
class B
{
	friend void TestFunc();
public:

protected:
	int _b;
};

class D : public B
{
protected:
	int _d;
};


void TestFunc()
{
	// 该函数是基类的友元函数
	// 可以在该函数中访问基类保护或者私有的成员
	B b;
	b._b = 10;

	// 不能访问子类中私有或者保护的成员
	D d;
	d._d = 10;

	// 结论：友元关系 不能被继承
	// 继承：子类一定继承的是基类中的成员
	// 例子：你爸爸的王哥家的财产--与你无关
}
#endif


#if 0
// 不同继承方式下，派生类的对象模型
// B <--- D    单继承：一个类只有一个基类


// 多继承
class B1
{
public:
	int _b1;
};

class B2
{
public:
	int _b2;
};

// 派生类将两个基类中的成员都继承到子类中
// 在派生类对象模型中：先继承那个基类，该基类中的成员就在对象模型的最上方
class D : public B1, public B2
{
public:
	int _d;
};


int main()
{
	cout << sizeof(D) << endl;

	D d;
	d._b1 = 1;
	d._b2 = 2;
	d._d = 3;
	return 0;
}
#endif

#if 0
// 面试题：什么是菱形继承？菱形继承有什么缺陷？如何解决？

// 菱形继承：单继承 + 多继承
class B
{
public:
	void TestFunc()
	{}

public:
	int _b;
};

class C1 : public B
{
public:
	int _c1;
};

class C2 : public B
{
public:
	int _c2;
};


class D : public C1, public C2
{
public:
	int _d;
};

int main()
{
	cout << sizeof(D) << endl;

	D  d;

	// C1从B中继承一个_b, C2从B中继承一个_b
	// D: 从C1中继承一个_b, 从C2中继承一个_b
	// D中就有两份_b
	// 如果直接通过派生类对象访问_b,编译器就不知道访问那个_b
	// 编译时报错：访问不明确
	// 以上就是菱形继承缺陷---菱形继承的二义性问题
	//d._b = 1;
	//d.TestFunc();

	// 代码通过编译：让访问明确
	// 1. 在_b前增加基类的名称
	d.C1::_b = 1;
	d._c1 = 2;

	d.C2::_b = 3;
	d._c2 = 4;

	d._d = 5;

	d.C1::TestFunc();
	d.C2::TestFunc();

	// 2. 能否让最顶层基类成员(B)在D类中只保存一份
	// 可以---菱形虚拟继承
	return 0;
}
#endif

#if 0
// 虚拟继承方式
class B
{
public:
	int _b;
};

class D : virtual public B
{
public:
	int _d;
};


// 虚拟继承和普通的单继承有什么区别？

int main()
{
	cout << sizeof(D) << endl;

	D d;
	d._b = 1;
	d._d = 2;
	return 0;
}
#endif

#if 0
// 菱形虚拟继承
class B
{
public:
	void TestFunc()
	{}

public:
	int _b;
};

class C1 : virtual public B
{
public:
	int _c1;
};

class C2 : virtual public B
{
public:
	int _c2;
};


class D : public C1, public C2
{
public:
	int _d;
};

int main()
{
	cout << sizeof(D) << endl;

	D  d;

	// C1从B中继承一个_b, C2从B中继承一个_b
	// D: 从C1中继承一个_b, 从C2中继承一个_b
	// D中就有两份_b
	// 如果直接通过派生类对象访问_b,编译器就不知道访问那个_b
	// 编译时报错：访问不明确
	// 以上就是菱形继承缺陷---菱形继承的二义性问题
	//d._b = 1;
	//d.TestFunc();

	// 代码通过编译：让访问明确
	// 1. 在_b前增加基类的名称
	d.C1::_b = 1;
	d._c1 = 2;

	d.C2::_b = 3;
	d._c2 = 4;

	d._d = 5;

	d.C1::TestFunc();
	d.C2::TestFunc();

	// 2. 能否让最顶层基类成员(B)在D类中只保存一份
	// 可以---菱形虚拟继承
	d._b = 0;
	d.TestFunc();
	return 0;
}
#endif

#if 0
// 菱形虚拟继承
class B
{
public:
	void TestFunc()
	{}

public:
	int _b;
};

class C1 : virtual public B
{
public:
	int _c1;
};

class C2 : virtual public B
{
public:
	int _c2;
};


class D : public C1, public C2
{
public:
	int _d;
};

int main()
{
	// 24
	cout << sizeof(D) << endl;

	D  d;
	d._b = 1;

	d._c1 = 2;
	d._c2 = 3;
	d._d = 4;

	C1& c1 = d;
	c1._b = 5;

	C2& c2 = d;
	c2._b = 6;

	return 0;
}
#endif

#if 0
class Base1 
{
public:
	int _b1;
};

class Base2 
{
public:
	int _b2;
};

class Derive : public Base1, public Base2 
{
public:
	int _d;
};

int main()
{
	// A. p1 == p2 == p3
	// B. p1 < p2 < p3
	// C. p1 == p3 != p2
	// D. p1 != p2 != p3

	Derive d;
	Base1* p1 = &d;
	Base2* p2 = &d;
	Derive* p3 = &d;

	return 0;
}
#endif


#if 0
// 普通人
class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "全价票" << endl;
	}

protected:
	string _name;
	string _gender;
	string _job;
	int _age;
};

class Student : public Person
{
public:
	void BuyTicket()
	{
		cout << "半价票" << endl;
	}

protected:
	int _stuId;
	double _score;
};

class soldier : public Person
{
public:
	virtual void BuyTicket()
	{
		cout << "军人优先" << endl;
	}
};


// 在程序运行时，根据基类引用实际引用的对象，选择调用对应类的虚函数
void TestBuyTicket(Person& p)
{
	p.BuyTicket();
}

// 如果多态的实现条件没有完全满足，全部调用基类的虚函数

int main()
{
	Person p;
	Student st;
	soldier so;

	TestBuyTicket(p);
	TestBuyTicket(st);
	TestBuyTicket(so);
	return 0;
}
#endif



// 协变
#if 0
class Base
{
public:
	virtual Base* TestFunc()
	{
		cout << "Base::TestFunc()" << endl;
		return this;
	}
};

class Derived : public Base
{
public:
	virtual Derived* TestFunc()
	{
		cout << "Derived::TestFunc()" << endl;
		return this;
	}
};

void TestVirtualFunc(Base* pd)
{
	pd->TestFunc();
}

#endif

#if 0
class A
{};

class B : public A
{};


A a;
B b;

// 基类返回基类的指针或引用，子类返回子类的指针或引用
// 注意：基类和子类不一定是Base类或Derived类
//      只要是具有继承关系的子类和基类都可以
class Base
{
public:
	virtual A& TestFunc()
	{
		cout << "Base::TestFunc()" << endl;
		return a;
	}
};

class Derived : public Base
{
public:
	virtual B& TestFunc()
	{
		cout << "Derived::TestFunc()" << endl;
		return b;
	}
};

void TestVirtualFunc(Base* pd)
{
	pd->TestFunc();
}

int main()
{
	Base b;
	Derived d;
	TestVirtualFunc(&b);
	TestVirtualFunc(&d);
	return 0;
}
#endif

#if 0
// 析构函数
// 常见的面试题：析构函数能不能是虚函数？ 如果可以，什么情况下建议最好将基类的析构函数设置成虚函数？
class Base
{
public:
	virtual ~Base()
	{
		cout << "Base::~Base()" << endl;
	}

protected:
	int _b;
};

class Derived : public Base
{
public:
	Derived()
	{
		_p = new int[10];
	}

	~Derived()
	{
		if (_p)
		{
			delete[] _p;
		}
		cout << "Derived::~Derived()" << endl;

		// call Base::~Base();
	}

protected:
	int* _p;
};

int main()
{
	Base* pb = new Derived;
	delete pb;

	return 0;
}
#endif

#if 0
// C++98--编译器不能帮助用户进行重写的检测
// C++11----override: 让编译器帮助用户检测派生类是否对基类中的某个虚函数进行重写
//                     是：编译成功
//                     否：编译报错
// 注意：override只能修饰子类的虚函数
class Base
{
public:
	virtual void TestFunc1()
	{
		cout << "Base::TestFunc1()" << endl;
	}

	//void TestFunc2()  编译报错：基类中TestFunc2不是虚函数
	virtual void TestFunc2() // OK
	{
		cout << "Base::TestFunc2()" << endl;
	}

	virtual void TestFunc3()
	{
		cout << "Base::TestFunc3()" << endl;
	}
};

class Derived : public Base
{
public:
	// 与基类的函数名字不同
	//virtual void TetsFunc1()override  // 报错：函数名不同，没有构成重写
	virtual void TestFunc1()override    // OK
	{
		cout << "Derived::TestFunc1()" << endl;
	}

	// 基类TestFunc2不是虚函数
	virtual void TestFunc2()override
	{
		cout << "Derived::TestFunc2()" << endl;
	}

	// 与基类虚函数的参数列表不同
	// virtual void TestFunc3(int)override  编译报错：与基类中TestFunc3虚函数参数列表不同
	virtual void TestFunc3()override
	{
		cout << "Derived::TestFunc3()" << endl;
	}
};

void TestFunc(Base& b)
{
	b.TestFunc1();
	b.TestFunc2();
	b.TestFunc3();
}

int main()
{
	Base b;
	Derived d;
	TestFunc(b);
	TestFunc(d);
	return 0;
}
#endif


// final如果修饰虚函数：表明该虚函数不能被派生类重写
class Base
{
public:
	virtual void TestFunc1()
	{
		cout << "Base::TestFunc1()" << endl;
	}
};

class Derived : public Base
{
public:
	virtual void TestFunc1()final
	{
		cout << "Derived::TestFunc1()" << endl;
	}
};

class D : public Derived
{
	virtual void TestFunc1()
	{
		cout << "Derived::TestFunc1()" << endl;
	}
};

void TestFunc(Base& b)
{
	b.TestFunc1();
}

int main()
{
	Base b;
	Derived d;
	D dd;
	TestFunc(b);
	TestFunc(d);
	TestFunc(dd);
	return 0;
}
