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
		// ����---ֱ�Ӳ���
		if (nullptr == _pRoot)
			_pRoot = new Node(data);

		// �ǿ�--�Ҵ�����ڵ��ڶ����������е�λ��
		// ��������˫�׽ڵ�
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

		// ����Ԫ��
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

		// �Ҵ�ɾ���ڵ��ڶ����������е�λ��
		// ��������˫��
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

		// �ýڵ㲻�ڶ�����������
		if (nullptr == pCur)
			return false;

		// �Ѿ��ҵ��øýڵ㣬ɾ��
		// ֻ���Һ��� || Ҷ�ӽڵ�
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
			// ֻ������
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
			// ���Һ��Ӿ�����
			Node* pDelNode = pCur->_pRight;
			pParent = pCur;
			// ������ڵ㣺��������������С(����)
			while (pDelNode->_pLeft)
			{
				pParent = pDelNode;
				pDelNode = pDelNode->_pLeft;
			}
			
			// ������ڵ���ֵ���滻ɾ���ڵ�
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