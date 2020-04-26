#pragma once

// 红黑树：二叉搜索树
//        节点中增加颜色：红色 和 黑色
//        条件约束：5条性质
/*
1. 每个节点都有颜色：红色或者黑色
2. 根节点必须为黑色
3. 如果一个节点的颜色是红色的，它的孩子节点一定是黑色的
   红黑树中不会出现连在一起的红色节点
4. 每条路径中黑色节点的个数相同
5. 每个叶子节点都是黑色(此处的叶子节点：树中的空指针域)
*/
// 结论：最长路径中节点个数一定不会超过最短路径中节点个数的两倍
// 因此：红黑树是一棵近似平衡的二叉搜索树
// 红黑树性能比AVL树更佳，而且实现比较简单


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


// 找工作：10月30号
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
			// 找右子树中最左侧节点
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

			// 注意：特殊情况-->根节点没有右孩子，迭代器在根位置
			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}

	// --
	void DeIncreament()
	{
		// 处理迭代器在end的位置
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
		// 按照二叉搜索树的性质插入新节点
		Node* & pRoot = GetRoot();
		if (nullptr == pRoot)
		{
			pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
			return true;
		}
		else
		{
			// 找待插入节点在二叉搜索树中的位置
			// 并保存其双亲节点
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

			// 插入新节点
			pCur = new Node(data);
			if (data < pParent->_data)
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;

			pCur->_pParent = pParent;

			// pCur新节点默认颜色：红色
			// 如果pParent的颜色是黑色的，满足红黑树性质
			// 如果pParent的颜色是红色的，违反了性质三--不能有连在一起的红色节点
			while (pParent != _pHead && pParent->_color == RED)
			{
				Node* grandFather = pParent->_pParent;
				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;
					// 叔叔节点存在且为红
					if (uncle && RED == uncle->_color)
					{
						// 情况一
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						// 叔叔节点不存在 || 叔叔节点存在 && 黑色
						if (pCur == pParent->_pRight)
						{
							// 情况三
							RotateL(pParent);
							swap(pCur, pParent);
						}

						// 情况二：
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateR(grandFather);
					}
				}
				else
				{
					// 一二三的反情况
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
						// 叔叔节点不存在 || 存在且为黑
						if (pCur == pParent->_pLeft)
						{
							// 情况三反情况
							RotateR(pParent);
							swap(pCur, pParent);
						}

						// 情况二的反情况
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
			cout << "违反性质一：根节点是黑色" << endl;
			return false;
		}

		// 获取一条路径中黑色节点的个数
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
			cout << "违反性质3：不能存在连在一起的红色节点" << endl;
			return false;
		}

		// 叶子节点
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (pathBlack != blackCount)
			{
				cout << "违反性质4：每条路径中黑色节点个数均相同" << endl;
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


// 找工作：10月30号
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
			// 找右子树中最左侧节点
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

			// 注意：特殊情况-->根节点没有右孩子，迭代器在根位置
			if (_pNode->_pRight != pParent)
				_pNode = pParent;
		}
	}

	// --
	void DeIncreament()
	{
		// 处理迭代器在end的位置
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


// T: 可能是键值对<key,value>
//    可能是一个key
// 不论节点中存储的是<key, value> || key, 都是按照key来进行比较的
// KeyOfValue: 提取data中的Key
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
		// 按照二叉搜索树的性质插入新节点
		Node* & pRoot = GetRoot();
		Node* pNewNode = nullptr;
		if (nullptr == pRoot)
		{
			pNewNode = pRoot = new Node(data, BLACK);
			pRoot->_pParent = _pHead;
		}
		else
		{
			// 找待插入节点在二叉搜索树中的位置
			// 并保存其双亲节点
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

			// 插入新节点
			pNewNode = pCur = new Node(data);
			if ((KeyOfValue()(data) < KeyOfValue()(pParent->_data)))
				pParent->_pLeft = pCur;
			else
				pParent->_pRight = pCur;

			pCur->_pParent = pParent;

			// pCur新节点默认颜色：红色
			// 如果pParent的颜色是黑色的，满足红黑树性质
			// 如果pParent的颜色是红色的，违反了性质三--不能有连在一起的红色节点
			while (pParent != _pHead && pParent->_color == RED)
			{
				Node* grandFather = pParent->_pParent;
				if (pParent == grandFather->_pLeft)
				{
					Node* uncle = grandFather->_pRight;
					// 叔叔节点存在且为红
					if (uncle && RED == uncle->_color)
					{
						// 情况一
						pParent->_color = BLACK;
						uncle->_color = BLACK;
						grandFather->_color = RED;
						pCur = grandFather;
						pParent = pCur->_pParent;
					}
					else
					{
						// 叔叔节点不存在 || 叔叔节点存在 && 黑色
						if (pCur == pParent->_pRight)
						{
							// 情况三
							RotateL(pParent);
							swap(pCur, pParent);
						}

						// 情况二：
						pParent->_color = BLACK;
						grandFather->_color = RED;
						RotateR(grandFather);
					}
				}
				else
				{
					// 一二三的反情况
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
						// 叔叔节点不存在 || 存在且为黑
						if (pCur == pParent->_pLeft)
						{
							// 情况三反情况
							RotateR(pParent);
							swap(pCur, pParent);
						}

						// 情况二的反情况
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
			cout << "违反性质一：根节点是黑色" << endl;
			return false;
		}

		// 获取一条路径中黑色节点的个数
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
			cout << "违反性质3：不能存在连在一起的红色节点" << endl;
			return false;
		}

		// 叶子节点
		if (nullptr == pRoot->_pLeft && nullptr == pRoot->_pRight)
		{
			if (pathBlack != blackCount)
			{
				cout << "违反性质4：每条路径中黑色节点个数均相同" << endl;
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