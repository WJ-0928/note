#pragma once


typedef char BTDataType;

typedef struct BTNode
{
	struct BTNode* _pLeft;
	struct BTNode* _pRight;
	BTDataType _data;
}BTNode;



// 1. 创建
BTNode* CreateBinTree(BTDataType* array, int size);
BTNode* CopyBinTree(BTNode* pRoot);
void DestroyBinTree(BTNode** pRoot);
// 二叉树的三种遍历方式
void PreOrder(BTNode* pRoot);
void PreOrderNor(BTNode* pRoot);
void InOrder(BTNode* pRoot);
void InOrderNor(BTNode* pRoot);
void PostOrder(BTNode* pRoot);
void PostOrderNor(BTNode* pRoot);
void LevelOrder(BTNode* pRoot);
int GetNodeCount(BTNode* pRoot);
int Height(BTNode* pRoot);
int IsBalanceTree(BTNode* pRoot); 
int IsBalanceTree_P(BTNode* pRoot, int* height);
int GetLeafNodeCount(BTNode* pRoot);
int GetKLevelNodeCount(BTNode* pRoot, int K);
BTNode* GetNodeParent(BTNode* pRoot, BTNode* pNode);
BTNode* GetNode(BTNode* pRoot, BTDataType data);
void Mirror(BTNode* pRoot);

void TestBinTree();
void TestTree2Str();