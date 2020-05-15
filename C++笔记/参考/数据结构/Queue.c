#include "Queue.h"
#include <assert.h>
#include <malloc.h>
#include <stdio.h>


QNode* BuyQNode(QDataType data)
{
	QNode* pNewNode = (QNode*)malloc(sizeof(QNode));
	if (NULL == pNewNode)
	{
		assert(0);
		return NULL;
	}

	pNewNode->_data = data;
	pNewNode->_pNext = NULL;

	return pNewNode;
}

void QueueInit(Queue* q)
{
	assert(q);
	q->_front = q->_rear = NULL;
}

void QueuePush(Queue* q, QDataType data)
{
	QNode* pNewNode = NULL;
	assert(q);

	// Î²²å
	// ¿Õ¶ÓÁÐ
	pNewNode = BuyQNode(data);
	if (NULL == q->_front)
	{
		q->_front = q->_rear = pNewNode;
	}
	else
	{
		q->_rear->_pNext = pNewNode;
		q->_rear = pNewNode;
	}
}

void QueuePop(Queue* q)
{
	assert(q);
	if (NULL == q->_front)
		return;
	else if (q->_front == q->_rear)
	{
		free(q->_front);
		q->_front = q->_rear = NULL;
	}
	else
	{
		QNode* pDel = q->_front;
		q->_front = pDel->_pNext;
		free(pDel);
	}
}

QDataType QueueFront(Queue* q)
{
	assert(q);
	return q->_front->_data;
}

QDataType QueueBack(Queue* q)
{
	assert(q);
	return q->_rear->_data;
}


int QueueSize(Queue* q)
{
	QNode* pCur = NULL;
	int count = 0;
	assert(q);

	pCur = q->_front;
	while (pCur)
	{
		count++;
		pCur = pCur->_pNext;
	}

	return count;
}

int QueueEmpty(Queue* q)
{
	assert(q);
	return NULL == q->_front;
}

void QueueDestroy(Queue* q)
{
	QNode* pCur = NULL;
	assert(q);

	pCur = q->_front;
	while (pCur)
	{
		q->_front = pCur->_pNext;
		free(pCur);
		pCur = q->_front;
	}

	q->_front = q->_rear = NULL;
}