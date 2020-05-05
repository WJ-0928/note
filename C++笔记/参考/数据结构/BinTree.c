#include "BinTree.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>
#include <string.h>
#include <math.h>

#include "Queue.h"
#include "Stack.h"


BTNode* BuyBinTreeNode(BTDataType data)
{
	BTNode* pNewNode = (BTNode*)malloc(sizeof(BTNode));
	if (NULL == pNewNode)
		assert(0);

	pNewNode->_pLeft = NULL;
	pNewNode->_pRight = NULL;
	pNewNode->_data = data;

	return pNewNode;
}

// 提供给外部用户
// 前序规则：ABD###CE##F
BTNode* _CreateBinTree(BTDataType* array, int size, int* index)
{
	BTNode* pRoot = NULL;
	if (*index < size && '#' != array[*index])
	{
		// 创建根节点
		pRoot = BuyBinTreeNode(array[*index]);
		(*index)++;

		// 创建根节点的左子树
		pRoot->_pLeft = _CreateBinTree(array, size, index);

		// 创建根节点的右子树
		(*index)++;
		pRoot->_pRight = _CreateBinTree(array, size, index);
	}

	return pRoot;
}

BTNode* CreateBinTree(BTDataType* array, int size)
{
	int index = 0;
	return _CreateBinTree(array, size, &index);
}

BTNode* CopyBinTree(BTNode* pRoot)
{
	BTNode* pNewRoot = NULL;
	if (pRoot)
	{
		// 拷贝根节点
		pNewRoot = BuyBinTreeNode(pRoot->_data);

		// 拷贝根节点的左子树
		if (pRoot->_pLeft)
			pNewRoot->_pLeft = CopyBinTree(pRoot->_pLeft);

		// 拷贝根节点的右子树
		if (pRoot->_pRight)
			pNewRoot->_pRight = CopyBinTree(pRoot->_pRight);
	}

	return pNewRoot;
}

void DestroyBinTree(BTNode** pRoot)
{
	assert(pRoot);
	if (*pRoot)
	{
		DestroyBinTree(&(*pRoot)->_pLeft);
		DestroyBinTree(&(*pRoot)->_pRight);
		free(*pRoot);
		*pRoot = NULL;
	}
}

// 根节点---->根节点的左子树----->根节点的右子树
void PreOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		printf("%c ", pRoot->_data);
		PreOrder(pRoot->_pLeft);
		PreOrder(pRoot->_pRight);
	}
}

void PreOrderNor(BTNode* pRoot)
{
	Stack s;
	if (NULL == pRoot)
		return;

	StackInit(&s);
	StackPush(&s, pRoot);
	while (!StackEmpty(&s))
	{
		BTNode* pCur = StackTop(&s);
		StackPop(&s);
		printf("%c ", pCur->_data);

		if (pCur->_pRight)
			StackPush(&s, pCur->_pRight);

		if (pCur->_pLeft)
			StackPush(&s, pCur->_pLeft);
	}

	printf("\n");
	StackDestroy(&s);
}

void InOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		InOrder(pRoot->_pLeft);
		printf("%c ", pRoot->_data);
		InOrder(pRoot->_pRight);
	}
}

void InOrderNor(BTNode* pRoot)
{
	Stack s;
	BTNode* pCur = pRoot;
	StackInit(&s);
	while (pCur || !StackEmpty(&s))
	{
		// 找以pCur为根的二叉树最左侧节点，并保存所经路径中的所有节点
		while (pCur)
		{
			StackPush(&s, pCur);
			pCur = pCur->_pLeft;
		}

		pCur = StackTop(&s);
		printf("%c ", pCur->_data);
		StackPop(&s);

		pCur = pCur->_pRight;
	}

	printf("\n");
	StackDestroy(&s);
}

void PostOrder(BTNode* pRoot)
{
	if (pRoot)
	{
		PostOrder(pRoot->_pLeft);
		PostOrder(pRoot->_pRight);
		printf("%c ", pRoot->_data);
	}
}

