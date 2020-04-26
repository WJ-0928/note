#pragma once

// �����������������
//        �ڵ���������ɫ����ɫ �� ��ɫ
//        ����Լ����5������
/*
1. ÿ���ڵ㶼����ɫ����ɫ���ߺ�ɫ
2. ���ڵ����Ϊ��ɫ
3. ���һ���ڵ����ɫ�Ǻ�ɫ�ģ����ĺ��ӽڵ�һ���Ǻ�ɫ��
   ������в����������һ��ĺ�ɫ�ڵ�
4. ÿ��·���к�ɫ�ڵ�ĸ�����ͬ
5. ÿ��Ҷ�ӽڵ㶼�Ǻ�ɫ(�˴���Ҷ�ӽڵ㣺���еĿ�ָ����)
*/
// ���ۣ��·���нڵ����һ�����ᳬ�����·���нڵ����������
// ��ˣ��������һ�ý���ƽ��Ķ���������
// ��������ܱ�AVL�����ѣ�����ʵ�ֱȽϼ�


#include <iostream>
using namespace std;



#if 0
enum Color{RED, BLACK};

template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& data = T(), Color color = RED)
	: _pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _data(data)
	, _color(color)
	{}

	RBTreeNode<T>* _pLeft;
	RBTreeNode<T>* _pRight;
	RBTreeNode<T>* _pParent;
	T _data;
	Color _color;
};


// �ҹ�����10��30��
template<class T>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;

	RBTreeIterator(Node* pNode)
		: _pNode(pNode)
	{}

	T& operator*()
	{
		return _pNode->_data;
	}

	T* operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		Increament();
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Increament();
		return temp;
	}

	Self& operator--()
	{
		DeIncreament();
		return *this;
	}

	Self operator--(int)
	{
		Self temp(*this);
		DeIncreament();
		return temp;
	}

	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}

	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}

private:
	// ++
	void Increament()
	{
		if (_pNode->_pRight)
		{
			// ���������������ڵ�
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
				_pNode = _pNode->_pLeft;
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}

			// ע�⣺�������-->���ڵ�û���Һ��ӣ��������ڸ�λ��
			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}

	// --
	void DeIncreament()
	{
		// �����������end��λ��
		if (_pNode->_pParent->_pParent == _pNode && _pNode->_color == RED)
			_pNode = _pNode->_pRight;
		else if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
				_pNode = _pNode->_pRight;
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (pParent->_pLeft == _pNode)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}

			_pNode = pParent;
		}
	}

	Node* _pNode;
};

template<class T>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T> iterator;
public:
	RBTree()
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	bool Insert(const T& data)
	{
		// ���ն��������������ʲ����½ڵ�
		Node* & pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
			return true;
		}
		else
		{
			// �Ҵ�����ڵ��ڶ����������е�λ��
			// ��������˫�׽ڵ�
			Node* pCur = pRoot;
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

			// pCur�½ڵ�Ĭ����ɫ����ɫ
			// ���pParent����ɫ�Ǻ�ɫ�ģ�������������
			// ���pParent����ɫ�Ǻ�ɫ�ģ�Υ����������--����������һ��ĺ�ɫ�ڵ�
			while (pParent != _pHead && pParent->_color == RED)
			{
				Node* grandFather = pParent->_pParent;
				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;
					// ����ڵ������Ϊ��
					if (uncle && RED == uncle->_color)
					{
						// ���һ
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						// ����ڵ㲻���� || ����ڵ���� && ��ɫ
						if (pCur == pParent->_pRight)
						{
							// �����
							RotateL(pParent);
							swap(pCur, pParent);
						}

						// �������
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateR(grandFather);
					}
				}
				else
				{
					// һ�����ķ����
					Node* uncle = grandFather->_pLeft;
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						// ����ڵ㲻���� || ������Ϊ��
						if (pCur == pParent->_pLeft)
						{
							// ����������
							RotateR(pParent);
							swap(pCur, pParent);
						}

						// ������ķ����
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateL(grandFather);
					}
				}
			}
		}

		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return true;
	}

	iterator Begin()
	{
		return iterator(LeftMost());
	}

	iterator End()
	{
		return iterator(_pHead);
	}


	Node*& GetRoot()
	{
		return _pHead->_pParent;
	}

	void InOrder()
	{
		_InOrder(GetRoot());
	}

	Node* LeftMost()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;

		Node* pCur = pRoot;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}

	Node* RightMost()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;

		Node* pCur = pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;

		return pCur;
	}

	bool IsValidRBTRee()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;

		if (pRoot->_color != BLACK)
		{
			cout << "Υ������һ�����ڵ��Ǻ�ɫ" << endl;
			return false;
		}

		// ��ȡһ��·���к�ɫ�ڵ�ĸ���
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				blackCount++;

			pCur = pCur->_pLeft;
		}

		size_t pathBalck = 0;
		return _IsValidRBTRee(pRoot, blackCount, pathBalck);
	}

