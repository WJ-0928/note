#pragma once
#include "RBTree.hpp"

namespace bite
{
	template<class K, class V>
	class map
	{
		
		typedef pair<K, V> ValueType;

		struct KeyOfValue
		{
			const K& operator()(const ValueType& data)
			{
				return data.first;
			}
		};

		typedef RBTree<ValueType, KeyOfValue> RBTree;
		typename typedef RBTree::iterator iterator;
	public:
		map()
			: t()
		{}

		/////////////////////////////
		// iterator
		iterator begin()
		{
			return t.Begin();
		}

		iterator end()
		{
			return t.End();
		}

		///////////////////////////////
		// capacity
		bool empty()const
		{
			return t.Empty();
		}

		size_t size()const
		{
			return t.Size();
		}

		///////////////////////////////
		// access
		V& operator[](const K& key)
		{
			return (*(t.Insert(pair<K, V>(key, V())).first)).second;
		}

		///////////////////////////////
		// modify
		pair<iterator, bool> insert(const ValueType& data)
		{
			return t.Insert(data);
		}

		void clear()
		{
			return t.clear();
		}

		iterator find(const K& key)
		{
			return t.Find(pair<K,V>(key, V()));
		}
	private:
		RBTree t;
	};
}

#include <string>

void TestMap()
{
	bite::map<string, string> m;

	m.insert(pair<string, string>("�ν�", "��ʱ��"));
	m.insert(make_pair("�ν�", "��ʱ��"));
	m["����"] = "������";
	cout << m.size() << endl;

	auto it = m.begin();
	while (it != m.end())
	{
		cout << it->first << "--->" << it->second << endl;
		++it;
	}

	m.insert(make_pair("����", "��ţ"));
	cout << m.size() << endl;

	it = m.find("�ֳ�");
	if (it != m.end())
	{
		cout << it->second << endl;
	}
	else
	{
		cout << "�޴���" << endl;
	}
}