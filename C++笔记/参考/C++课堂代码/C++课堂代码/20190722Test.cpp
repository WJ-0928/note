#include <iostream>
using namespace std;

#if 0
int a1 = 10;
int a2 = 20;


int main()
{
	int a = 10;

	return 0;
}
#endif

#include <stdio.h>


#if 0
int a = 1;

namespace N1
{
	int a = 10;
	int b = 20;

	int Add(int left, int right)
	{
		return left + right;
	}
}

// �����ռ����Ƕ��
namespace N2
{
	int a = 30;
	int b = 40;

	int Sub(int left, int right)
	{
		return left - right;
	}

	namespace N3
	{
		int a = 40;
		int b = 50;

		int Mul(int left, int right)
		{
			return left*right;
		}
	}
}


// 1.  ֱ���ڳ�Աǰ�������ռ�����::

int main()
{
	int a = 60;
	printf("%d \n", a);
	printf("%d \n", ::a);
	printf("%d \n", N1::a);
	printf("%d\n", N2::N3::a);
	return 0;
}
#endif

#if 0
namespace N1
{
	int a = 10;
	int b = 20;

	int Add(int left, int right)
	{
		return left + right;
	}
}

//using N1::a;


int a = 10;

int main()
{
	printf("%d\n", N1::a);
	return  0;
}
#endif

#if 0
namespace N1
{
	int a = 10;
	int b = 20;

	int Add(int left, int right)
	{
		return left + right;
	}
}

using namespace N1;


int main()
{
	printf("%d\n", Add(a, b));
	return 0;
}
#endif

#if 0
// ���һ�������д��ڶ����ͬ���������ռ�ʱ���������Ὣ��ϳɲ�һ��
namespace N1
{
	int a = 10;
	int b = 20;

	int Add(int left, int right)
	{
		return left + right;
	}
}


namespace N1
{
	int c = 10;
	int d = 20;

	int Sub(int left, int right)
	{
		return left - right;
	}
}
#endif

#if 0
// #include <iostream.h>

#include <iostream>
using namespace std;

int main()
{
	int a;
	double d;
	cin >> a;
	cin >> d;
	cout << a << " " << d << endl;

	cin >> a >> d;
	cout << a << " " << d << endl;

	cout << 10;
	cout << 12.34 << " " << 'A' << "\n";
	cout << "hello world" << endl;
	return 0;
}
#endif


/*
void TestFunc(int a = 10)
{
	cout << a << endl;
}

int main()
{
	TestFunc();
	TestFunc(100);
	return 0;
}
*/

#if 0
// ȫȱʡ���������в���������Ĭ��ֵ
void TestFunc(int a = 1, int b = 2, int c = 3)
{
	cout << a << " " << b << " " <<c<< endl;
}

int main()
{
	TestFunc();
	TestFunc(10);
	TestFunc(10, 20);
	TestFunc(10, 20, 30);
	return 0;
}
#endif

#if 0
// ��ȱʡ���������ֲ�������Ĭ��ֵ  Ҫ��ֻ�ܴ����������
void TestFunc(int a, int b = 2, int c = 3)
{
	cout << a << " " << b << " " << c << endl;
}

int main()
{
	TestFunc(10);
	TestFunc(10, 20);
	TestFunc(10, 20, 30);
	return 0;
}
#endif

#if 0
void TestFunc(int a = 10);

void TestFunc(int a = 20)
{
	cout << a << endl;
}

int main()
{
	TestFunc();
	return 0;
}
#endif

#if 0
int g_a = 30;

void TestFunc(int a);
void TestFunc(int a)
{
	cout << a << endl;
}

int main()
{
	TestFunc(10);
	return 0;
}
#endif


/*
// �������أ���������ͬ�������� ��ͬ���ֵĺ�������������б�ͬ(���������͡����ʹ���)
// �뷵��ֵ�����Ƿ���ͬ�޹�
int Add(int left, int right)
{
	return left + right;
}

double Add(double left, double right)
{
	return left + right;
}

namespace N
{
	char Add(char left, char right)
	{
		return left + right;
	}
}


int main()
{
	// �������ڱ���׶Σ������ʵ�ε����ͽ�������, �������ݵ�ʵ�����͵Ľ��ѡ����ú��ʵĺ���
	Add(1,2);  // 1-->int, 2-->int  Add(int,int)
	Add(1.0, 2.0);  // 1.9��Ԫ
	return 0;
}
*/

#if 0
// 1
void TestFunc()
{}

// 2��1�ǲ���������ͬ
// 2
void TestFunc(int a)
{}

// 3
void TestFunc(int a, double b)
{}

// 3��4��ͬ���������ʹ���
// 4
void TestFunc(double a, int b)
{}

// 2��5����������
// 5
int TestFunc(char a)
{
	return 0;
}

// 6
char TestFunc(char a)
{
	return a;
}


int main()
{
	int ret1 = TestFunc('a');
	char ret2 = TestFunc('b');
	TestFunc('c');
	return 0;
}
#endif

#if 0
// C���Ժ����������ι��򣺱�����ֻ���ں�������ǰ����_
// _Add
//int Add(int left, int right);
// {
// 	return left + right;
// }

// _Add
double Add(double left, double right);
// {
// 	return left + right;
// }

int main()
{
	Add(1, 2); // call _Add
	return 0;
}
#endif


#if 0
// 
int Add(int left, int right);
// {
// 	return left + right;
// }

// _Add
double Add(double left, double right);
// {
// 	return left + right;
// }

