#include <iostream>
using namespace std;

#include <string>
#include <map>

#if 0
void TestMap1()
{
	map<string, string> m;
	m.insert(pair<string, string>("����", "������"));
	m.insert(make_pair("�ֳ�", "����ͷ"));
	m.insert(make_pair("�ν�", "��ʱ��"));
	m.insert(make_pair("�����", "ĸҹ��"));

	cout << m.size() << endl;
	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "<--->" << it->second << endl;
		++it;
	}
	cout << endl;

	m.insert(make_pair("����", "��ţ"));
	for (auto& e : m)
		cout << e.first << "<--->" << e.second << endl;
	cout << endl;

	cout << m["�ν�"] << endl;
	cout << m["����"] << endl;
	m["³��"] = "������";
	// <"³��"��"">
}
#endif

#if 0
// ����key����
void TestMap2()
{
	map<int, int> m;
	int array[] = { 5, 1, 0, 9, 7, 3, 6, 4, 2, 8 };
	for (size_t i = 0; i < 10; ++i)
		m.insert(make_pair(array[i], i));

	for (auto e : m)
		cout << e.first << "--->" << e.second << endl;
}

int main()
{
	//TestMap1();
	TestMap2();
	return 0;
}
#endif

#if 0
int main()
{
	map<string, string> m;
	m.insert(pair<string, string>("����", "������"));
	m.insert(make_pair("�ֳ�", "����ͷ"));
	m.insert(make_pair("�ν�", "��ʱ��"));
	m.insert(make_pair("�����", "ĸҹ��"));

	cout << m.count("�ν�") << endl;
	cout << m.count("³��") << endl;

	auto it = m.find("�ν�");

	// map�е�key�����޸�
	//it->first = "����";   // ����ʧ��

	// ���һ��Ҫ�ģ���ɾ����key�������²���
	pair<string, string> data("����", it->second);
	if (it != m.end())
		m.erase(it);

	m.insert(data);

	m.clear();
	return 0;
}
#endif

#if 0
#include <functional>

int main()
{
	// map�е�Ԫ��Ĭ�ϰ���less(С��)��ʽ���бȽ�---����
	map<int, int> m1;
	int array[] = { 5, 1, 0, 9, 7, 3, 6, 4, 2, 8 };
	for (size_t i = 0; i < 10; ++i)
		m1.insert(make_pair(array[i], i));

	for (auto e : m1)
		cout << e.first << "--->" << e.second << endl;

	map<int, int, greater<int>> m2;
	for (size_t i = 0; i < 10; ++i)
		m2.insert(make_pair(array[i], i));

	for (auto e : m2)
		cout << e.first << "--->" << e.second << endl;
	return 0;
}
#endif

#if 0
// set---���ԣ����� + ȥ��
#include <set>

int main()
{
	int array[] = { 5, 2, 9, 0, 8, 1, 7, 3, 6, 4, 5, 2, 9, 0, 8, 1, 7, 3, 6, 4 };
	set<int> s;
	for (auto e : array)
		s.insert(e);

	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return 0;
}
#endif

#if 0
int main()
{
	int array[] = { 5, 2, 9, 0, 8, 1, 7, 3, 6, 4, 5, 2, 9, 0, 8, 1, 7, 3, 6, 4 };
	multimap<int,int> s;
	for (auto e : array)
		s.insert(make_pair(e,e));

	auto it = s.begin();
	while (it != s.end())
	{
		cout << it->first << "--->"<<it->second<<endl;
		++it;
	}
	cout << endl;
	return 0;
}
#endif

#if 0
// ���ԣ�����
#include <set>

int main()
{
	int array[] = { 5, 2, 9, 0, 8, 1, 7, 3, 6, 4, 5, 2, 9, 0, 8, 1, 7, 3, 6, 4 };
	multiset<int> s;
	for (auto e : array)
		s.insert(e);

	auto it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
	return 0;
}
#endif

#if 0
//#include "BinarySearchTree.hpp"
//#include "AVLTree.h"
//#include "RBTree.hpp"
//#include "Map.hpp"
#include "Set.hpp"

int main()
{
	// TestBSTree();
	//TestAVLTree();
	//TestRBTree();

	//TestMap();

	TestSet();
	return 0;
}
#endif

#if 0
class A{
	void test(float a)
	{ cout << "1"; }
};
class B :public A{
	void test(int b){ cout << "2"; }
};

int main()
{
	A *a = new A;
	B *b = new B;
	a = b;
	a.test(1.1);
	return 0;
}
#endif

#if 0
// ���
// A::func(val=1)
// A::test()
class A
{
public:
	virtual void func(int val = 1)
	{
		std::cout << "A->" << val << std::endl;
	}
	virtual void test()
	{
		this->func();
	}
};

// ���:
// B::func(val=0)
// A::test()
class B : public A
{
public:
	void func(int val = 0)
	{
		std::cout << "B->" << val << std::endl;
	}
};


#include <string>

int main()
{
	string str;
	while (cin >> str)
	{
		int count[256] = { 0 };
		for (auto e : str)
		{
			count[e]++;
			if (count[e] == 1)
				cout << e;
		}

		//cout << endl;
	}
	return 0;
}
#endif

#if 0
#include "HashBucket.hpp"

int main()
{
	string s1("1234");
	//int a = (int)s1;
	cout << atoi(s1.c_str()) << endl;
	cout << (int)s1.c_str() << endl;

	TestHashBucket1();
	TestHashBucket2();
	return 0;
}
#endif

//#include "UnorderedMap.hpp"

//#include "BitSet.hpp"

#include "BloomFilter.hpp"

int main()
{
	//TestUnorderedMap1();
	//TestUnorderedMap2();
	//TestBitset1();
	//TestBitset2();

	TestBloomFilter();
	return 0;
}



