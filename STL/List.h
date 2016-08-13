#pragma once
#include<iostream>
using namespace std;

template<class T>
struct _ListNode
{
	_ListNode(const T& d=T())
	:_data(d)
	,_next(NULL)
	,_prev(NULL)
	{
	}

	T _data;
	_ListNode<T>* _next;
	_ListNode<T>* _prev;
};

//List的迭代器
template<class T,class Ref,class Ptr>
class _ListIterator
{
public:
	typedef _ListIterator<T,Ref,Ptr> Self;
	typedef _ListNode<T>* LinkType;
	
	_ListIterator(const LinkType Node=NULL)
		:_Node(Node)
	{}

	bool operator==(Self& x)
	{
		return _Node == x._Node;
	}

	bool operator!=(Self& x)
	{
		return _Node != x._Node;
	}


	Ref operator*()
	{
		return _Node->_data;
	}
	Ptr operator->()
	{
		return &(_Node->_data);
	}

	Self& operator++()
	{
		_Node = _Node->_next;
		return *this;
	}

	Self operator++(int)
	{
		Self tmp(_Node);
		_Node = _Node->_next;
		return tmp;
	}

	Self& operator--()
	{
		_Node = _Node->_next;
		return *this;
	}

	Self operator--(int)
	{
		Iterator tmp(_Node);
		_Node = _Node->_prev;
		return tmp;
	}

	LinkType _Node;//指向节点的指针
};


template<class T>
class List//设计成双向循环链表
{
public:
	typedef _ListNode<T> Node;
	typedef _ListIterator<T,T&,T*> Iterator;
	typedef _ListIterator<T, const T&, const T*> ConstIterator;
	typedef _ListIterator<T, T&, T*> ReverseIterator;
	typedef _ListIterator<const T, const T&,const T*> ReverseConstIterator;

	typedef T ValueType;
	typedef T& Reference;
	typedef T* Pointer;
	typedef const T* ConstPointer;
	typedef const T& ConstReference;
	typedef int DifferenceType;

public:
	List()
		:_head(new _ListNode<T>())
	{
		_head->_next = _head;
		_head->_prev = _head;
	}

	//在pos之前插入一个节点
	void Insert(Iterator pos, const ValueType& x)
	{
		Node* tmp = new _ListNode<T>(x);
		Node* prev = pos._Node->_prev;
		Node* cur = pos._Node;

		prev->_next = tmp;
		tmp->_prev = prev;
		tmp->_next = cur;
		cur->_prev = tmp;
	}


	void PushBack(const ValueType& x)
	{
		Insert(End(), x);
	}

	void PushFront(const ValueType& x)
	{
		Insert(Begin(), x);
	}

	void PopBack()
	{
		Erase(--End());
	}

	void PopFront()
	{
		Erase(Begin());
	}

	//ConstIterator Begin()const 
	//{
	//	return ConstIterator(_head->_next);
	//}

	ReverseIterator Rbegin()
	{
		return ReverseIterator(End());
	}
	ReverseIterator Rend()
	{
		return ReverseIterator(Begin());
	}
	ReverseIterator Rbegin()const
	{
		return ReverseIterator(End());
	}
	ReverseIterator Rend()const
	{
		return ReverseIterator(Begin());
	}

	Iterator Begin()
	{
		return _head->_next;
	}

	Iterator End()
	{
		return _head;
	}
	Iterator Erase(Iterator pos)//删除pos所指向的节点，返回pos后面的一个节点
	{
		Node* cur = pos._Node;
		Node*  prev = pos._Node->_prev;
		Node* next = pos._Node->_next;

		prev->_next = next;
		next->_prev = prev;
		delete pos._Node;

		return Iterator(next);
	}

	bool Empty()
	{
		if (_head->_next == _head)
			return true;
		else
			return false;
	}
	size_t Size()
	{
		size_t count = 0;
		Node* start = _head;
		do
		{
			count++;
			start = start->_next;
		} while (start != _head);

		return count-1;
	}

private:
	Node* _head;
};

void Printf(List<int> l)
{
	List<int>::Iterator it;
	it = l.Begin();
	cout << *it << endl;
}
//
//void Printf1(const List<int>& l)
//{
//	List<int>::ConstIterator it;
//	it = l.Begin();
//
//	cout << *it << endl;
//}

void Printf2(List<int>& l)
{
	List<int>::ReverseIterator it;
	it = l.Rend();
	cout << *it << endl;
}

void Printf3(const List<int>& l)
{
	List<int>::ReverseConstIterator it;
}

void testList()
{
	List<int> l;
	l.PushBack(1);
	l.PushBack(3);
	l.PushBack(5);
	l.PushBack(7);

	Printf(l);

//	Printf1(l);

	//Printf2(l);
	//Printf3(l);
}