double Add(int left, double right);

int main()
{
	Add(1, 2); // call _Add
	Add(1.0, 2.0);
	Add(1, 2.0);
	return 0;
}
#endif

#if 0
// ��C++������

// _Add
// extern "C"����:  ����������C�ķ����б���
extern "C" int Add(int left, int right);
// {
// 	return left + right;
// }

int main()
{
	Add(1, 2); // ?Add@@YAHHH@Z---vs
	return 0;
}
#endif


#if 0
void TestFunc(int a = 10)
{}

void TestFunc()
{}

int main()
{
	TestFunc();
	return 0;
}
#endif

#if 0
// ��ֵ
// �ŵ�: �Ժ����βεĸı䲻��Ӱ���ⲿ��ʵ��
// ȱ�㣺����ͨ���βθı��ⲿ��ʵ�Σ��˷ѿռ䣬���ʹ��������Ч��
struct SeqList
{
	int array[100000];
	int _size;
};

void Swap(int left, int right)
{
	int temp = left;
	left = right;
	right = temp;
}

// ����ַ
// �ŵ㣺����ͨ���βθı��ⲿ��ʵ�Σ����ε�Ч��
// ȱ�㣺�����ĸ����û�Ӱ���ⲿ��ʵ��  ָ�벻��ȫ�����ʹ���Ŀɶ���
void Swap(int *left, int *right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}


int main()
{
	int a = 10;
	int b = 20;
	Swap(a, b);

	Swap(&a, &b);

	Swap(NULL, NULL);
	return 0;
}
#endif

#if 0
// ���õĸ���
int main()
{
	int a = 10;
	// һ��ʵ������ж������
	int& ra1 = a;
	int& ra2 = a;
	int& ra3 = ra2;

	ra1 = 100;
	ra2 = 200;
	ra3 = 200;

	cout << &a << " " << &ra1 << endl;

	// һ���������͵ı���һ����һ��ʵ���Ϻ󣬾Ͳ��ܹ���������ʵ����
	int b = 10;
	//&ra1 = b;

	if (true)
	{
		int& rb = b;
	}

	//rb = 200;
	return 0;
}
#endif

#if 0
int main()
{
	const int a = 10;
	const int& ra = a;

	const int& rb = 10;

	// ����ͨ��rc�޸�c
	int c = 10;
	const int& rc = c;

	double d = 12.34;
	const int& rd = d;
	cout << &rd << " " << &d << endl;
	return 0;
}
#endif

#if 0
// ������Ϊ�������βΣ������Ҫͨ���βθı��ⲿʵ��---������ͨ��������
//                  �������Ҫͨ���βθı��ⲿʵ��---����const��������
                  
void Swap(int& left, int& right)
{
	int temp = left;
	left = right;
	right = temp;
}

void TestFunc(const int& ra)
{
	//ra = 100;
}


int main()
{
	int a = 10;
	int b = 20;
	Swap(a, b);

	cout << a << " " << b << endl;

	TestFunc(a);
	return 0;
}
#endif

#if 0
// ������Ϊ�����ķ���ֵ����
// ע�⣺����������÷�ʽ���з��أ�һ�����ܷ���ջ�ϵĿռ�
// �������ͣ����ر������������ڲ��ܺ���������Ӱ��
int g_a = 0;
int& Add(int left, int right)
{
	/*
	int ret = left + right;
	return ret;
	*/

	g_a = left + right;
	return g_a;
}

int main()
{
	int& r = Add(1, 2);
	Add(3, 4);
	return 0;
}
#endif

#if 0
#include <time.h>
struct A
{
	int a[10000];
};

void TestFunc1(A* a)
{}

void TestFunc2(A& a)
{}

void TestRefAndValue()
{
	A a;
	// ��ֵ��Ϊ��������
	size_t begin1 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc1(&a);
	size_t end1 = clock();

	// ��������Ϊ��������
	size_t begin2 = clock();
	for (size_t i = 0; i < 10000; ++i)
		TestFunc2(a);
	size_t end2 = clock();

	// �ֱ���������������н������ʱ��
	cout << "TestFunc1(int*)-time:" << end1 - begin1 << endl;
	cout << "TestFunc2(int&)-time:" << end2 - begin2 << endl;
}
// ���ж�Σ����ֵ�������ڴ��η����Ч������
int main()
{
	for (int i = 0; i < 10; ++i)
	{
		TestRefAndValue();
	}
	return 0;
}
#endif

#if 0
// ָ������õ�����*****
int main()
{
	int a = 10;

	int* pa = &a;
	*pa = 100;

	int& ra = a;
	ra = 100;
	return 0;
}
#endif


#if 0
int main()
{
	int a = 10;
	int b = 20;
	int* pa;
	int&ra = a;
	//&ra = b;

	pa = &a;
	pa = &b;

	++ra;
	++pa;

	char c = 'a';
	char& rc = c;
	char* pc = &c;

	cout << sizeof(rc) << " " << sizeof(pc) << endl;


	int** pb;
	int&& r = 10;   // C++11 ��ֵ����
	return 0;
}
#endif

// �����ȱ�㣺
// �꣺���峣��

#if 0
#define PI "3.14"

int main()
{
	cout << PI * 2 * 2 << endl;
	return 0;
}
#endif

#if 0
int main()
{
	const int a = "10";
	//int array[a];

	int* pa = (int*)&a;
	*pa = 100;

	cout << 10/*a*/ << " " << *pa << endl;
	return 0;
}
#endif


