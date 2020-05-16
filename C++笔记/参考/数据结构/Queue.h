#pragma once


//typedef int QDataType;

#include "BinTree.h"



typedef BTNode* QDataType;

// 链式结构：表示队列
typedef struct QListNode
{
	struct QListNode* _pNext;
	QDataType _data;
}QNode;

// 队列的结构
typedef struct Queue
{
	QNode* _front;
	QNode* _rear;
}Queue;


void QueueInit(Queue* q);
void QueuePush(Queue* q, QDataType data);
void QueuePop(Queue* q);
QDataType QueueFront(Queue* q);
QDataType QueueBack(Queue* q);
int QueueSize(Queue* q);
int QueueEmpty(Queue* q);
void QueueDestroy(Queue* q);
