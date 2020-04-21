#pragma once
#include "Common.h"

#include "BitSet.hpp"

// N代表底层底层位图中的比特位
template<class T, size_t N = 10, class HF1 = Str2Int1, class HF2 = Str2Int2, class HF3 = Str2Int3
	                      , class HF4 = Str2Int4, class HF5 = Str2Int5>
class BloomFilter
{
public:
	BloomFilter()
		: _bf()
		, _size(0)
	{}

	bool Insert(const T& data)
	{
		size_t index = HF1()(data)%N;
		_bf.set(index);

		index = HF2()(data) % N;
		_bf.set(index);

		index = HF3()(data) % N;
		_bf.set(index);

		index = HF4()(data) % N;
		_bf.set(index);

		index = HF5()(data) % N;
		_bf.set(index);

		++_size;
		return true;
	}

	bool IsIn(const T& data)
	{
		// 只要5个哈希函数中有一个说数据不出在(对应比特位为0),则该数据一定不出在
		size_t index = HF1()(data) % N;
		if (!_bf.test(index))
			return false;

		index = HF2()(data) % N;
		if (!_bf.test(index))
			return false;

		index = HF3()(data) % N;
		if (!_bf.test(index))
			return false;

		index = HF4()(data) % N;
		if (!_bf.test(index))
			return false;

		index = HF5()(data) % N;
		if (!_bf.test(index))
			return false;

		// 说明该数据可能存在
		return true;
	}

	size_t size()const
	{
		return _size;
	}

private:
	bite::bitset<N> _bf;
	size_t _size;  // 有效元素的个数
};


// 维护黑名单：vector-->string

// 维护了一份黑名单：
void TestBloomFilter()
{
	BloomFilter<string, 100> bf;
	bf.Insert("欧阳锋");
	bf.Insert("欧阳克");
	bf.Insert("Peter");
	bf.Insert("金轮法王");

	if (bf.IsIn("杨过"))
	{
		cout << "坏人" << endl;
	}
	else
	{
		cout << "大侠" << endl;
	}

	if (bf.IsIn("欧阳克"))
	{
		cout << "坏人" << endl;
	}
	else
	{
		cout << "大侠" << endl;
	}
}