#if 0
// �꺯����
#define MAX(a,b) ((a)>(b))? (a):(b)


int main()
{
	int a = 10;
	int b = 20;
	int c = MAX(a, b);
	c = MAX(++b, a);
	return 0;
}
#endif

#if 0
#include "InlineFunc.h"

// ��������
// �ڱ���׶Σ������������ĵ���λ��ʹ������������չ��
inline int Add(int left, int right)
{
	Add(left, right);
	return left + right;
}

int main()
{
	int a = 10;
	int b = 20;
	int c = 0;
	c = Add(a, b);

	Sub(a, b);
	return 0;
}
#endif

// auto

#if 0
int TestAuto()
{
	return 0;
}

#include <map>
#include <string>

int main()
{
	int a = 10;

	auto b = a;
	auto c = 'c';
	auto d = TestAuto();

	cout << typeid(a).name() << endl;
	cout << typeid(b).name() << endl;
	cout << typeid(c).name() << endl;
	cout << typeid(d).name() << endl;

	std::map<std::string, std::string> m{ { "apple", "ƻ��" }, {"banana", "�㽶"} };
	//std::map<std::string, std::string>::iterator it = m.begin();
	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << " " << it->second << endl;
		++it;
	}
	cout << endl;
	
	return 0;
}
#endif

// void TestAuto(auto a)
// {}

#if 0
int main()
{
	int a = 10;
	auto pa1 = &a;
	auto* pa2 = &a;

	cout << typeid(pa1).name() << endl;
	cout << typeid(pa2).name() << endl;

	auto ra1 = a;
	auto& ra2 = a;

	cout << &a << " " << &ra1 << endl;
	cout << &a << " " << &ra2 << endl;

	auto c1 = 1, c2 = 2, c3 = 3;
	//auto d1 = 1, d2 = 2.0;

	int arr1[10] = { 1, 2, 3 };
	//auto arr2[] = { 1, 2, 3 };
	return 0;
}
#endif


#if 0
void TestFor(int array[10])
{
	for (auto e : array)
		cout << endl;
}

int main()
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
	{
		array[i] *= 2;
	}

	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
		cout << array[i] << " ";
	cout << endl;

	for (auto& e : array)
		e = e * 2;

	for (auto e : array)
		cout << e << " ";
	cout << endl;

	int* p = array;

// 	for (auto e : p)
// 		cout << e << " ";
// 	cout << endl;

	return 0;
}
#endif

#if 0
void TestFunc(int a)
{
	cout << "TestFunc(int)" << endl;
}

void TestFunc(int* pa)
{
	cout << "TestFunc(int*)" << endl;
}

int main()
{
	TestFunc(0);
	TestFunc(NULL);
	TestFunc(nullptr);

	int* p = nullptr;
	return 0;
}
#endif

#if 0
struct Student
{
	void SetStudentInfo(char* name, char* gender, int age)
	{
		strcpy(_name, name);
		strcpy(_gender, gender);
		_age = age;
	}

	void Study()
	{
		cout << "�������˵�ѧϰ" << endl;
	}

	void PrintStudentInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;
	}

private:
protected:
	char _name[20];
	char _gender[3];
	int _age;
};

struct A
{
	int a;
	int b;
	int c;
};

int main()
{
	A aa;
	aa.a = 10;

	Student s1, s2, s3;
	s1.SetStudentInfo("Peter", "��", 18);
	s2.SetStudentInfo("jingjing", "Ů", 19);
	s3.SetStudentInfo("summer", "��", 3);
	//cout << s1._age << endl;

	s1.PrintStudentInfo();
	s2.PrintStudentInfo();
	s3.PrintStudentInfo();
	return 0;
}
#endif

#if 0
int a = 10;

namespace N
{
	int a = 20;
}

// void SetTest()
// {}

class Test
{
public:
	void SetTest(int a)
	{
		_a = a;
	}

	void Print()  // ��
	{
		cout << _a << endl;
	}

private:
	int _a;  // _a�൱�������Ա������ȫ�ֱ���
};


int g_a = 10;

int main()
{
	int a = 40;
	Test t;
	t.SetTest(30);

	cout << a << endl; // 40
	cout << ::a << endl; // 10
	cout << N::a << endl; // 20
	t.Print();            // 30

	cout << g_a << endl;
	return 0;
}
#endif


#if 0
class Student
{
public:
	void SetStudentInfo(char* name, char* gender, int age)
	{
		strcpy(_name, name);
		strcpy(_gender, gender);
		_age = age;
	}

	void Study()
	{
		cout << "�������˵�ѧϰ" << endl;
	}

	void PrintStudentInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;
	}

private:
protected:
	char _name[20];
	char _gender[3];

public:
	int _age;
};


int main()
{
	Student s1, s2, s3;
	//Student._age = 10;

	cout << sizeof(Student) << endl;

	s1.SetStudentInfo("Peter", "��", 18);
	s2.SetStudentInfo("jingjing", "Ů", 19);
	s3.SetStudentInfo("summer", "��", 3);
	//cout << s1._age << endl;

	s1.PrintStudentInfo();
	s2.PrintStudentInfo();
	s3.PrintStudentInfo();

	return 0;
}
#endif

#if 0
class Student
{
public:
	void SetStudentInfo(char* name, char* gender, int age)
	{
		strcpy(_name, name);
		strcpy(_gender, gender);
		_age = age;
	}

