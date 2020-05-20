#include "SeqList.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>


void SeqListInit(PSeqList ps)
{
	// 先检测参数的合法性
	assert(ps);

	// 功能
	// 默认情况：顺序中可以存放3个元素
	ps->_array = (DataType*)malloc(sizeof(DataType)* 3);
	if (NULL == ps->_array)
	{
		assert(0);   // 调试宏
		return;
	}

	ps->_capacity = 3;
	ps->_size = 0;
}

void SeqListDestroy(PSeqList ps)
{
	assert(ps);
	if (ps->_array)
	{
		free(ps->_array);
		ps->_array = NULL;
		ps->_capacity = 0;
		ps->_size = 0;
	}
}

void _CheckCapacity(PSeqList ps)
{
	assert(ps);
	if (ps->_size == ps->_capacity)
	{
		int newCapacity = ps->_capacity * 2;
		
		// 开辟新空间
		DataType* pTemp = (DataType*)malloc(sizeof(DataType)*newCapacity);
		if (NULL == pTemp)
		{
			assert(0);
			return;
		}

		// 拷贝元素
		memcpy(pTemp, ps->_array, ps->_size*sizeof(DataType));

		// 释放旧空间
		free(ps->_array);
		ps->_array = pTemp;
		ps->_capacity = newCapacity;
	}
}

// 尾插
void SeqListPushBack(PSeqList ps, DataType data)
{
	/*
	assert(ps);
	// 顺序表满，扩容
	 _CheckCapacity(ps);
	ps->_array[ps->_size] = data;
	ps->_size++;
	*/

	assert(ps);
	SeqListInsert(ps, ps->_size, data);
}


// 尾删
void SeqListPopBack(PSeqList ps)
{
	/*
	assert(ps);
	if (0 == ps->_size)
		return;

	ps->_size--;
	*/

	assert(ps);
	SeqListErase(ps, ps->_size - 1);
}

// 头插
void SeqListPushFront(PSeqList ps, DataType data)
{
	assert(ps);

	// 检测空间释放充足
	 _CheckCapacity(ps);

	// 将顺序表中有效元素整体向后搬移一个位置
	for (int i = ps->_size - 1; i >= 0; --i)
	{
		ps->_array[i+1] = ps->_array[i];
	}

	/*
	for (int i = ps->_size; i > 0; --i)
	{
	    ps->_array[i] = ps->_array[i-1];
	}
	*/

	// 插入元素
	ps->_array[0] = data;
	ps->_size++;
}

// 头删
void SeqListPopFront(PSeqList ps)
{
	assert(ps);
	if (0 == ps->_size)
		return;

	// i: 元素被搬移到位置的下标
	for (int i = 0; i < ps->_size-1; ++i)
	{
		ps->_array[i] = ps->_array[i + 1];
	}

	ps->_size--;
}

// 任意位置插入
void SeqListInsert(PSeqList ps, int pos, DataType data)
{
	assert(ps);
	if (pos < 0 || pos > ps->_size)
	{
		printf("插入元素位置非法\n");
		return;
	}

	// 检测容量
	 _CheckCapacity(ps);

	for (int i = ps->_size - 1; i >= pos; --i)
	{
		ps->_array[i+1] = ps->_array[i];
	}

	ps->_array[pos] = data;
	ps->_size++;
}

// 任意位置删除
void SeqListErase(PSeqList ps, int pos)
{
	assert(ps);
	if (pos < 0 || pos >= ps->_size)
	{
		printf("删除元素位置非法\n");
		return;
	}

	for (int i = pos; i < ps->_size - 1; ++i)
	{
		ps->_array[i] = ps->_array[i + 1];
	}

	ps->_size--;
}

int SeqListFind(PSeqList ps, DataType data)
{
	assert(ps);
	for (int i = 0; i < ps->_size; ++i)
	{
		if (ps->_array[i] == data)
			return i;
	}

	return -1;
}

// 移除顺序表中第一个值为data的元素
void SeqListRemove(PSeqList ps, DataType data)
{
	SeqListErase(ps, SeqListFind(ps, data));
}

// 移除顺序表中所有值为data的元素
void SeqListRemoveAll(PSeqList ps, DataType data)
{
	/*
	O(N*M)
	int pos = -1;
	while (-1 != (pos = SeqListFind(ps, data)))
	{
		SeqListErase(ps, pos);
	}
	*/

	/*
	int i = 0;
	for (; i < ps->_size; ++i)
	{
		if (ps->_array[i] == data)
		{
			SeqListErase(ps, i);
		}
	}
	*/

	int count = 0;   // 记录待删除元素的个数
	for (int i = 0; i < ps->_size; ++i)
	{
		if (ps->_array[i] == data)
			count++;
		else
			ps->_array[i - count] = ps->_array[i];
	}

	ps->_size -= count;
}

// 获取顺序表有效元素个数
int SeqListSize(PSeqList ps)
{
	assert(ps);
	return ps->_size;
}

// 获取顺序表的容量
int SeqListCapacity(PSeqList ps)
{
	assert(ps);
	return ps->_capacity;
}

// 检测顺序表是否为空
int SeqListEmpty(PSeqList ps)
{
	assert(ps);
	return 0 == ps->_size;
}

// 获取顺序表中第一个元素
DataType SeqListFront(PSeqList ps)
{
	assert(ps);
	return ps->_array[0];
}

// 获取顺序表中最后一个元素
DataType SeqListBack(PSeqList ps)
{
	assert(ps);
	return ps->_array[ps->_size-1];
}



///////////////////////////////////////////
// test
void PrintSeqList(PSeqList ps)
{
	assert(ps);
	for (int i = 0; i < ps->_size; ++i)
	{
		printf("%d ", ps->_array[i]);
	}
	printf("\n");
}
