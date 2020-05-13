#pragma once


typedef int HPDataType;
typedef int(*PFC)(HPDataType left, HPDataType right);

typedef struct Heap
{
	HPDataType* _array;
	int _capacity;
	int _size;   // ������ЧԪ�ظ���
	PFC _pFC;
}Heap;


int Less(HPDataType left, HPDataType right);
int Greater(HPDataType left, HPDataType right);

void CreateHeap(Heap* hp, HPDataType* array, int size, PFC pFC);
void InsertHeap(Heap* hp, HPDataType data);
void EraseHeap(Heap* hp); // ɾ���Ѷ�Ԫ��
HPDataType TopHeap(Heap* hp);
int  SizeHeap(Heap* hp);
int  EmptyHeap(Heap* hp);
void DestroyHeap(Heap* hp);

// ������
void HeapSort(int* array, int size);