	void Study()
	{
		cout << "�������˵�ѧϰ" << endl;
	}

	void PrintStudentInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;
	}

	char _name[20];
	char _gender[3];
	int _age;
};

class A
{};

int main()
{
	cout << sizeof(A) << endl;
	Student s1, s2, s3;
	cout << sizeof(Student) << endl;
	
	s1.SetStudentInfo("Peter", "��", 18);
	s2.SetStudentInfo("jingjing", "Ů", 19);
	s3.SetStudentInfo("summer", "��", 3);

	s1.PrintStudentInfo();
	s2.PrintStudentInfo();
	s3.PrintStudentInfo();
	return 0;
}
#endif


#if 0
class A
{
public:
	void SetA(int a)
	{
		_a = a;
	}

private:
	int _a;
};

class B
{
public:
	void TestFunc1()
	{}

	void TestFunc2()
	{}
};


// ����Ĵ�С
class C
{};

struct D
{
	int a;
	char b;
	double d;
	char c;
};

// E  ��Աa

int main()
{
	C c1, c2, c3;
	cout << offsetof(D, d) << endl;

	cout << sizeof(B) << endl;
	cout << sizeof(C) << endl;
	return 0;
}
#endif

#if 0
class Student
{
public:

	// thisָ���ǳ�Ա������һ��Ĭ�ϵ��βΣ��ò�������Ҫ�û����ݣ��������Զ����д���
	void SetStudentInfo(char* name, char* gender, int age)
 	{
 		// this: ָ����һ�����øú�������
 		// ���ݷ�ʽ��ͨ��ecx����
 		cout << this << endl;
 		strcpy(this->_name, name);
 		strcpy(this->_gender, gender);
 		this->_age = age;
 	}

	// ���������ĺ���---�����������
	// this�Ĵ��ݷ�ʽ��ͨ������ѹջ�ķ�ʽ
	void TestFunc(...)
	{}

	void TestThis()
	{
		cout << this << endl;
		this->_age = 10;
	}

	void Study()
	{
		cout << "�������˵�ѧϰ" << endl;
	}

	void PrintStudentInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;
	}

	char _name[20];
	char _gender[3];
	int _age;
};


int main()
{
	Student s1, s2, s3;
	//cout << this << endl;
	s1.SetStudentInfo("Peter", "��", 18);
	s1.PrintStudentInfo();
	s1.Study();
	s1.TestFunc(1, 2, 3);
	s1.TestThis();

	Student* ps = &s1;
	ps->TestThis();

	ps = nullptr;
	ps->TestThis();

	s2.SetStudentInfo("jingjing", "Ů", 19);
	s3.SetStudentInfo("summer", "��", 3);

	s1.PrintStudentInfo();
	s2.PrintStudentInfo();
	s3.PrintStudentInfo();
	return 0;
}
#endif

/*
// �������һ��Ů���ѣ�
Ů����----Ⱥ��---���
�˽�Ů�������Ϣ
Ů�����س� 
*/

/*
��������α�����ģ�
1. ʶ������
2. ʶ�����еĳ�Ա����
3. ʶ�����еĳ�Ա���� & �Գ�Ա���������޸�
*/
#if 0
class Student
{
public:
	/*
	void SetStudentInfo(Student* const this, char* name, char* gender, int age)
	{
	    strcpy(this->_name, name);
		strcpy(this->_gender, gender);
		this->_age = age;
	}
	*/
	void SetStudentInfo(char* name, char* gender, int age)
	{
		strcpy(_name, name);
		strcpy(_gender, gender);
		_age = age;
	}

	/*
	void PrintStudentInfo(Student* const this)
	{
		cout << this->_name << " " << this->_gender << " " << this->_age << endl;
	}
	*/
	void PrintStudentInfo()
	{
		cout << _name << " " << _gender << " " << _age << endl;
	}

	char _name[20];
	char _gender[3];
	int _age;
};


int main()
{
	return 0;
}
#endif

#if 0
class Date
{
public:
	void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	int a;
	int b = 0;
	int c(0);

	Date d1;
	d1.SetDate(2019, 7, 25);
	d1.PrintDate();

	Date d2(2019, 7, 25);
	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Date(int,int,int):" << this << endl;
	}

	Date()
	{
		_year = 1900;
		_month = 1;
		_day = 1;
	}

	void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

void TestDate()
{
	Date d1(2019, 7, 25);
	d1.PrintDate();

	Date d2;
	// Date d3();  ��һ����������
}

int main()
{
	TestDate();
	return 0;
}
#endif


#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Date(int,int,int):" << this << endl;
	}

	Date()
	{
		_year = 1900;
		_month = 1;
		_day = 1;
	}

	void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	Date d;
	return 0;
}
#endif

#if 0
class Time
{
public:
	Time(int hour = 0, int minute = 0, int second = 0)
	{
		_hour = hour;
		_minute = minute;
		_second = second;
	}

	Time()
	{}

private:
	int _hour;
	int _minute;
	int _second;
};

// 
class Date
{
public:
// 	Date(int year = 1900, int month = 1, int day = 1)
// 	{
// 		_year = year;
// 		_month = month;
// 		_day = day;
// 		cout << "Date(int,int,int):" << this << endl;
// 	}
// 
// 	Date()
// 	{
// 		_year = 1900;
// 		_month = 1;
// 		_day = 1;
// 	}

	// û���κ����壬���󴴽���֮���Ծ������ֵ
// 	Date()
// 	{}