void PostOrderNor(BTNode* pRoot)
{
	BTNode* pCur = pRoot;
	BTNode* pPrev = NULL;   // 标记最近刚访问过的节点
	Stack s;
	StackInit(&s);

	while (pCur || !StackEmpty(&s))
	{
		// 找以pCur为根的二叉树最左侧的节点，并保存其所经路径中的所有节点
		while (pCur)
		{
			StackPush(&s, pCur);
			pCur = pCur->_pLeft;
		}

		BTNode* pTop = StackTop(&s);
		if (NULL == pTop->_pRight || pTop->_pRight == pPrev)
		{
			printf("%c ", pTop->_data);
			pPrev = pTop;
			StackPop(&s);
		}
		else
			pCur = pTop->_pRight;
	}

	printf("\n");
	StackDestroy(&s);
}

void LevelOrder(BTNode* pRoot)
{
	Queue q;
	if (NULL == pRoot)
		return;

	QueueInit(&q);
	QueuePush(&q, pRoot);
	while (!QueueEmpty(&q))
	{
		BTNode* pCur = QueueFront(&q);
		printf("%c ", pCur->_data);
		QueuePop(&q);

		// 检测当前节点是否存在左孩子
		if (pCur->_pLeft)
			QueuePush(&q, pCur->_pLeft);

		// 检测当前节点是否存在右孩子
		if (pCur->_pRight)
			QueuePush(&q, pCur->_pRight);
	}

	QueueDestroy(&q);
	printf("\n");
}

int GetNodeCount(BTNode* pRoot)
{
	if (NULL == pRoot)
		return 0;

	return GetNodeCount(pRoot->_pLeft) + GetNodeCount(pRoot->_pRight) + 1;
}

