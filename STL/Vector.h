#pragma once 
#include<iostream>
#include<string.h>
#include<assert.h>

template<class T>
class Vector
{
public:
	typedef T ValueType;
	typedef ValueType* Pointer;
	typedef ValueType* Iterator;
	typedef ValueType& Reference;

	typedef T* Iterator;
	typedef const T* ConstIterator;
	

public:
	Vector()
		:_start(NULL)
		, _finish(NULL)
		, _endofStorage(NULL)
	{}

	size_t Size()
	{
		return _finish - _start;
	}
	size_t Capacity()
	{
		return _endofStorage - _start;
	}

	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}

	bool Empty()
	{
		return Begin() == End();
	}

	Iterator Erase(Iterator& pos)//返回删除数据的下一个元素
	{
		Iterator begin = pos + 1;
		while (begin != _finish)
		{
			*(begin - 1) = *begin;
			begin++;
		}
		--_finish;
		return pos;
	}

	void Insert(Iterator pos, const ValueType& x)//在pos前面插入
	{
		_finish++;
		_CheckExpand();
	
		Iterator next = End();
		Iterator prev=End()-1;
		
		while (prev!=pos)
		{
			*next = *prev;
			prev--;
			next--;
		}
		*(prev+1) = *pos;
		*pos = x;
	}

	void PushBack(const T& x)
	{
		_CheckExpand();

		*_finish = x;
		_finish++;
	}

	void PopBack()
	{
		--_finish;
	}

	ValueType operator[](int index)
	{
		assert(index < Size() && index >= 0);
		return *(_start + index);
	}

protected:
	void _CheckExpand()//检查容量
	{
		if (_finish == _endofStorage)
		{
			size_t size = Size();
			size_t capacity = 2 * size + 1;
			T* tmp = new T[capacity];
			
			if (_start)
				//memcpy(_start, tmp, sizeof(T)*size);//此处不能用memcpy
			{
				for (int i = 0; i < Size(); i++)
				{
					tmp[i] = _start[i];
				}
			}
			_start = tmp;
			_finish = _start + size;
			_endofStorage = _start + capacity;
		}
	}

public:
	Iterator _start;
	Iterator _finish;//指向有效数字的下一个
	Iterator _endofStorage;
};



void testVector()
{
	Vector<int> v;
	v.PushBack(1);
	v.PushBack(3);
	v.PushBack(5);
	v.PushBack(7);
	/*
	for (int i=0; i < v.Size(); i++)
	{
	cout << v[i] << " ";
	}
	cout << endl;

	cout << v.Size() << endl;

	v.PopBack();
	cout << v.Size() << endl;*/

	Vector<int>::Iterator it;
	//it = v.Begin();
	//v.Insert(it, 0);
	//for (int i = 0; i < v.Size(); i++)
	//{
	//	cout << v[i] << " ";
	//}
	//cout << endl;

	it = v.End() - 1;
	v.Erase(it);
	for (int i = 0; i < v.Size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}