	void SetDate(int year, int month, int day)
	{
		_year = year;
		_month = month;
		_day = day;
	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}
private:
	int _year;
	int _month;
	int _day;
	Time _t;
};


// �﷨�� ���һ����û����ʽ����(�û��Զ���)�κι��캯������������������һ���޲ε�Ĭ�Ϲ��캯��
// �Ż����������о��Լ���Ҫ��ʱ��������
int main()
{
	Date d;    // call Date::Date();  call Time::Time()
	return 0;
}
#endif

#include <malloc.h>
#include <assert.h>

#if 0
typedef int DataType;

class SeqList
{
public:
	SeqList(size_t capacity = 10)
	{
		_array = (DataType*)malloc(capacity * sizeof(DataType));
		assert(_array);
		_capacity = capacity;
		_size = 0;
		cout << "SeqList(size):" << this << endl;
	}

	// �ڶ�������ʱ���ɱ������Զ����е��ã���ɶ�������Դ����������
// 	~SeqList()
// 	{
// 		cout << "~SeqList():" << this << endl;
// 		if (_array)
// 		{
// 			free(_array);
// 			_array = nullptr;
// 			_capacity = 0;
// 			_size = 0;
// 		}
// 	}

private:
	DataType* _array;
	size_t _capacity;
	size_t _size;
};

void TestSeqList()
{
	SeqList s;
}


int main()
{
	TestSeqList();
	return 0;
}
#endif

#if 0
class String
{
public:
	String(char* str = "")
	{
		if (nullptr == str)
			str = "";

		// str="hello"
		_str = (char*)malloc(strlen(str)+1);
		strcpy(_str, str);
	}

	~String()
	{
		if (_str)
		{
			free(_str);
			_str = nullptr;
		}
	}
private:
	char* _str;
};

class Person
{
	//...
private:
	String _name;
	String _gender;
	int _age;
};

void TestPerson()
{
	Person p;
}

int main()
{
	TestPerson();
	return 0;
}
#endif


#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Date(int,int,int):" << this << endl;
	}

	// ���Ѿ����ڵĶ��󿽱������¶���ʱ���ɱ������Զ����е���
// 	Date(const Date& d)
// 	{
// 		_year = d._year;
// 		_month = d._month;
// 		_day = d._day;
// 
// 		cout << "Date(Date&):" << this << endl;
// 	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	int a = 10;
	int b(a);

	Date d1(2019,7,26);
	Date d2(d1);

	Date d3;
	d3 = d1;
	return 0;
}
#endif


#if 0
class String
{
public:
	String(char* str = "")
	{
		if (nullptr == str)
			str = "";

		// str="hello"
		_str = (char*)malloc(strlen(str) + 1);
		strcpy(_str, str);
	}

	~String()
	{
		if (_str)
		{
			free(_str);
			_str = nullptr;
		}
	}
private:
	char* _str;
};

void TestString()
{
	String s1("hello");
	//String s2(s1);
	String s2;

	//1. ǳ����  2. s2ԭ���Ŀռ䶪ʧ��
	s2 = s1;
}

int main()
{
	TestString();
	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Date(int,int,int):" << this << endl;
	}

	// ���Ѿ����ڵĶ��󿽱������¶���ʱ���ɱ������Զ����е���
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;
	
		cout << "Date(Date&):" << this << endl;
	}

	// 
	Date AddDays(int days)
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}

	//bool operator==()

	// 10 + 20
	Date operator+(int days)
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}

	bool operator==(const Date& d)
	{
		return _year == d._year &&
			   _month == d._month &&
			   _day == d._day;
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};


// void operator@()
// {}

enum Data{ONE, TWO, THREE};
int operator+(int left, Date right)
{
	return left + right;
}

void TestDate()
{
	Date d(2019, 7, 26);
	d = d.AddDays(3);

	d = d + 100;
}

int main()
{
	TestDate();

	Date d1(2019, 7, 26);
	Date d2(2018, 7, 26);
	if (d1 == d2)
		;

	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Date(int,int,int):" << this << endl;
	}

	// ���Ѿ����ڵĶ��󿽱������¶���ʱ���ɱ������Զ����е���
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;

		cout << "Date(Date&):" << this << endl;
	}

	// a = b = c;
	Date& operator=(const Date& d)
	{
		//cout << this << " = " << &d << endl;
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}
		
		return *this;
	}

	// 10 + 20
	Date operator+(int days)
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}

	bool operator==(const Date& d)
	{
		return _year == d._year &&
			_month == d._month &&
			_day == d._day;
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

private:
	int _year;
	int _month;
	int _day;
};

