#pragma once
#include "Common.h"

#include "BitSet.hpp"

// N����ײ�ײ�λͼ�еı���λ
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
		// ֻҪ5����ϣ��������һ��˵���ݲ�����(��Ӧ����λΪ0),�������һ��������
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

		// ˵�������ݿ��ܴ���
		return true;
	}

	size_t size()const
	{
		return _size;
	}

private:
	bite::bitset<N> _bf;
	size_t _size;  // ��ЧԪ�صĸ���
};


// ά����������vector-->string

// ά����һ�ݺ�������
void TestBloomFilter()
{
	BloomFilter<string, 100> bf;
	bf.Insert("ŷ����");
	bf.Insert("ŷ����");
	bf.Insert("Peter");
	bf.Insert("���ַ���");

	if (bf.IsIn("���"))
	{
		cout << "����" << endl;
	}
	else
	{
		cout << "����" << endl;
	}

	if (bf.IsIn("ŷ����"))
	{
		cout << "����" << endl;
	}
	else
	{
		cout << "����" << endl;
	}
}