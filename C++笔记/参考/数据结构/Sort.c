#include <stdio.h>
#include "Sort.h"
#include <assert.h>
#include <string.h>



void Swap(int* left, int* right)
{
	int temp = *left;
	*left = *right;
	*right = temp;
}

void PrintArray(int* array, int size)
{
	for (int i = 0; i < size; ++i)
		printf("%d ", array[i]);
	printf("\n");
}

// 时间复杂度：O(N^2)
// 空间复杂度：O(1)
// 稳定
// 适应场景：数据量比较小，接近有序
void InsertSort(int* array, int size)
{
	for (int i = 1; i < size; ++i)
	{
		int key = array[i];
		int end = i - 1;

		// 找待插入位置---O(N)
		while (end >= 0 && key < array[end])
		{
			array[end+1] = array[end];
			--end;
		}

		// 插入数据
		array[end+1] = key;
	}
}

// 时间复杂度：N^1.25 ~ 1.6N^1.25
// 空间复杂度：O(1)
// 稳定性：不稳定
// 场景：数据量大比较杂乱
void ShellSort(int* array, int size)
{
	int gap = size;  // 10-->4 2 1  
	while (gap > 1)
	{
		// gap /= 2;  gap: 取一系列素数
		gap = gap / 3 + 1;
		for (int i = gap; i < size; ++i)
		{
			int key = array[i];
			int end = i - gap;

			// 找待插入位置---O(N)
			while (end >= 0 && key < array[end])
			{
				array[end + gap] = array[end];
				end -= gap;
			}

			// 插入数据
			array[end + gap] = key;
		}

		//gap -= 1;
	}
}

// 稳定性：不稳定
// 时间复杂度：O(N^2)
// 空间复杂度: O(1)
void SelectSort(int* array, int size)
{
	// O(N)
	for (int i = 0; i < size-1; ++i)
	{
		// 标记最大元素的位置
		int maxPos = 0;
		// O(N)
		for (int j = 1; j < size - i; ++j)
		{
			if (array[j] > array[maxPos])
				maxPos = j;
		}

		if (maxPos != size - i - 1)
			Swap(&array[maxPos], &array[size - i - 1]);
	}
}

void SelectSortOP(int* array, int size)
{
	int begin = 0;
	int end = size - 1;

	while (begin < end)
	{
		int maxPos = begin;
		int minPos = begin;

		int idx = begin+1;
		while (idx <= end)
		{
			if (array[idx] > array[maxPos])
				maxPos = idx;

			if (array[idx] < array[minPos])
				minPos = idx;
			++idx;
		}

		if (maxPos != end)
			Swap(&array[maxPos], &array[end]);

		if (minPos == end)
			minPos = maxPos;

		if (minPos != begin)
			Swap(&array[minPos], &array[begin]);

		begin++;
		end--;
	}
}


void HeapAdjust(int* array, int size, int parent)
{
	int child = parent * 2 + 1;
	while (child < size)
	{
		// 找左右孩子中最大的
		if (child + 1 < size && array[child + 1] > array[child])
			child += 1;

		// 检测parent是否满足情况
		if (array[parent] < array[child])
		{
			Swap(&array[parent], &array[child]);
			parent = child;
			child = parent * 2 + 1;
		}
		else
			return;
	}
}


// 时间复杂度：O(NlogN)
// 空间复杂度：O(1)
// 稳定性：不稳定
void HeapSort(int* array, int size)
{
	// 1. 建堆---向下调整
	// 升序：大堆   降序：小堆
	int root = ((size - 2) >> 1);
	for (; root >= 0; --root)
		HeapAdjust(array, size, root);

	// 2. 排序---删除---向下调整
	int end = size - 1;
	while (end)
	{
		Swap(&array[0], &array[end]);
		HeapAdjust(array, end, 0);
		end--;
	}
}


// 稳定性：稳定
// 时间复杂度：O(N^2)
// 空间复杂度：O(1)
void BubbleSort(int* array, int size)
{
	for (int i = 0; i < size - 1; ++i)
	{
		int Ischange = 0;
		for (int j = 1; j < size - i; ++j)
		{
			if (array[j-1] > array[j])
			{
				Ischange = 1;
				Swap(&array[j-1], &array[j]);
			}
		}

		if (!Ischange)
			return;
	}
}

// 三数取中法
int GetIndexOfMid(int* array, int left, int right)
{
	int mid = left + ((right - left) >> 1);
	if (array[left] < array[right])
	{
		if (array[mid] < array[left])
			return left;
		else if (array[mid] > array[right])
			return right;
		else
			return mid;
	}
	else
	{
		if (array[mid] > array[left])
			return left;
		else if (array[mid] < array[right])
			return right;
		else
			return mid;
	}
}


// hoare
int Partion1(int* array, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = 0;
	int index = GetIndexOfMid(array, left, right - 1);
	Swap(&array[index], &array[right - 1]);
	key = array[end];

	while (begin < end)
	{
		// 从前往后找，找比基准值大的元素
		while (begin < end && array[begin] <= key)
			begin++;

		// 从后往前找，找比基准值小的元素
		while (begin < end && array[end] >= key)
			end--;

		if (begin < end)
			Swap(&array[begin], &array[end]);
	}

	if (begin != right)
		Swap(&array[begin], &array[right-1]);
	
	return begin;
}