private:
	bool _IsValidRBTRee(Node* pRoot, size_t blackCount, size_t pathBlack)
	{
		if (nullptr == pRoot)
			return true;

		if (pRoot->_color == BLACK)
			pathBlack++;

		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead &&
			RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "Υ������3�����ܴ�������һ��ĺ�ɫ�ڵ�" << endl;
			return false;
		}

		// Ҷ�ӽڵ�
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (pathBlack != blackCount)
			{
				cout << "Υ������4��ÿ��·���к�ɫ�ڵ��������ͬ" << endl;
				return false;
			}
		}

		return _IsValidRBTRee(pRoot->_pLeft, blackCount, pathBlack) &&
			   _IsValidRBTRee(pRoot->_pRight, blackCount, pathBlack);
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
	void RotateL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pSubR->_pParent = pPParent;
		pParent->_pParent = pSubR;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubR;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
	}

	void RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;

		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}
private:
	Node* _pHead;
};

void TestRBTree()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	RBTree<int> t;
	for (auto e : a)
		t.Insert(e);

	t.InOrder();
	cout << endl;

	cout << t.LeftMost()->_data << endl;
	cout << t.RightMost()->_data << endl;

	if (t.IsValidRBTRee())
		cout << "t is RBTree" << endl;
	else
		cout << "t is not RBTree" << endl;

	auto it = t.Begin();
	while (it != t.End())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;
}
#endif

enum Color{ RED, BLACK };

template<class T>
struct RBTreeNode
{
	RBTreeNode(const T& data = T(), Color color = RED)
	: _pLeft(nullptr)
	, _pRight(nullptr)
	, _pParent(nullptr)
	, _data(data)
	, _color(color)
	{}

	RBTreeNode<T>* _pLeft;
	RBTreeNode<T>* _pRight;
	RBTreeNode<T>* _pParent;
	T _data;
	Color _color;
};


// �ҹ�����10��30��
template<class T>
struct RBTreeIterator
{
	typedef RBTreeNode<T> Node;
	typedef RBTreeIterator<T> Self;

	RBTreeIterator(Node* pNode)
		: _pNode(pNode)
	{}

	T& operator*()
	{
		return _pNode->_data;
	}

	T* operator->()
	{
		return &(operator*());
	}

	Self& operator++()
	{
		Increament();
		return *this;
	}

	Self operator++(int)
	{
		Self temp(*this);
		Increament();
		return temp;
	}

	Self& operator--()
	{
		DeIncreament();
		return *this;
	}

	Self operator--(int)
	{
		Self temp(*this);
		DeIncreament();
		return temp;
	}

	bool operator!=(const Self& s)const
	{
		return _pNode != s._pNode;
	}

	bool operator==(const Self& s)const
	{
		return _pNode == s._pNode;
	}

private:
	// ++
	void Increament()
	{
		if (_pNode->_pRight)
		{
			// ���������������ڵ�
			_pNode = _pNode->_pRight;
			while (_pNode->_pLeft)
				_pNode = _pNode->_pLeft;
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (_pNode == pParent->_pRight)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}

			// ע�⣺�������-->���ڵ�û���Һ��ӣ��������ڸ�λ��
			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}

