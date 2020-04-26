#pragma once

#include "RBTree.hpp"


namespace bite
{
	template<class K>
	class set
	{
		typedef K ValueType;

		struct KeyOfValue
		{
			const K& operator()(const ValueType& data)
			{
				return data;
			}
		};

		typedef RBTree<ValueType, KeyOfValue> RBTree;
		typename typedef RBTree::iterator iterator;
	public:
		set()
			: t()
		{}

		////////////////////////////
		// iterator
		iterator begin()
		{
			return t.Begin();
		}

		iterator end()
		{
			return t.End();
		}
		//////////////////////////////
		// capacity
		bool empty()const
		{
			return t.Empty();
		}

		size_t size()const
		{
			return t.Size();
		}

		///////////////////////////
		// modify
		pair<iterator, bool> insert(const ValueType& data)
		{
			return t.Insert(data);
		}

		void clear()
		{
			t.Clear();
		}

		iterator find(const K& key)
		{
			return t.Find(key);
		}

	private:
		RBTree t;
	};
}

void TestSet()
{
	int array[] = {1,2,3,4,5,6,7,8,9,0,0,9,8,7,6,5,4,3,2,1};
	bite::set<int> s;
	for (auto e : array)
		s.insert(e);

	cout << s.size() << endl;

	for (auto e : s)
		cout << e << " ";
	cout << endl;
}