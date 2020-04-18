#pragma once

#include <iostream>
using namespace std;


template<class T>
struct AVLTreeNode
{
	AVLTreeNode(const T& data = T())
	: _pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _data(data)
	, _bf(0)
	{}

	AVLTreeNode<T>* _pLeft;
	AVLTreeNode<T>* _pRight;
	AVLTreeNode<T>* _pParent;
	T _data;
	int _bf;   // �ڵ��ƽ������
};



// AVL: ���������� + ƽ�����ӵ�����
template<class T>
class AVLTree
{
	typedef AVLTreeNode<T> Node;
public:
	AVLTree()
		: _pRoot(nullptr)
	{}

	bool Insert(const T& data)
	{
		// �Ȱ��ն����������ķ�ʽ���в���
		if (nullptr == _pRoot)
		{
			_pRoot = new Node(data);
			return true;
		}

		// ���ն������������ԣ��Ҵ�����ڵ������е�λ��
		// ��������˫��
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

		// �����½ڵ�
		pCur = new Node(data);
		if (data < pParent->_data)
			pParent->_pLeft = pCur;
		else
			pParent->_pRight = pCur;
		pCur->_pParent = pParent;

		while (pParent)
		{
			// ����pParent��ƽ������
			if (pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;

			if (0 == pParent->_bf)
				break;
			else if (-1 == pParent->_bf || 1 == pParent->_bf)
			{
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{
				// pParent->_bf: 2 || -2
				// pParent�Ľڵ�ʧȥƽ��
				if (2 == pParent->_bf)
				{
					// ��������-->����������
					if (1 == pCur->_bf)
						RotateL(pParent);
					else
						RotateRL(pParent);
				}
				else
				{
					if (-1 == pCur->_bf)
						RotateR(pParent);
					else
						RotateLR(pParent);
				}

				break;
			}
		}
		
		return true;
	}

	void InOrder()
	{
		_InOrder(_pRoot);
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

	bool IsAVLTree()
	{
		return _IsAVLTree(_pRoot);
	}

private:
	bool _IsAVLTree(Node* pRoot)
	{
		if (nullptr == pRoot)
			return true;

		int leftHeight = _Height(pRoot->_pLeft);
		int rightHeight = _Height(pRoot->_pRight);

		if (abs(rightHeight - leftHeight) > 1 ||
			rightHeight - leftHeight != pRoot->_bf)
			return false;

		return _IsAVLTree(pRoot->_pLeft) && _IsAVLTree(pRoot->_pRight);
	}

	size_t _Height(Node* pRoot)
	{
		if (nullptr == pRoot)
			return 0;

		size_t leftHeight = _Height(pRoot->_pLeft);
		size_t rightHeight = _Height(pRoot->_pRight);

		return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
	}


	void RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		// �ı�pParent��pSubL���ӵ�ָ��
		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;

		// ����pParent��pSubL��˫��
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		// ����ԭpParent˫�׵���||��ָ����ָ��
		if (nullptr == pPParent)
		{
			_pRoot = pSubL;
		}
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}

		pParent->_bf = pSubL->_bf = 0;
	}

	void RotateL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubR;
		pSubR->_pParent = pPParent;

		if (nullptr == pPParent)
		{
			_pRoot = pSubR;
		}
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}

		pParent->_bf = pSubR->_bf = 0;
	}

	void RotateRL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;
		int bf = pSubRL->_bf;

		RotateR(pParent->_pRight);
		RotateL(pParent);

		// ���²��ֽڵ��ƽ������
		if (bf == -1)
			pSubR->_bf = 1;
		else if (bf == 1)
			pParent->_bf = -1;
	}

	void RotateLR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;
		int bf = pSubLR->_bf;

		RotateL(pParent->_pLeft);
		RotateR(pParent);
		if (-1 == bf)
			pParent->_bf = 1;
		else if (1 == bf)
			pSubL->_bf = -1;
	}

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

void TestAVLTree()
{
	//int array[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	int array[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
	AVLTree<int> t;
	for (auto e : array)
	{
		t.Insert(e);
	}

	// ��֤���Ƿ�Ϊ����������
	t.InOrder();
	cout << endl;

	cout << t.LeftMost()->_data << endl;
	cout<<t.RightMost()->_data<<endl;
	if (t.IsAVLTree())
		cout << "t is AVLTree" << endl;
	else
		cout << "t is not AVLTree" << endl;
}