	// --
	void DeIncreament()
	{
		// �����������end��λ��
		if (_pNode->_pParent->_pParent == _pNode && _pNode->_color == RED)
			_pNode = _pNode->_pRight;
		else if (_pNode->_pLeft)
		{
			_pNode = _pNode->_pLeft;
			while (_pNode->_pRight)
				_pNode = _pNode->_pRight;
		}
		else
		{
			Node* pParent = _pNode->_pParent;
			while (pParent->_pLeft == _pNode)
			{
				_pNode = pParent;
				pParent = _pNode->_pParent;
			}

			_pNode = pParent;
		}
	}

	Node* _pNode;
};


// T: �����Ǽ�ֵ��<key,value>
//    ������һ��key
// ���۽ڵ��д洢����<key, value> || key, ���ǰ���key�����бȽϵ�
// KeyOfValue: ��ȡdata�е�Key
template<class T, class KeyOfValue>
class RBTree
{
	typedef RBTreeNode<T> Node;
public:
	typedef RBTreeIterator<T> iterator;
public:
	RBTree()
		: _size(0)
	{
		_pHead = new Node;
		_pHead->_pLeft = _pHead;
		_pHead->_pRight = _pHead;
	}

	pair<iterator, bool> Insert(const T& data)
	{
		// ���ն��������������ʲ����½ڵ�
		Node* & pRoot = GetRoot();
		Node* pNewNode = nullptr;
		if (nullptr == pRoot)
		{
			pNewNode = pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
		}
		else
		{
			// �Ҵ�����ڵ��ڶ����������е�λ��
			// ��������˫�׽ڵ�
			Node* pCur = pRoot;
			Node* pParent = nullptr;
			while (pCur)
			{
				pParent = pCur;
				if (KeyOfValue()(data) < KeyOfValue()(pCur->_data))
					pCur = pCur->_pLeft;
				else if (KeyOfValue()(data) > KeyOfValue()(pCur->_data))
					pCur = pCur->_pRight;
				else
					return make_pair(iterator(pCur), false);
			}

			// �����½ڵ�
			pNewNode = pCur = new Node(data);
			if ((KeyOfValue()(data) < KeyOfValue()(pParent->_data)))
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;

			pCur->_pParent = pParent;

			// pCur�½ڵ�Ĭ����ɫ����ɫ
			// ���pParent����ɫ�Ǻ�ɫ�ģ�������������
			// ���pParent����ɫ�Ǻ�ɫ�ģ�Υ����������--����������һ��ĺ�ɫ�ڵ�
			while (pParent != _pHead && pParent->_color == RED)
			{
				Node* grandFather = pParent->_pParent;
				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;
					// ����ڵ������Ϊ��
					if (uncle && RED == uncle->_color)
					{
						// ���һ
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						// ����ڵ㲻���� || ����ڵ���� && ��ɫ
						if (pCur == pParent->_pRight)
						{
							// �����
							RotateL(pParent);
							swap(pCur, pParent);
						}

						// �������
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateR(grandFather);
					}
				}
				else
				{
					// һ�����ķ����
					Node* uncle = grandFather->_pLeft;
					if (uncle && RED == uncle->_color)
					{
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						// ����ڵ㲻���� || ������Ϊ��
						if (pCur == pParent->_pLeft)
						{
							// ����������
							RotateR(pParent);
							swap(pCur, pParent);
						}

						// ������ķ����
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateL(grandFather);
					}
				}
			}
		}

