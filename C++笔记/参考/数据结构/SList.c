#include "SList.h"
#include <assert.h>
#include <stdio.h>
#include <malloc.h>


void SListInit(SList* pl)
{
	assert(pl);
	pl->_pHead = NULL;
}


Node* BuySListNode(SDataType data)
{
	Node* pNode = (Node*)malloc(sizeof(Node));
	if (NULL == pNode)
	{
		assert(0);
		return NULL;
	}

	pNode->_data = data;
	pNode->_pNext = NULL;

	return pNode;
}

void SListPushBack(SList* pl, SDataType data)
{
	Node* pNewNode = NULL;
	Node* pCur = NULL;

	assert(pl);

	pNewNode = BuySListNode(data);
	pCur = pl->_pHead;
	
	// ������
	if (NULL == pl->_pHead)
		pl->_pHead = pNewNode;
	else
	{
		while (pCur->_pNext)
		{
			pCur = pCur->_pNext;
		}

		pCur->_pNext = pNewNode;
	}
}

void SListPopBack(SList* pl)
{
	assert(pl);
	if (NULL == pl->_pHead)  // ������
	{
		return;
	}
	else if (NULL == pl->_pHead->_pNext)  // ֻ��һ���ڵ�
	{
		free(pl->_pHead);
		pl->_pHead = NULL;
	}
	else  // �����������ڵ�
	{
		/*
		// �ҵ�����һ���ڵ㣬��������ǰһ���ڵ�
		Node* pTailNode = pl->_pHead;
		Node* pPreTail = NULL;
		while (pTailNode->_pNext)
		{
			pPreTail = pTailNode;
			pTailNode = pTailNode->_pNext;
		}

		free(pTailNode);
		pPreTail->_pNext = NULL;
		*/

		// �ҵ����ڶ����ڵ�
		Node* pTailNode = pl->_pHead;
		// 1-->2-->3-->NULL
		while (pTailNode->_pNext->_pNext)
		{
			pTailNode = pTailNode->_pNext;
		}

		free(pTailNode->_pNext);
		pTailNode->_pNext = NULL;
	}
}

void SListDestroy(SList* pl)
{
	Node* pCur = NULL;
	assert(pl);

	// ͷɾ
	pCur = pl->_pHead;
	while (pCur)
	{
		pl->_pHead = pCur->_pNext;
		free(pCur);
		pCur = pl->_pHead;
	}

	pl->_pHead = NULL;
}

void SListPushFront(SList* pl, SDataType data)
{
	Node* pNewNode = NULL;
	assert(pl);

	pNewNode = BuySListNode(data);
	pNewNode->_pNext = pl->_pHead;
	pl->_pHead = pNewNode;
}

void SListPopFront(SList* pl)
{
	assert(pl);
	if (NULL == pl->_pHead)
		return;
	else
	{
		Node* pDelNode = pl->_pHead;
		pl->_pHead = pDelNode->_pNext;
		free(pDelNode);
	}
}

void SListInsertAfter(Node* pos, SDataType data)
{
	Node* pNewNode = NULL;
	if (NULL == pos)
		return;

	pNewNode = BuySListNode(data);
	pNewNode->_pNext = pos->_pNext;
	pos->_pNext = pNewNode;
}

void SListErase(SList* pl, Node* pos)
{
	Node* pPrePos = NULL;

	assert(pl);
	if (NULL == pl->_pHead || NULL == pos)
		return;

	// pos�պ��ڵ�һ���ڵ��λ��
	if (pos == pl->_pHead)
	{
		pl->_pHead = pos->_pNext;
		free(pos);
		return;
	}

	// pos�ڷǵ�һ���ڵ��λ��
	pPrePos = pl->_pHead;
	while (pPrePos->_pNext != pos)
	{
		pPrePos = pPrePos->_pNext;
	}

	pPrePos->_pNext = pos->_pNext;
	free(pos);
}

Node* SListFind(SList* pl, SDataType data)
{
	Node* pCur = pl->_pHead;
	assert(pl);

	while (pCur)
	{
		if (pCur->_data == data)
			return pCur;

		pCur = pCur->_pNext;
	}

	return NULL;
}