int main()
{
	int a = 10;
	int b = 20;
	int c = 30;

	a = b;

	a = b = c;

	Date d1(2019, 7, 26);
	Date d2;
	Date d3;

	//d2 = d1;

	//d1 = d1;

	d3 = d2 = d1;
	d3.operator=(d2.operator=(d1));


	Date& d4 = d1;





	d4 = d1;
	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Date(int,int,int):" << this << endl;
	}

	// ���Ѿ����ڵĶ��󿽱������¶���ʱ���ɱ������Զ����е���
	Date(const Date& d)
	{
		_year = d._year;
		_month = d._month;
		_day = d._day;

		cout << "Date(Date&):" << this << endl;
	}

	// a = b = c;
	Date& operator=(const Date& d)
	{
		//cout << this << " = " << &d << endl;
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	// 10 + 20
	Date operator+(int days)
	{
		Date temp(*this);
		temp._day += days;
		return temp;
	}

	bool operator==(const Date& d)
	{
		return _year == d._year &&
			_month == d._month &&
			_day == d._day;
	}

	bool operator!=(const Date& d)
	{
		return !(*this == d);
	}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	// ǰ��++���ȼ�1��ʹ��(ʹ�õ��Ǽ�1֮��Ľ��)
	Date& operator++()
	{
		_day += 1;
		return *this;
	}

	// ����++������ǰ�����1�����ؼ�1֮ǰ�ľ�ֵ��  
	Date operator++(int)
	{
		Date temp(*this);
		_day += 1;
		return temp;
	}

	// ǰ��++
	Date& operator--()
	{
		_day -= 1;
		return *this;
	}

	// ����++  
	Date operator--(int)
	{
		Date temp(*this);
		_day -= 1;
		return temp;
	}

private:
	int _year;
	int _month;
	int _day;
};


int main()
{
	int a = 10;
	a++;  // ��ʹ�ú��1
	++a;  // �ȼ�1��ʹ��
	a--;
	--a;

	Date d(2019, 7, 26);
	Date ret;

	ret = ++d;

	ret = d++;
	


	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		_year = year;
		_month = month;
		_day = day;
		cout << "Date(int,int,int):" << this << endl;
	}


	// this�����ͣ������� * const--->ָ�����޸�
	void SetDate(int year, int month, int day)
	{
		cout << typeid(this).name() << endl;
		_year = year;
		_month = month;
		_day = day;
	}

	void TestFunc1()
	{}

	void TestFunc2()const
	{}


	// ���ۣ�const��Ա�����в��ܵ�����ͨ���͵ĳ�Ա����
	// ֻ�ܵ���const���͵ĳ�Ա����
	void TestFunc3()const
	{
		// TestFunc1()  // ����ʧ��
		TestFunc2();
	}
	
	// ���ۣ���ͨ��Ա�����У�const���ͳ�Ա����ͨ���ͳ�Ա���������Ե���
	void TestFunc4()
	{
		TestFunc1();
		TestFunc2();
	}

	// this�����ͣ�const������ * const ������thisָ������е����ݲ����޸�
	// ���ۣ�const��Ա�����в����޸����еĳ�Ա����
	// ���⣺�������ĳ����Ա��mutable��������£���const��Ա�����л������޸ĸó�Ա
	void PrintDate()const
	{
		cout << typeid(this).name() << endl;
		this->_day += 1; //���뱨��
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	// �ڸú����У������޸����еĳ�Ա����
	Date* operator&()
	{
		// ....
		return this;
	}

	const Date* operator&()const
	{
		return this;
	}

private:
	int _year;
	int _month;
	mutable int _day;
};


int main()
{
	Date d1(2019, 7, 27);
	d1.SetDate(2019, 7, 27);

	// ��ͨ���Ͷ�����Ե���const���ͳ�Ա����
	// const���ͳ�Ա�����У�ֻ�ܶ�ȡ�����е����ݣ��������������д����
	// ��ͨ���Ͷ��󣺼��ɶ�Ҳ��д
	d1.PrintDate();

	cout << &d1 << endl;

	// const���Ͷ����ܵ�����ͨ���ͳ�Ա��������ͨ��Ա�����п����޸���ĳ�Ա������
	// ��const���Ͷ����еĳ�Աʱ�������޸ĵģ��������������const���Ͷ��������ͨ��Ա������
	// ��������ܶ�����ͨ��Ա�����ж�const���Ͷ��������ݽ����޸�
	const Date d2(2019, 7, 28);
	cout << &d2 << endl;
	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
	{
		// �������в��ǳ�ʼ��---->��ֵ
		_year = year;
		_month = month;
		_day = day;

		// ��Ϊ����ʼ��ֻ�ܳ�ʼ��һ��
		_day = 10;
		_day = 11;
		_day = 12;
	}



private:
	int _year;
	int _month;
	int _day;

	const int _a;
};
#endif

#if 0
class Time
{
public:
	Time(int hour, int minute, int second)
		: _hour(hour)
		, _minute(minute)
		, _second(second)
	{}


private:
	int _hour;
	int _minute;
	int _second;
};
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1) 
		: _year(year)
		, _month(month)
		, _day(day)
		, _a(_day)
		, _b(10)
		, _t(0,0,0)
	{
		// ��ֵ
// 		_year = year;
// 		_month = month;
// 		_day = day;
	}

private:
	int _year;
	int _month;
	int _day;

	// ��Щ��Ա�����ڳ�ʼ���б��λ�ý��г�ʼ��
	int& _a;
	const int _b;
	Time _t; // ���ԣ��й��캯��(���Ǹù��캯�������޲εĹ��캯�����߲���ȫȱʡ�Ĺ��캯��)
};

int main()
{
	Date d1(2019, 7, 27);
	return 0;
}
#endif

#if 0
class Time
{
public:
	Time(int hour=0, int minute=0, int second=0)
		: _hour(hour)
		, _minute(minute)
		, _second(second)
	{
		cout << "Time(int, int, int)" << endl;
	}


private:
	int _hour;
	int _minute;
	int _second;
};

class Date
{
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
	Time _t;
};


int main()
{
	Date d1(2019, 7, 27);
	return 0;
}
#endif