		++_size;
		pRoot->_color = BLACK;
		_pHead->_pLeft = LeftMost();
		_pHead->_pRight = RightMost();
		return make_pair(iterator(pNewNode), true);
	}

	iterator Begin()
	{
		return iterator(LeftMost());
	}

	iterator End()
	{
		return iterator(_pHead);
	}

	bool Empty()const
	{
		return _pHead->_pLeft == _pHead;
	}

	size_t Size()const
	{
		return _size;
	}

	void Clear()
	{
		_Destroy(GetRoot());
	}

	// O(logN)
	iterator Find(const T& data)
	{
		Node* pCur = GetRoot();
		while (pCur)
		{
			if ((KeyOfValue()(data) == KeyOfValue()(pCur->_data)))
				return iterator(pCur);
			else if ((KeyOfValue()(data) < KeyOfValue()(pCur->_data)))
				pCur = pCur->_pLeft;
			else
				pCur = pCur->_pRight;
		}

		return End();
	}

	Node*& GetRoot()
	{
		return _pHead->_pParent;
	}

	void InOrder()
	{
		_InOrder(GetRoot());
	}

	Node* LeftMost()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;

		Node* pCur = pRoot;
		while (pCur->_pLeft)
			pCur = pCur->_pLeft;

		return pCur;
	}

	Node* RightMost()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return _pHead;

		Node* pCur = pRoot;
		while (pCur->_pRight)
			pCur = pCur->_pRight;

		return pCur;
	}

	bool IsValidRBTRee()
	{
		Node* pRoot = GetRoot();
		if (nullptr == pRoot)
			return true;

		if (pRoot->_color != BLACK)
		{
			cout << "Υ������һ�����ڵ��Ǻ�ɫ" << endl;
			return false;
		}

		// ��ȡһ��·���к�ɫ�ڵ�ĸ���
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (pCur->_color == BLACK)
				blackCount++;

			pCur = pCur->_pLeft;
		}

		size_t pathBalck = 0;
		return _IsValidRBTRee(pRoot, blackCount, pathBalck);
	}

private:
	void _Destroy(Node* & pRoot)
	{
		if (pRoot)
		{
			_Destroy(pRoot->_pLeft);
			_Destroy(pRoot->_pRight);
			delete pRoot;
			pRoot = nullptr;
		}
	}
	bool _IsValidRBTRee(Node* pRoot, size_t blackCount, size_t pathBlack)
	{
		if (nullptr == pRoot)
			return true;

		if (pRoot->_color == BLACK)
			pathBlack++;

		Node* pParent = pRoot->_pParent;
		if (pParent != _pHead &&
			RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "Υ������3�����ܴ�������һ��ĺ�ɫ�ڵ�" << endl;
			return false;
		}

		// Ҷ�ӽڵ�
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (pathBlack != blackCount)
			{
				cout << "Υ������4��ÿ��·���к�ɫ�ڵ��������ͬ" << endl;
				return false;
			}
		}

		return _IsValidRBTRee(pRoot->_pLeft, blackCount, pathBlack) &&
			_IsValidRBTRee(pRoot->_pRight, blackCount, pathBlack);
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
	void RotateL(Node* pParent)
	{
		Node* pSubR = pParent->_pRight;
		Node* pSubRL = pSubR->_pLeft;

		pParent->_pRight = pSubRL;
		if (pSubRL)
			pSubRL->_pParent = pParent;

		pSubR->_pLeft = pParent;
		Node* pPParent = pParent->_pParent;
		pSubR->_pParent = pPParent;
		pParent->_pParent = pSubR;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubR;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubR;
			else
				pPParent->_pRight = pSubR;
		}
	}

	void RotateR(Node* pParent)
	{
		Node* pSubL = pParent->_pLeft;
		Node* pSubLR = pSubL->_pRight;

		pParent->_pLeft = pSubLR;
		if (pSubLR)
			pSubLR->_pParent = pParent;

		pSubL->_pRight = pParent;

		Node* pPParent = pParent->_pParent;
		pParent->_pParent = pSubL;
		pSubL->_pParent = pPParent;

		if (pPParent == _pHead)
			_pHead->_pParent = pSubL;
		else
		{
			if (pParent == pPParent->_pLeft)
				pPParent->_pLeft = pSubL;
			else
				pPParent->_pRight = pSubL;
		}
	}
private:
	Node* _pHead;
	size_t _size;
};