// O(N)
int Height(BTNode* pRoot)
{
	int leftHeight = 0;
	int rightHeight = 0;
	if (NULL == pRoot)
		return 0;

	leftHeight = Height(pRoot->_pLeft);
	rightHeight = Height(pRoot->_pRight);
	return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

// 缺陷：O(N^2)
int IsBalanceTree(BTNode* pRoot)
{
	int leftHeight = 0;
	int rightHeight = 0;
	if (NULL == pRoot)
		return 1;

	leftHeight = Height(pRoot->_pLeft);
	rightHeight = Height(pRoot->_pRight);
	return abs(rightHeight - leftHeight) < 2 &&
		IsBalanceTree(pRoot->_pLeft) &&
		IsBalanceTree(pRoot->_pRight);
}

//O(N)
int IsBalanceTree_P(BTNode* pRoot, int* height)
{
	int IsLBalance = 0;
	int IsRBalance = 0;
	int leftHeight = 0;
	int rightHeight = 0;

	if (NULL == pRoot)
		return 1;

	// 验证pRoot的左右子树是否平衡
	IsLBalance = IsBalanceTree_P(pRoot->_pLeft, &leftHeight);
	IsRBalance = IsBalanceTree_P(pRoot->_pRight, &rightHeight);

	if (IsLBalance && IsRBalance && abs(rightHeight - leftHeight) < 2)
	{
		*height = leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
		return 1;
	}

	return 0;
}

int GetLeafNodeCount(BTNode* pRoot)
{
	if (NULL == pRoot)
		return 0;

	if (NULL == pRoot->_pLeft && NULL == pRoot->_pRight)
		return 1;

	return GetLeafNodeCount(pRoot->_pLeft) + GetLeafNodeCount(pRoot->_pRight);
}

int GetKLevelNodeCount(BTNode* pRoot, int K)
{
	if (NULL == pRoot || K < 1)
		return 0;

	if (1 == K)
		return 1;

	return GetKLevelNodeCount(pRoot->_pLeft, K - 1) +
		   GetKLevelNodeCount(pRoot->_pRight, K - 1);
}

BTNode* GetNodeParent(BTNode* pRoot, BTNode* pNode)
{
	BTNode* pParent = NULL;
	if (NULL == pRoot || NULL == pNode)
		return NULL;

	if (pRoot == pNode)
		return NULL;

	if (pRoot->_pLeft == pNode || pRoot->_pRight == pNode)
		return pRoot;

	if (pParent = GetNodeParent(pRoot->_pLeft, pNode))
		return pParent;

	return GetNodeParent(pRoot->_pRight, pNode);
}

BTNode* GetNode(BTNode* pRoot, BTDataType data)
{
	BTNode* pNode = NULL;
	if (NULL == pRoot)
		return NULL;

	if (pRoot->_data == data)
		return pRoot;

	if (pNode = GetNode(pRoot->_pLeft, data))
		return pNode;

	return GetNode(pRoot->_pRight, data);
}

void Swap(BTNode** pLeft, BTNode** pRight)
{
	BTNode* pTemp = *pLeft;
	*pLeft = *pRight;
	*pRight = pTemp;
}


void Mirror(BTNode* pRoot)
{
	if (pRoot)
	{
		Swap(&(pRoot->_pLeft), &(pRoot->_pRight));
		Mirror(pRoot->_pLeft);
		Mirror(pRoot->_pRight);
	}
}

void MirrorNor(BTNode* pRoot)
{
	if (NULL == pRoot)
		return;

	Queue q;
	QueueInit(&q);
	QueuePush(&q, pRoot);

	while (!QueueEmpty(&q))
	{
		BTNode* pCur = QueueFront(&q);
		Swap(&(pCur->_pLeft), &(pCur->_pRight));

		if (pCur->_pLeft)
			QueuePush(&q, pCur->_pLeft);

		if (pCur->_pRight)
			QueuePush(&q, pCur->_pRight);

		QueuePop(&q);
	}
}





/////////////////////////////////////////
void TestBinTree()
{
	char* pStr = "ABD###CE##F";
	BTNode* pRoot = CreateBinTree(pStr, strlen(pStr));
	BTNode* pNewRoot = CopyBinTree(pRoot);
	BTNode* pParent;
	printf("前序遍历：");
	PreOrder(pRoot);
	printf("\n");
	PreOrderNor(pRoot);
	PreOrder(pNewRoot);
	printf("\n");

	printf("中序遍历：");
	InOrder(pRoot);
	printf("\n");
	InOrderNor(pRoot);
	InOrder(pNewRoot);
	printf("\n");


	printf("后序遍历：");
	PostOrder(pRoot);
	printf("\n");
	PostOrderNor(pRoot);

	PostOrder(pNewRoot);
	printf("\n");

	printf("层序遍历：");
	LevelOrder(pRoot);


	printf("二叉树中的节点个数:%d\n", GetNodeCount(pRoot));
	printf("二叉树的高度:%d\n", Height(pRoot));
	printf("二叉树是否平衡:%d\n", IsBalanceTree(pRoot));
	printf("二叉树中叶子节点个数:%d\n", GetLeafNodeCount(pRoot));
	printf("二叉树第3层中节点个数:%d\n", GetKLevelNodeCount(pRoot, 3));
	printf("二叉树第10层中节点个数:%d\n", GetKLevelNodeCount(pRoot, 10));

	pParent = GetNodeParent(pRoot, GetNode(pRoot, 'D'));
	pParent = GetNodeParent(pRoot, GetNode(pRoot, 'G'));
	DestroyBinTree(&pRoot);
	DestroyBinTree(&pNewRoot);
}

char* _tree2str(BTNode* t, char* szRet)
{
	if (NULL == t)
		return szRet;

	char szValue[32] = { 0 };
	//itoa(t->val, szValue, 10);
	sprintf(szValue, "%d", t->_data);
	strcat(szRet, szValue);

	if (NULL == t->_pLeft)
	{
		if (NULL == t->_pRight)
			return szRet;
		else
			strcat(szRet, "()");
	}
	else
	{
		strcat(szRet, "(");
		_tree2str(t->_pLeft, szRet);
		strcat(szRet, ")");
	}

	if (NULL == t->_pRight)
	{
		return szRet;
	}
	else
	{
		strcat(szRet, "(");
		_tree2str(t->_pRight, szRet);
		strcat(szRet, ")");
	}

	return szRet;
}

void TestTree2Str()
{
	char szRet[100000];
	szRet[0] = '\0';

	char* pStr = "124###3";
	BTNode* pRoot = CreateBinTree(pStr, strlen(pStr));
	_tree2str(pRoot, szRet);
	return szRet;
}