// 挖坑法
int Partion2(int* array, int left, int right)
{
	int begin = left;
	int end = right - 1;
	int key = 0;
	int index = GetIndexOfMid(array, left, right - 1);
	Swap(&array[index], &array[right - 1]);
	key = array[end];

	while (begin < end)
	{
		while (begin < end && array[begin] <= key)
			++begin;

		if (begin < end)
		{
			array[end] = array[begin];
			end--;
		}

		while (begin < end && array[end] >= key)
			end--;

		if (begin < end)
		{
			array[begin] = array[end];
			begin++;
		}
	}

	array[begin] = key;
	return begin;
}


int Partion3(int* array, int left, int right)
{
	int cur = left;
	int prev = cur - 1;
	int key = 0;

	int index = GetIndexOfMid(array, left, right - 1);
	Swap(&array[index], &array[right - 1]);
	key = array[right-1];

	while (cur < right)
	{
		if (array[cur] < key && ++prev != cur)
			Swap(&array[cur], &array[prev]);

		++cur;
	}

	if (++prev != right - 1)
		Swap(&array[prev], &array[right - 1]);

	return prev;
}

//[left, right)
void QuickSort(int* array, int left, int right)
{
	if (right - left < 16)
		InsertSort(array, right - left);
	else
	{
		int div = Partion3(array, left, right);
		QuickSort(array, left, div);
		QuickSort(array, div + 1, right);
	}
}

#include "Stack.h"

void QuickSortNor(int* array, int size)
{
	int left = 0;
	int right = size;
	Stack s;
	StackInit(&s);
	StackPush(&s, right);
	StackPush(&s, left);

	while (!StackEmpty(&s))
	{
		left = StackTop(&s);
		StackPop(&s);

		right = StackTop(&s);
		StackPop(&s);

		int div = Partion3(array, left, right);

		// 保存右半部分数据的区间
		if (div+1 < right)
		{
			StackPush(&s, right);
			StackPush(&s, div + 1);
		}

		// 保存左半部分数据的区间
		if (left < div)
		{
			StackPush(&s, div);
			StackPush(&s, left);
		}
	}

	StackDestroy(&s);
}


void MergeData(int* array, int left, int mid, int right, int* temp)
{
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid;
	int end2 = right;
	int index = left;

	while (begin1 < end1 && begin2 < end2)
	{
		if (array[begin1] <= array[begin2])
			temp[index++] = array[begin1++];
		else
			temp[index++] = array[begin2++];
	}

	while (begin1 < end1)
		temp[index++] = array[begin1++];

	while (begin2 < end2)
		temp[index++] = array[begin2++];
}

void _MergeSort(int* array, int left, int right, int* temp)
{
	if (left + 1 < right)
	{
		int mid = left + ((right - left) >> 1);
		_MergeSort(array, left, mid, temp);
		_MergeSort(array, mid, right, temp);
		MergeData(array, left, mid, right, temp);
		memcpy(array+left, temp+left, (right - left)*sizeof(array[0]));
	}
}

#include <malloc.h>

void MergeSort(int* array, int size)
{
	int* temp = (int*)malloc(sizeof(array[0])*size);
	_MergeSort(array, 0, size, temp);
	free(temp);
}

void MergeSortNor(int* array, int size)
{
	int* temp = (int*)malloc(sizeof(array[0])*size);
	
	int gap = 1;
	while (gap < size)
	{
		for (int i = 0; i < size; i += 2 * gap)
		{
			int left = i;
			int mid = left + gap;
			int right = mid + gap;

			if (mid > size)
				mid = size;

			if (right > size)
				right = size;

			MergeData(array, left, mid, right, temp);
		}

		memcpy(array, temp, size*sizeof(array[0]));
		gap *= 2;
	}
	
	free(temp);
}

//////////////////////////////////////////////
// 非比较排序

// 时间复杂度：O(N)
// 空间复杂度：O(M)
// 稳定性：稳定
void CountSort(int* array, int size)
{
	// 1. 找出数据的范围--O(N)
	int minValue = array[0];
	int maxValue = array[0];
	for (int i = 1; i < size; ++i)
	{
		if (array[i] > maxValue)
			maxValue = array[i];

		if (array[i] < minValue)
			minValue = array[i];
	}

	// 给出用于计数的辅助空间
	int range = maxValue - minValue + 1;
	int* temp = (int*)malloc(sizeof(int)*range);
	assert(temp);
	memset(temp, 0, sizeof(int)*range);

	// 统计每个元素出现的次数--O(N)
	for (int i = 0; i < size; ++i)
		temp[array[i] - minValue]++;

	// 对数据进行回收   O(N)
	int index = 0;
	for (int i = 0; i < range; ++i)
	{
		int count = temp[i];
		while (count--)
			array[index++] = i + minValue;
	}

	free(temp);
}

// 基数排序


