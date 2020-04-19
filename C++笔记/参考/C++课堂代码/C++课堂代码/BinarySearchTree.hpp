#pragma once
#include <iostream>
using namespace std;


template<class T>
struct BSTreeNode
{
	BSTreeNode(const T& data = T())
	: _pLeft(nullptr)
	, _pRight(nullptr)
	, _data(data)
	{}

	BSTreeNode<T>* _pLeft;
	BSTreeNode<T>* _pRight;
	T _data;
};


template<class T>
class BSTree
{
	typedef BSTreeNode<T> Node;
public:
	BSTree()
		: _pRoot(nullptr)
	{}

	bool Insert(const T& data)
	{
		// 空树---直接插入
		if (nullptr == _pRoot)
			_pRoot = new Node(data);

		// 非空--找待插入节点在二叉搜索树中的位置
		// 并保存其双亲节点
		Node* pCur = _pRoot;
		Node* pParent = nullptr;
		while (pCur)
		{
			pParent = pCur;
			if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else if (data > pCur->_data)
				pCur = pCur->_pRight;
			else
				return false;
		}

		// 插入元素
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;

		return true;
	}

	bool Delete(const T& data)
	{
		if (nullptr == _pRoot)
			return false;

		// 找待删除节点在二叉搜索树中的位置
		// 并保存其双亲
		Node* pCur = _pRoot;
		Node* pParent = nullptr;
		while (pCur)
		{
			if (data == pCur->_data)
				break;
			else if (data < pCur->_data)
			{
				pParent = pCur;
				pCur = pCur->_pLeft;
			}
			else
			{
				pParent = pCur;
				pCur = pCur->_pRight;
			}
		}

		// 该节点不在二叉搜索树中
		if (nullptr == pCur)
			return false;

		// 已经找到该该节点，删除
		// 只有右孩子 || 叶子节点
		if (nullptr == pCur->_pLeft)
		{
			if (nullptr == pParent)
				_pRoot = pCur->_pRight;
			else
			{
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pRight;
				else
					pParent->_pRight = pCur->_pRight;
			}
		}
		else if (nullptr == pCur->_pRight)
		{
			// 只有左孩子
			if (nullptr == pParent)
				_pRoot = pCur->_pLeft;
			else
			{
				if (pCur == pParent->_pLeft)
					pParent->_pLeft = pCur->_pLeft;
				else
					pParent->_pRight = pCur->_pLeft;
			}
		}
		else
		{
			// 左右孩子均存在
			Node* pDelNode = pCur->_pRight;
			pParent = pCur;
			// 找替代节点：在右子树中找最小(最左)
			while (pDelNode->_pLeft)
			{
				pParent = pDelNode;
				pDelNode = pDelNode->_pLeft;
			}
			
			// 用替代节点中值域替换删除节点
			pCur->_data = pDelNode->_data;

			if (pDelNode == pParent->_pLeft)
				pParent->_pLeft = pDelNode->_pRight;
			else
				pParent->_pRight = pDelNode->_pRight;

			pCur = pDelNode;
		}

		delete pCur;
		return true;
	}

	Node* Find(const T& data)
	{
		Node* pCur = _pRoot;
		while (pCur)
		{
			if (data == pCur->_data)
				return pCur;
			else if (data < pCur->_data)
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}

		return nullptr;
	}

	Node* LeftMost()
	{
		if (nullptr == _pRoot)
			return nullptr;

		Node* pCur = _pRoot;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}

	Node* RightMost()
	{
		if (nullptr == _pRoot)
			return nullptr;

		Node* pCur = _pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;

		return pCur;
	}

	void InOrder()
	{
		_InOrder(_pRoot);
	}

private:
	void _InOrder(Node* pRoot)
	{
		if (pRoot)
		{
			_InOrder(pRoot->_pLeft);
			cout << pRoot->_data << " ";
			_InOrder(pRoot->_pRight);
		}
	}
private:
	Node* _pRoot;
};

void TestBSTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> bst;
	for (auto e : a)
		bst.Insert(e);

	cout << bst.LeftMost()->_data << endl;
	cout << bst.RightMost()->_data << endl;
	bst.InOrder();

	bst.Delete(8);
	bst.InOrder();

	bst.Delete(0);
	bst.InOrder();

	bst.Delete(5);
	bst.InOrder();
}