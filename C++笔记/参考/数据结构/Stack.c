#include "Stack.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>

void _CheckCapacity(Stack* ps)
{
	assert(ps);
	if (ps->_top == ps->_capacity)
	{
		// �����¿ռ�
		int newcap = ps->_capacity * 2;
		SDataType* pTemp = (SDataType*)malloc(sizeof(SDataType)*newcap);
		if (NULL == pTemp)
		{
			assert(0);
			return;
		}

		// ����Ԫ��
		// memcpy
		memcpy(pTemp, ps->_array, ps->_top*sizeof(SDataType));

		// for����Ԫ��
		//for (int i = 0; i < ps->_top; ++i)
		//	pTemp[i] = ps->_array[i];

		// �ͷžɿռ�
		free(ps->_array);
		ps->_array = pTemp;
		ps->_capacity = newcap;
	}
}

void StackInit(Stack* ps)
{
	assert(ps);
	ps->_array = (SDataType*)malloc(sizeof(SDataType)* 3);
	if (NULL == ps->_array)
	{
		assert(0);
		return;
	}

	ps->_capacity = 3;
	ps->_top = 0;
}

void StackPush(Stack* ps, SDataType data)
{
	assert(ps);
	_CheckCapacity(ps);
	ps->_array[ps->_top] = data;
	ps->_top++;
}

void StackPop(Stack* ps)
{
	assert(ps);
	if (0 == ps->_top)
		return;

	ps->_top--;
}

SDataType StackTop(Stack* ps)
{
	assert(ps);
	return ps->_array[ps->_top - 1];
}

int StackSize(Stack* ps)
{
	assert(ps);
	return ps->_top;
}

int StackEmpty(Stack* ps)
{
	assert(ps);
	return 0 == ps->_top;
}

void StackDestroy(Stack* ps)
{
	assert(ps);
	if (ps->_array)
	{
		free(ps->_array);
		ps->_array = NULL;
		ps->_capacity = 0;
		ps->_top = 0;
	}
}