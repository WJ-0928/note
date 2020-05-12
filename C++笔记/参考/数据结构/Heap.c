#include "Heap.h"
#include <malloc.h>
#include <assert.h>
#include <string.h>

int Less(HPDataType left, HPDataType right)
{
	return left < right;
}

int Greater(HPDataType left, HPDataType right)
{
	return left > right;
}

void Swap(int* left, int* right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}

void AdjustDown(HPDataType* array, int size, int parent, PFC pFC)
{
	int child = parent * 2 + 1;

	while (child < size)
	{
		// 找左右孩子中最小的孩子
		if (child + 1 < size && pFC(array[child+1], array[child]))
		{
			child += 1;
		}

		// 检测双亲是否满足情况
		if (pFC(array[child], array[parent]))
		{
			Swap(&array[parent], &array[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}

void AdjustUP(HPDataType* array, int size, int child)
{
	int parent = ((child - 1) >> 1);

	while (child)
	{
		if (array[child] > array[parent])
		{
			Swap(&array[parent], &array[child]);
			child = parent;
			parent = ((child - 1) >> 1);
		}
		else
			return;
	}
}

void CreateHeap(Heap* hp, HPDataType* array, int size, PFC pFC)
{
	int root = -1;
	hp->_array = malloc(sizeof(HPDataType)*size);
	assert(hp);
	hp->_capacity = size;
	hp->_size = size;

	hp->_pFC = pFC;

	memcpy(hp->_array, array, size* sizeof(HPDataType));

	// 找倒数第一个非叶子节点
	root = (size - 2) / 2;
	for (; root >= 0; --root)
	{
		AdjustDown(hp->_array, size, root, pFC);
	}
}

void CheckCapacity(Heap* hp)
{
	if (hp->_size == hp->_capacity)
	{
		int capacity = 2 * hp->_capacity;
		HPDataType* pTemp = (HPDataType*)malloc(capacity*sizeof(HPDataType));
		if (NULL == pTemp)
			assert(0);

		memcpy(pTemp, hp->_array, hp->_size*sizeof(HPDataType));

		free(hp->_array);

		hp->_array = pTemp;
		hp->_capacity = capacity;
	}
}

void InsertHeap(Heap* hp, HPDataType data)
{
	CheckCapacity(hp);

	hp->_array[hp->_size++] = data;
	AdjustUP(hp->_array, hp->_size, hp->_size - 1);
}

void EraseHeap(Heap* hp)
{
	if (EmptyHeap(hp))
		return;

	Swap(&hp->_array[0], &hp->_array[hp->_size - 1]);
	hp->_size -= 1;
	AdjustDown(hp->_array, hp->_size, 0, hp->_pFC);
}

HPDataType TopHeap(Heap* hp)
{
	assert(!EmptyHeap(hp));
	return hp->_array[0];
}

int  SizeHeap(Heap* hp)
{
	assert(hp);
	return hp->_size;
}

int  EmptyHeap(Heap* hp)
{
	assert(hp);
	return 0 == hp->_size;
}

void DestroyHeap(Heap* hp)
{
	if (hp->_array)
	{
		free(hp->_array);
		hp->_capacity = 0;
		hp->_size = 0;
	}
}

void HeapAdjust(int* array, int size, int parent)
{
	// 默认parent的左孩子比较小
	int child = parent * 2 + 1;

	while (child < size)
	{
		// 找左右孩子中最小的孩子
		if (child+1 < size && array[child + 1] < array[child])
			child += 1;

		// 检测parent是否满足堆的性质
		if (array[parent] > array[child])
		{
			Swap(&array[parent], &array[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
		{
			return;
		}
	}
}

void HeapSort(int* array, int size)
{
	// 1. 建堆---O(NlogN)
	int root = ((size - 2) >> 1);
	for (; root >= 0; --root)
		HeapAdjust(array, size, root);


	// 2. 排序--->堆删除原理O(NlogN)
	for (int last = size-1; last >= 0; last--)
	{
		Swap(&array[0], &array[last]);
		HeapAdjust(array, last, 0);
	}
}

#include <stdio.h>

void TestHeap()
{
	Heap hp;
	int array[] = {9,0,1,7,8,2,5,3,6,4};
	CreateHeap(&hp, array, sizeof(array)/sizeof(array[0]), Greater);
	EraseHeap(&hp);
	printf("%d\n", TopHeap(&hp));

	InsertHeap(&hp, 0);
	printf("%d\n", TopHeap(&hp));
	printf("%d\n", SizeHeap(&hp));
	DestroyHeap(&hp);
}
