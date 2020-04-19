#pragma once


#include <assert.h>

#include <vector>
namespace bite
{
	// N ����
	template<size_t N>
	class bitset
	{
	public:
		bitset()
			: _size(0)
			, _totalBite(N)
		{
			_bst.resize((N >> 3) + 1);
		}

		// ����which������λ��1
		void set(size_t which)
		{
			assert(which < _totalBite);

			size_t index = (which >> 3);
			size_t pos = which % 8;

			_bst[index] |= (1 << pos);
			++_size;
		}

		// ����which��������0
		void reset(size_t which)
		{
			assert(which < _totalBite);

			size_t index = (which >> 3);
			size_t pos = which % 8;

			_bst[index] &= (~(1 << pos));
			--_size;
		}

		// ���which��Ӧ�ı���λ�Ƿ�Ϊ1
		bool test(size_t which)
		{
			assert(which < _totalBite);

			size_t index = (which >> 3);
			size_t pos = which % 8;

			return  _bst[index] & (1 << pos);
		}

		size_t size()const
		{
			return _totalBite;
		}

		// ����Ϊ1�ı���λ����
		size_t count()const
		{
			return _size;
		}

	private:
		std::vector<unsigned char> _bst;
		size_t _size;  // Ϊ1�ı���λ�ĸ��� --- ���û��_size�ĳ�Ա����ο��ٷ���bitset��Ϊ1�ı���λ�ܵĸ�����
		size_t _totalBite;  // �ܵı���Ϊ����
	};
}




#include <bitset>
#include <iostream>
using namespace std;

void TestBitset1()
{
	std::bitset<100> t;
	t.set(1);
	t.set(50);
	cout << t.size() << endl;
	cout << t.count() << endl;

	if (t.test(50))
		cout << "��1" << endl;
	else
		cout << "��0" << endl;

	t.reset(50);
	cout << t.count() << endl;

	if (t.test(50))
		cout << "��1" << endl;
	else
		cout << "��0" << endl;
}

void TestBitset2()
{
	bite::bitset<100> t;
	t.set(1);
	t.set(50);
	cout << t.size() << endl;
	cout << t.count() << endl;

	if (t.test(50))
		cout << "��1" << endl;
	else
		cout << "��0" << endl;

	t.reset(50);
	cout << t.count() << endl;

	if (t.test(50))
		cout << "��1" << endl;
	else
		cout << "��0" << endl;
}