#if 0
// ��Ա���������������е���������������ڳ�ʼ���б��еĳ�ʼ������
// �����ڳ�ʼ���б��г��ֵ��Ⱥ�����޹�
// ���飺��ò�Ҫʹ�ó�Ա��ʼ����Ա
class Date
{
public:
	Date(int year, int month)
		: _year(year)
		, _month(month)
		, _day(_month)
	{}

private:
	int _year;
	int _day;
	int _month;
	
};


int main()
{
	Date d1(2019, 7);
	return 0;
}
#endif

#if 0
class Date
{
public:
	// ���ι��캯����������ת��������
	explicit Date(int year)
		: _year(year)
		, _month(1)
		, _day(1)
	{
		cout << "Date(int):" << this << endl;
	}

	Date(const Date& d)
		: _year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		cout << "Date(const Date&):" << this << endl;
	}


	Date& operator=(const Date& d)
	{
		cout << this << " = " << &d << endl;
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}



private:
	int _year;
	int _month;
	int _day;

};

int main()
{
	Date d(2018);

	// ���õ��ι��캯����2019ת��Ϊ��ʱ����
	// ���ʹ����ʱ�����d��ֵ
	d = 2019;

	return 0;
}
#endif

// ���֪��һ���ഴ���˶��ٸ�����
/*
1. ���������ʲôʱ�������˶���  ����ʲô���������
    ���캯�� || ��������
	��������
2. ��������¼��������ĸ���----int
3. ������Ӧ��ÿ��������
*/


#if 0
int _count = 0;

class Date
{
public:
	 Date(int year=1900, int month=1, int day=1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
		 _count++;
	}

	Date(const Date& d)
		: _year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		_count++;
	}

	Date& operator=(const Date& d)
	{
		cout << this << " = " << &d << endl;
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	~Date()
	{
		--_count;
	}
private:
	int _year;
	int _month;
	int _day;

	//int _count;
};


void TestDate()
{
	Date d1;
	Date d2;
	cout << _count << endl;
}

int main()
{
	Date d1;
	Date d2(d1);
	_count = 0;

	cout << _count << endl;

	TestDate();

	cout << _count << endl;
	return 0;
}
#endif

#if 0
class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
		_count++;
	}

	Date(const Date& d)
		: _year(d._year)
		, _month(d._month)
		, _day(d._day)
	{
		_count++;
	}

	Date& operator=(const Date& d)
	{
		cout << this << " = " << &d << endl;
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	~Date()
	{
		--_count;
	}

	void TestFunc()
	{

	}

	// ��̬��Ա����
	static int GetObjCount()//const
	{
		//TestFunc();

		//cout << this << endl;
		//cout << _year << endl;
		return _count;
	}

private:
	int _year;
	int _month;
	int _day;

	static int _count;
};

int Date::_count = 0;

void TestDate()
{
	Date d1;
	Date d2(d1);
	cout << Date::GetObjCount() << endl;
}

int main()
{
	Date d[100];

	cout << Date::GetObjCount() << endl;;

	Date d1;
	Date d2(d1);
	cout << Date::GetObjCount() << endl;

	TestDate();
	cout << Date::GetObjCount() << endl;
	return 0;
}
#endif

#if 0
int main()
{
	cout << sizeof(Date) << endl;

	cout << Date::_count << endl;
	cout << &Date::_count << endl;

	Date d1;
	d1._year = 2019;
	d1._count = 10;


	Date d2;
	d2._count = 11;

	cout << &d1._count << " " << &d2._count << endl;
	return 0;
}
#endif


#if 0
class Solution {
public:
	class Sum
	{
	public:
		Sum()
		{
			++_count;
			_sum += _count;
		}

		static void Reset()
		{
			_count = _sum = 0;
		}

		static size_t GetSum()
		{
			return _sum;
		}
	private:
		static size_t _count;
		static size_t _sum;
	};

	int Sum_Solution(int n) {
		Sum::Reset();
		Sum* ps = new Sum[n];
		delete[] ps;

		return Sum::GetSum();
	}
};

size_t Solution::Sum::_count = 0;
size_t Solution::Sum::_sum = 0;

int main()
{
	Solution s;

	cout << s.Sum_Solution(3) << endl;
	cout << s.Sum_Solution(5) << endl;
	return 0;
}
#endif

#if 0
class Time
{
	friend void Print();
public:
	Time(int hour, int minute, int second)
		: _hour(hour)
		, _minute(hour)
		, _second(second)
	{}

private:
	int _hour;
	int _minute;
	int _second;
};

class Date
{
	friend void Print();
	friend istream& operator>>(istream& _cin, Date& d);
	friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
	}

	// <<�����ز���д����ĳ�Ա��������Ϊ���һ������һ��Ϊ�����(ostream)���������,
	// �����������Ϊ��ĳ�Ա���������һ��������Ϊthisָ��
// 	void operator<<(ostream& _cout)
// 	{
// 		_cout << _year << "-" << _month << "-" << _day;
// 	}

private:
	int _year;
	int _month;
	int _day;
};


istream& operator>>(istream& _cin, Date& d)
{
	_cin >> d._year >> d._month >> d._day;

	return _cin;
}

ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

void Print()
{
	Time t(11,11,30);
	t._second = 32;


	Date d;
	d._year = 2019;
}

int main()
{
	Date d(2019, 7, 29);
	d.PrintDate();

	cout << d << endl;
	
	cin >> d;

	cout << d << endl;
	// d << cout;
	return 0;
}
#endif


#if 0
class Time
{
	friend class Date;
public:
	Time(int hour, int minute, int second)
		: _hour(hour)
		, _minute(hour)
		, _second(second)
	{}

private:
	int _hour;
	int _minute;
	int _second;
};

