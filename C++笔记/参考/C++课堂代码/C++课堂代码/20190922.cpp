#include <iostream>
using namespace std;


#if 0
// ����/����
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


// ������/����
class Derived : public Base
{
public:
	int _d;
};


int main()
{
	// ������̳��˻����еĳ�Ա����
	cout << sizeof(Derived) << endl;

	// ������̳��˻����еĳ�Ա����
	Derived d;
	d.SetBase(10);
	d.PrintBase();
	return 0;
}
#endif

#if 0
// ���ּ̳з�ʽ֮������𣺻����в�ͬ����Ȩ�޵ĳ�Ա�������е�Ȩ��
// public
// ����/����
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


// ������/����---һ��Ҫ�Ի��������չ
// public�̳з�ʽ��������public��protected����Ȩ�����εĳ�Ա�������е�Ȩ�޲���
//               ������private���εĳ�Ա�������в���ֱ�ӷ��� || ���ɼ�---�Ѿ����̳е�������
class Derived : public Base
{
public:
	void SetDerived(int pubD, int proD, int priD)
	{
		_pub = pubD;

		// ������protected���εĳ�Ա���������е�Ȩ�ޣ�protected
		_pro = proD;

		// public�̳з�ʽ��������private��Ա���������в���ֱ�ӷ���---���ɼ�
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
// ����/����
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


// ������/����---һ��Ҫ�Ի��������չ
// protected�̳з�ʽ�������б�public���εĳ�Ա�������е�Ȩ�޽�Ϊprotected
//                  �����б�protected���εĳ�Ա�������е�Ȩ�޲���
//                  ������private���εĳ�Ա�������в���ֱ�ӷ��� || ���ɼ�---�Ѿ����̳е�������
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


// ������/����---һ��Ҫ�Ի��������չ
// private�̳з�ʽ�������б�public��protected���εĳ�Ա�������е�Ȩ�޽�Ϊprivate
//                  ������private���εĳ�Ա�������в���ֱ�ӷ��� || ���ɼ�---�Ѿ����̳е�������
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


// classĬ�ϼ̳�Ȩ��---private
// structĬ�ϼ̳�Ȩ��---public
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
// ��ֵ���ݹ���---public

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
public�̳з�ʽ: �����г�Ա���������з���Ȩ�޲��ᷢ���ı�
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

// �����public�ļ̳з�ʽ�����������Ĺ�ϵ�� is-a
// is-a: ���Խ�������󿴳���һ���������
//      ��������(������)�������������õ���������λ�ã�������ʹ��������������
//      ����ģ�ͣ������и�����Ա�������ڴ��еĲ��ַ�ʽ


// 1. ���Խ��������ֱ�Ӹ�ֵ���������
// 2. �����û����ָ���������ֱ��ָ������Ķ���
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
// ͬ������
// �������������о�����ͬ���Ƶĳ�Ա����Ա��������Ա������ʱ
// ���ͨ����������������ͬ���Ƶĳ�Աʱ�����ȵ����������Լ�
// ����ǳ�Ա����ͬ�������Ա�����������Ƿ���ͬ�޹�
// ����ǳ�Ա����ͬ�������Ա������ԭ���Ƿ���ͬ�޹�
// �����ȵ����������Լ���ͬ����Ա
// �����Ҫ���û����ͬ����Ա��ֻ����ͬ����Աǰ���ӻ���������Լ��������޶���
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
// �������û�ж��幹�캯�� ���� �������Ĭ�ϵĹ��캯�����޲κ�ȫȱʡ�Ĺ��캯����
// 1. ��������Բ��ö���
// 2. �����������Ҫ���������飬���Լ��Ĺ��캯����ʽ����
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
	// �����������������ɵ�Ĭ�Ϲ��캯��
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
1. Ԥϰ---60%
2. ���ô���----�ع˱�������������
3. �����ܽ᣺   ˼ά��ͼ
              д����
4. ����
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


// �����������޲εĹ��캯��ʱ�������������ʽ�����Լ��Ĺ��캯��
// ���ұ��������ʼ���б��λ����ʽ���û���Ĺ��캯��������������
// �л��ಿ�ֳ�Ա�ĳ�ʼ��
struct Derived : public Base
{
public:
	Derived(int b, int d)
		: Base(b)
		, _d(d)
 	{}

	// �����������������ɵ�Ĭ�Ϲ��캯��
	//Derived()
	//	: Base()
	//{}

	// �������û����ʽ�����Լ��Ŀ������캯�����������Ƿ��嶼����
	// ���������ʽ�����Լ��Ŀ������캯���������������ʽ���忽�����캯��
	// ������Ҫ���俽�������ʼ���б��λ����ʽ���û���Ŀ������캯��
	Derived(const Derived& d)
		: Base(d)
		, _d(d._d)
	{}

	/*
	û���漰����Դ����ʱ�����������û����ʽ�����Լ��ĸ�ֵ��������أ�������������һ��Ĭ�ϵģ�
	��Ĭ�ϵĸ�ֵ��������ؿ��������ĸ�ֵ

	��������漰����Դ������������Ҫ���Լ��Ŀ������캯����ʽ���������������ڲ���ʽ���û����
	��ֵ�����������ɻ��ಿ�ֵĸ�ֵ��������Լ����г�Ա�ĸ�ֵ
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

	// ��������󣺻��ಿ�� + ����������
	~Derived()
	{
		// �����������Լ�����Դ
		cout << "Derived::~Derived()" << endl;

		// �����������������һ�����֮�����һ�����û������������Ļ�����
		// ������������������ڻ��ಿ�ֵ���Դ
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

	// ��������󣺻��ಿ�� + ����������
	~Derived()
	{
		// �����������Լ�����Դ
		cout << "Derived::~Derived()" << endl;

		// �����������������һ�����֮�����һ�����û������������Ļ�����
		// ������������������ڻ��ಿ�ֵ���Դ
		// call Base::~Base();
	}

	char _d;
};

// 
/*
1. ��ӡ���
    Base::Base()
	Derived::Derived()
	Derived::~Derived()
	Base::~Base()
*/
// 2. �������ô���
/*
      ���๹��
	  �����๹��
	  ����������
	  ��������

	  �����Ǹ���Ķ��󣬵����Ǹ���Ĺ��캯��
	  �����Ǹ���Ķ��󣬵����Ǹ������������

	  Derived  d(10, 20);
	  ����������Ĺ��캯��
	      : ���û���Ĺ��캯��
	  {}

	  �������������������
	  {
	      // �����������Լ�����Դ
		  // call �������������
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
// Ҫ��A�಻�ܱ��̳�
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
// C++11 final���ã�������ʱ���������಻�ܱ��̳�
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
// ���壺ϡ���䱦

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
	// �ú����ǻ������Ԫ����
	// �����ڸú����з��ʻ��ౣ������˽�еĳ�Ա
	B b;
	b._b = 10;

	// ���ܷ���������˽�л��߱����ĳ�Ա
	D d;
	d._d = 10;

	// ���ۣ���Ԫ��ϵ ���ܱ��̳�
	// �̳У�����һ���̳е��ǻ����еĳ�Ա
	// ���ӣ���ְֵ�����ҵĲƲ�--�����޹�
}
#endif


#if 0
// ��ͬ�̳з�ʽ�£�������Ķ���ģ��
// B <--- D    ���̳У�һ����ֻ��һ������


// ��̳�
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

// �����ཫ���������еĳ�Ա���̳е�������
// �����������ģ���У��ȼ̳��Ǹ����࣬�û����еĳ�Ա���ڶ���ģ�͵����Ϸ�
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
// �����⣺ʲô�����μ̳У����μ̳���ʲôȱ�ݣ���ν����

// ���μ̳У����̳� + ��̳�
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

	// C1��B�м̳�һ��_b, C2��B�м̳�һ��_b
	// D: ��C1�м̳�һ��_b, ��C2�м̳�һ��_b
	// D�о�������_b
	// ���ֱ��ͨ��������������_b,�������Ͳ�֪�������Ǹ�_b
	// ����ʱ�������ʲ���ȷ
	// ���Ͼ������μ̳�ȱ��---���μ̳еĶ���������
	//d._b = 1;
	//d.TestFunc();

	// ����ͨ�����룺�÷�����ȷ
	// 1. ��_bǰ���ӻ��������
	d.C1::_b = 1;
	d._c1 = 2;

	d.C2::_b = 3;
	d._c2 = 4;

	d._d = 5;

	d.C1::TestFunc();
	d.C2::TestFunc();

	// 2. �ܷ����������Ա(B)��D����ֻ����һ��
	// ����---��������̳�
	return 0;
}
#endif

#if 0
// ����̳з�ʽ
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


// ����̳к���ͨ�ĵ��̳���ʲô����

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
// ��������̳�
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

	// C1��B�м̳�һ��_b, C2��B�м̳�һ��_b
	// D: ��C1�м̳�һ��_b, ��C2�м̳�һ��_b
	// D�о�������_b
	// ���ֱ��ͨ��������������_b,�������Ͳ�֪�������Ǹ�_b
	// ����ʱ�������ʲ���ȷ
	// ���Ͼ������μ̳�ȱ��---���μ̳еĶ���������
	//d._b = 1;
	//d.TestFunc();

	// ����ͨ�����룺�÷�����ȷ
	// 1. ��_bǰ���ӻ��������
	d.C1::_b = 1;
	d._c1 = 2;

	d.C2::_b = 3;
	d._c2 = 4;

	d._d = 5;

	d.C1::TestFunc();
	d.C2::TestFunc();

	// 2. �ܷ����������Ա(B)��D����ֻ����һ��
	// ����---��������̳�
	d._b = 0;
	d.TestFunc();
	return 0;
}
#endif

#if 0
// ��������̳�
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
// ��ͨ��
class Person
{
public:
	virtual void BuyTicket()
	{
		cout << "ȫ��Ʊ" << endl;
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
		cout << "���Ʊ" << endl;
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
		cout << "��������" << endl;
	}
};


// �ڳ�������ʱ�����ݻ�������ʵ�����õĶ���ѡ����ö�Ӧ����麯��
void TestBuyTicket(Person& p)
{
	p.BuyTicket();
}

// �����̬��ʵ������û����ȫ���㣬ȫ�����û�����麯��

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



// Э��
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

// ���෵�ػ����ָ������ã����෵�������ָ�������
// ע�⣺��������಻һ����Base���Derived��
//      ֻҪ�Ǿ��м̳й�ϵ������ͻ��඼����
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
// ��������
// �����������⣺���������ܲ������麯���� ������ԣ�ʲô����½�����ý�����������������ó��麯����
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
// C++98--���������ܰ����û�������д�ļ��
// C++11----override: �ñ����������û�����������Ƿ�Ի����е�ĳ���麯��������д
//                     �ǣ�����ɹ�
//                     �񣺱��뱨��
// ע�⣺overrideֻ������������麯��
class Base
{
public:
	virtual void TestFunc1()
	{
		cout << "Base::TestFunc1()" << endl;
	}

	//void TestFunc2()  ���뱨��������TestFunc2�����麯��
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
	// �����ĺ������ֲ�ͬ
	//virtual void TetsFunc1()override  // ������������ͬ��û�й�����д
	virtual void TestFunc1()override    // OK
	{
		cout << "Derived::TestFunc1()" << endl;
	}

	// ����TestFunc2�����麯��
	virtual void TestFunc2()override
	{
		cout << "Derived::TestFunc2()" << endl;
	}

	// ������麯���Ĳ����б�ͬ
	// virtual void TestFunc3(int)override  ���뱨���������TestFunc3�麯�������б�ͬ
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


// final��������麯�����������麯�����ܱ���������д
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
