#include <malloc.h>
#include <string.h>
#include <stdio.h>

void PrintArray(int* array, int size)
{
	for (int i = 0; i < size; ++i)
		printf("%d ", array[i]);
	printf("\n");
}

// O(N)
void MergeData(int* array, int left, int mid, int  right, int* temp)
{
	int begin1 = left, end1 = mid;
	int begin2 = mid, end2 = right;
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

// [left, right)
void _MergeSort(int* array, int left, int right, int* temp)
{
	if (right - left <= 16)
	{
		//InsertSort(array, right - left);
		return;
	}
		

	int mid = (left + ((right-left) >> 1));
	// [left, mid) [mid, right)
	_MergeSort(array, left, mid, temp);
	_MergeSort(array, mid, right, temp);

	MergeData(array, left, mid, right, temp);
	memcpy(array + left , temp+left, (right - left)*sizeof(array[0]));
}

void MergeSort(int* arrray, int size)
{
	int* temp = (int*)malloc(size*sizeof(arrray[0]));
	if (NULL == temp)
		return;

	_MergeSort(arrray, 0, size, temp);
	free(temp);
}

void MergeSortNor(int* array, int size)
{
	int* temp = (int*)malloc(size*sizeof(array[0]));
	if (NULL == temp)
		return;

	int gap = 1;
	while (gap < size)
	{
		for (size_t i = 0; i < size; i+=2*gap)
		{
			int left = i;
			int mid = left + gap;
			int right = mid + gap;

			if (mid >= size)
				mid = size;

			if (right >= size)
				right = size;
			MergeData(array, left, mid, right, temp);
		}

		memcpy(array, temp, size*sizeof(array[0]));
		gap *= 2;
	}
	
	free(temp);
}

// 应用场景
// 时间复杂度：O(N)
// 空间复杂度: O(M)  M: 区间中元素的个数
// 稳定性：稳定的
void CountSort(int* array, int size)
{
	// 1. 计算数据范围
	int minValue = array[0];
	int maxValue = array[0];
	// O(N)
	for (int i = 0; i < size; ++i)
	{
		if (array[i] < minValue)
			minValue = array[i];

		if (array[i] > maxValue)
			maxValue = array[i];
	}

	// 2. 获取计数的空间
	int range = maxValue - minValue + 1;
	int* temp = (int*)malloc(range*sizeof(int));
	if (NULL == temp)
		return;

	// 3. 统计每个元素出现的次数
	memset(temp, 0, sizeof(int)*range);

	// O(N)
	for (int i = 0; i < size; ++i)
		temp[array[i]-minValue]++;

	// 回收
	// O(N)
	int index = 0;
	for (int i = 0; i < range; ++i)
	{
		while (temp[i])
		{
			array[index++] = i + minValue;
			temp[i]--;
		}	
	}

	free(temp);
}


// 非比较排序
// 计数排序---鸽巢原理
int main()
{
	//int array[] = {3,1,5,0,8,6,4,9,7,2};
	int array[] = { 3, 1, 5, 3,3,3,3,0, 8, 6, 4, 9, 7, 2 };
	PrintArray(array, sizeof(array) / sizeof(array[0]));
	//MergeSort(array, sizeof(array)/sizeof(array[0]));
	//MergeSortNor(array, sizeof(array) / sizeof(array[0]));
	CountSort(array, sizeof(array) / sizeof(array[0]));
	PrintArray(array, sizeof(array) / sizeof(array[0]));

	//  3   4   3   2   3   7   9  7   6   7   9  5   5   2  2   3   0    0
	return 0;
}