class Date
{
public:
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
		, _t(0,0,0)
	{}

	void PrintDate()
	{
		cout << _year << "-" << _month << "-" << _day << endl;
		cout << _t._hour << ":" << _t._minute << ":" << _t._second<<endl;
	}

private:
	int _year;
	int _month;
	int _day;
	Time _t;
};

int main()
{
	return 0;
}
#endif

#if 0
class A
{
	class B
	{
	public:
		B(int b)
			: _b(b)
		{}

		void TestFunc()
		{
			// �ڲ������ⲿ�����Ԫ�ࣺ�������ڲ����з����ⲿ���˽�еĳ�Ա
			A a(10);
			a._a = 10;


			// �ⲿ���еľ�̬��Ա�����൱�����ڲ����ȫ�ֱ���
			_c = 10;
		}

	private:
		int _b;
	};

public:
	A(int a)
		: _a(a)
		, _b(0)
	{
		// �������ⲿ���з����ڲ����˽�еĳ�Ա
		//_b._b = 10;
	}

private:
	int _a;
	static int _c;
	B _b;
};

int A::_c = 0;

int main()
{
	cout << sizeof(A) << endl;
	return 0;
}
#endif


class Date
{
	friend ostream& operator<<(ostream& _cout, const Date& d);
public:
	// һ��Ҫ������ڵĺϷ���
	Date(int year = 1900, int month = 1, int day = 1)
		: _year(year)
		, _month(month)
		, _day(day)
	{
		if (!(year > 0 &&
			(month > 0 && month < 13) &&
			(day > 0 && day <= GetDaysOfMonth(year, month))))
		{
			_year = 1900;
			_month = 1;
			_day = 1;
		}
	}

	bool IsLeapYear(int year)
	{
		if (0 == year % 4 && 0 != year % 100 ||
			0 == year % 400)
		{
			return true;
		}
		

		return false;
	}

	Date(const Date& d)
		: _year(d._year)
		, _month(d._month)
		, _day(d._day)
	{}

	Date& operator=(const Date& d)
	{
		if (this != &d)
		{
			_year = d._year;
			_month = d._month;
			_day = d._day;
		}

		return *this;
	}

	// +���ܸı����Ҳ�����������
	// 2019 7 30 + (-100)
	// 2019 7 30 - 100
	Date operator+(int days)
	{
		if (days < 0)
		{
			return *this - (0 - days);
		}

		Date temp(*this);
		temp._day += days;

		// ������_day�Ƿ�
		int daysOfMonth = 0;
		while (temp._day > (daysOfMonth = GetDaysOfMonth(temp._year, temp._month)))
		{
			temp._day -= daysOfMonth;
			temp._month += 1;
			if (temp._month > 12)
			{
				temp._year += 1;
				temp._month = 1;
			}
		}

		return temp;
	}

	Date operator-(int days)
	{
		if (days < 0)
		{
			return *this + (0 - days);
		}

		Date temp(*this);
		temp._day -= days;

		// ���temp�Ƿ�Ϊ�Ϸ�����
		while (temp._day <= 0)
		{
			temp._month -= 1;
			if (0 == temp._month)
			{
				temp._year -= 1;
				temp._month = 12;
			}

			temp._day += GetDaysOfMonth(temp._year, temp._month);
		}

		return temp;
	}

	//
	int operator-(const Date& d)const
	{
		Date minDate(*this);
		Date maxDate(d);

		// ��ȡ���������е���Сֵ
		if (minDate > maxDate)
		{
			minDate = d;
			maxDate = *this;
		}

		int count = 0;
		while (minDate != maxDate)
		{
			count++;
			++minDate;
		}

		return count;
	}

	// ǰ��++
	Date& operator++()
	{
		*this = *this + 1;
		return *this;
	}

	// ����++
	Date operator++(int)
	{
		Date temp(*this);
		*this = *this + 1;
		return temp;
	}

	// ǰ��--
	Date& operator--()
	{
		*this = *this - 1;
		return *this;
	}

	// ����++
	Date operator--(int)
	{
		Date temp(*this);
		*this = *this - 1;
		return temp;
	}

	bool operator>(const Date& d)const
	{
		return _year > d._year ||
			   _year == d._year && _month > d._month ||
			   _year == d._year && _month == d._month && _day > d._day;
	}

	bool operator==(const Date& d)const
	{
		return _year == d._year &&
			   _month == d._month &&
			   _day == d._day;
	}

	bool operator!=(const Date& d)const
	{
		return !(*this == d);
	}

	bool operator<(const Date& d)const
	{
		return _year < d._year ||
			_year == d._year && _month < d._month ||
			_year == d._year && _month == d._month && _day < d._day;
	}

	int GetDaysOfMonth(int year, int month)
	{
		int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (2 == month && IsLeapYear(year))
		{
			days[month] += 1;
		}

		return days[month];
	}

private:
	int _year;
	int _month;
	int _day;
};


ostream& operator<<(ostream& _cout, const Date& d)
{
	_cout << d._year << "-" << d._month << "-" << d._day;
	return _cout;
}

int main()
{
	Date d1(2019, 7, 30);
	Date d2(2020, 1, 1);
	cout << d2 - d1 << endl;

	d1 = d1 - 100;
	cout << d1 << endl;

	d1 = d1 + 10000;   // 99999
	cout << d1 << endl;
	return 0;
}


