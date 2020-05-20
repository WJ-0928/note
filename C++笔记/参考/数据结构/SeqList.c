#include "SeqList.h"
#include <malloc.h>
#include <assert.h>
#include <stdio.h>


void SeqListInit(PSeqList ps)
{
	// �ȼ������ĺϷ���
	assert(ps);

	// ����
	// Ĭ�������˳���п��Դ��3��Ԫ��
	ps->_array = (DataType*)malloc(sizeof(DataType)* 3);
	if (NULL == ps->_array)
	{
		assert(0);   // ���Ժ�
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
		
		// �����¿ռ�
		DataType* pTemp = (DataType*)malloc(sizeof(DataType)*newCapacity);
		if (NULL == pTemp)
		{
			assert(0);
			return;
		}

		// ����Ԫ��
		memcpy(pTemp, ps->_array, ps->_size*sizeof(DataType));

		// �ͷžɿռ�
		free(ps->_array);
		ps->_array = pTemp;
		ps->_capacity = newCapacity;
	}
}

// β��
void SeqListPushBack(PSeqList ps, DataType data)
{
	/*
	assert(ps);
	// ˳�����������
	 _CheckCapacity(ps);
	ps->_array[ps->_size] = data;
	ps->_size++;
	*/

	assert(ps);
	SeqListInsert(ps, ps->_size, data);
}


// βɾ
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

// ͷ��
void SeqListPushFront(PSeqList ps, DataType data)
{
	assert(ps);

	// ���ռ��ͷų���
	 _CheckCapacity(ps);

	// ��˳�������ЧԪ������������һ��λ��
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

	// ����Ԫ��
	ps->_array[0] = data;
	ps->_size++;
}

// ͷɾ
void SeqListPopFront(PSeqList ps)
{
	assert(ps);
	if (0 == ps->_size)
		return;

	// i: Ԫ�ر����Ƶ�λ�õ��±�
	for (int i = 0; i < ps->_size-1; ++i)
	{
		ps->_array[i] = ps->_array[i + 1];
	}

	ps->_size--;
}

// ����λ�ò���
void SeqListInsert(PSeqList ps, int pos, DataType data)
{
	assert(ps);
	if (pos < 0 || pos > ps->_size)
	{
		printf("����Ԫ��λ�÷Ƿ�\n");
		return;
	}

	// �������
	 _CheckCapacity(ps);

	for (int i = ps->_size - 1; i >= pos; --i)
	{
		ps->_array[i+1] = ps->_array[i];
	}

	ps->_array[pos] = data;
	ps->_size++;
}

// ����λ��ɾ��
void SeqListErase(PSeqList ps, int pos)
{
	assert(ps);
	if (pos < 0 || pos >= ps->_size)
	{
		printf("ɾ��Ԫ��λ�÷Ƿ�\n");
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

// �Ƴ�˳����е�һ��ֵΪdata��Ԫ��
void SeqListRemove(PSeqList ps, DataType data)
{
	SeqListErase(ps, SeqListFind(ps, data));
}

// �Ƴ�˳���������ֵΪdata��Ԫ��
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

	int count = 0;   // ��¼��ɾ��Ԫ�صĸ���
	for (int i = 0; i < ps->_size; ++i)
	{
		if (ps->_array[i] == data)
			count++;
		else
			ps->_array[i - count] = ps->_array[i];
	}

	ps->_size -= count;
}

// ��ȡ˳�����ЧԪ�ظ���
int SeqListSize(PSeqList ps)
{
	assert(ps);
	return ps->_size;
}

// ��ȡ˳��������
int SeqListCapacity(PSeqList ps)
{
	assert(ps);
	return ps->_capacity;
}

// ���˳����Ƿ�Ϊ��
int SeqListEmpty(PSeqList ps)
{
	assert(ps);
	return 0 == ps->_size;
}

// ��ȡ˳����е�һ��Ԫ��
DataType SeqListFront(PSeqList ps)
{
	assert(ps);
	return ps->_array[0];
}

// ��ȡ˳��������һ��Ԫ��
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
