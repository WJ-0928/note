#pragma once


typedef int DLDataType;

typedef struct DListNode
{
	struct DListNode* _pNext;
	struct DListNode* _pPre;
	DLDataType _data;
}DLNode;



void DListInit(DLNode** pHead);
void DListPushBack(DLNode* pHead, DLDataType data);
void DListPopBack(DLNode* pHead);

void DListPushFront(DLNode* pHead, DLDataType data);
void DListPopFront(DLNode* pHead);

DLNode* DListFind(DLNode* pHead, DLDataType data);
void DListInsert(DLNode* pos, DLDataType data);
void DListErase(DLNode* pos);
void DListClear(DLNode* pHead);
void DListDestroy(DLNode** pHead);
void TestDList();