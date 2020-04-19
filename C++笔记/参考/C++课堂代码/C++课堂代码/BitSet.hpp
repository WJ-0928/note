#pragma once


#include <assert.h>

#include <vector>
namespace bite
{
	// N 代表
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

		// 将第which个比特位置1
		void set(size_t which)
		{
			assert(which < _totalBite);

			size_t index = (which >> 3);
			size_t pos = which % 8;

			_bst[index] |= (1 << pos);
			++_size;
		}

		// 将第which个比特置0
		void reset(size_t which)
		{
			assert(which < _totalBite);

			size_t index = (which >> 3);
			size_t pos = which % 8;

			_bst[index] &= (~(1 << pos));
			--_size;
		}

		// 检测which对应的比特位是否为1
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

		// 返回为1的比特位个数
		size_t count()const
		{
			return _size;
		}

	private:
		std::vector<unsigned char> _bst;
		size_t _size;  // 为1的比特位的个数 --- 如果没有_size的成员，如何快速返回bitset中为1的比特位总的个数？
		size_t _totalBite;  // 总的比特为个数
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
		cout << "是1" << endl;
	else
		cout << "是0" << endl;

	t.reset(50);
	cout << t.count() << endl;

	if (t.test(50))
		cout << "是1" << endl;
	else
		cout << "是0" << endl;
}

void TestBitset2()
{
	bite::bitset<100> t;
	t.set(1);
	t.set(50);
	cout << t.size() << endl;
	cout << t.count() << endl;

	if (t.test(50))
		cout << "是1" << endl;
	else
		cout << "是0" << endl;

	t.reset(50);
	cout << t.count() << endl;

	if (t.test(50))
		cout << "是1" << endl;
	else
		cout << "是0" << endl;
}