int SListSize(SList* pl)
{
	Node* pCur = NULL;
	int count = 0;
	assert(pl);

	pCur = pl->_pHead;
	while (pCur)
	{
		count++;
		pCur = pCur->_pNext;
	}

	return count;
}

int SListEmpty(SList* pl)
{
	assert(pl);
	return NULL == pl->_pHead;
}

Node* SListFront(SList* pl)
{
	assert(pl);

	return pl->_pHead;
}

// ���뱣֤�нڵ�
Node* SListBack(SList* pl)
{
	Node* pCur = NULL;
	assert(pl);
	assert(pl->_pHead);

	pCur = pl->_pHead;
	while (pCur->_pNext)
	{
		pCur = pCur->_pNext;
	}

	return pCur;
}

//////////////////////////////////////////
// 
void PrintfSList(SList* pl)
{
	Node* pCur = NULL;
	assert(pl);

	pCur = pl->_pHead;
	while (pCur)
	{
		printf("%d--->", pCur->_data);
		pCur = pCur->_pNext;
	}
	
	printf("NULL\n");
}


void TestList1()
{
	SList s;
	SListInit(&s);
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);
	SListPushBack(&s, 4);
	PrintfSList(&s);

	SListPopBack(&s);
	PrintfSList(&s);

	SListPopBack(&s);
	SListPopBack(&s);
	SListPopBack(&s);
	SListPopBack(&s);

	SListDestroy(&s);
}


void TestList2()
{
	SList s;
	SListInit(&s);
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);
	SListPushBack(&s, 4);
	PrintfSList(&s);

	SListPushFront(&s, 0);
	PrintfSList(&s);

	SListPopFront(&s);
	PrintfSList(&s);

	SListPopFront(&s);
	SListPopFront(&s);
	SListPopFront(&s);
	SListPopFront(&s);
	SListPopFront(&s);
	SListPopFront(&s);
	SListPopFront(&s);
	SListPopFront(&s);

	SListDestroy(&s);
}

void TestSList3()
{
	SList s;
	SListInit(&s);
	SListPushBack(&s, 1);
	SListPushBack(&s, 2);
	SListPushBack(&s, 3);
	SListPushBack(&s, 4);
	PrintfSList(&s);

	SListInsertAfter(SListFind(&s, 2), 5);
	PrintfSList(&s);

	SListErase(&s, SListFind(&s, 5));
	PrintfSList(&s);

	SListErase(&s, SListFind(&s, 1));
	PrintfSList(&s);

	SListDestroy(&s);
}

// 1. ����Ϊ��
// 2. ����ǿ�---�����һ���ڵ�

// pHead����---����ĵ�ַ
void SListPushBackII(Node** pHead, SDataType data)
{
	assert(pHead);
	Node* pNewNode = BuySListNode(data);
	if (NULL == *pHead)
	{
		*pHead = pNewNode;
	}
	else
	{
		Node* pCur = *pHead;
		while (pCur->_pNext)
		{
			pCur = pCur->_pNext;
		}

		pCur->_pNext = pNewNode;
	}
}

void TestSList4()
{
	Node* pHead = NULL;
	SListPushBackII(&pHead, 1);
}

/*
// ����ͷ�ڵ�
// һ��ָ��---->��������
void SListPushFrontII(Node* pHead, SDataType data)
{
	printf("%p\n", &pHead);
	Node* pNewNode = BuySListNode(data);
	pNewNode->_pNext = pHead;
	pHead = pNewNode;   // �޸�ָ�뱾�������
}

void TestList5()
{
	Node* pH = NULL;
	printf("%p\n", &pH);
	SListPushFrontII(&pH, 1);
	SListPushFrontII(&pH, 2);
}
*/

// ��ͷ���
void SListPushFrontII(Node* pHead, SDataType data)
{
	printf("%p\n", &pHead);
	Node* pNewNode = BuySListNode(data);
	pNewNode->_pNext = pHead->_pNext;
	pHead->_pNext = pNewNode;  // ���Ǹı�ָ��ռ������
}

// ��ͷ���
void TestList5()
{
	Node nodeHead;
	nodeHead._pNext = NULL;

	
	SListPushFrontII(&nodeHead, 1);
	SListPushFrontII(&nodeHead, 2);
}

void TestList()
{
	//TestList1();
	//TestList2();
	//TestSList3();

	//TestSList4();
	TestList5();
}