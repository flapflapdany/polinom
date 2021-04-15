#ifndef __LIST_H__
#define __LIST_H__
#include <iostream>
using namespace std;

const int MaxSize = 1000;

template<class T>
class Node
{
public:
	Node * pNext;
	T data;
	Node *pPrev;
	Node(T data1 = {})
	{
		data = data1;
		pNext = nullptr;
	}
	Node(T data1, Node * pNext1)
	{
		data = data1;
		pNext = pNext1;
	}
};

template<class T>
class List
{
protected:
	int Size;
	Node<T> *pFirst;
public:

	List() :Size(0)
	{
		pFirst = nullptr;
	}
	List(const List<T> &list)
	{
		Size = list.Size;
		pFirst = nullptr;
		for (Node<T> *res = list.pFirst; res != nullptr; res = res->pNext)
		{
			PushBack(res->data);
		}
	}
	List(Node<T>* p)
	{
		pFirst = p;
		pFirst->next = pFirst;
		Size = 0;
	}
	~List()
	{
		while (pFirst != nullptr)
		{
			Node<T> *res = pFirst;
			pFirst = pFirst->pNext;
			delete res;
		}
	}
	int GetSize() { return Size; }
	bool IsEmpty() { return pFirst == nullptr; }
	List<T>& operator=(const List<T> &list);
	bool operator==(const List<T> &list);
	bool operator!=(const List<T> &list);
	void PushBack(T key);
	void DeleteAllNodes();
	void Insert1(Node<T>* previousNode, T val);

	class LinkPointer
	{
	protected:
		Node<T> *pointer;
	public:
		LinkPointer()
		{
			pointer = new Node<T>;
		}
		LinkPointer(const LinkPointer &i)
		{
			pointer = i.pointer;
		}
		Node<T>* operator->() const { return pointer; }  
		Node<T>* GetIntenge()
		{
			return pointer;
		}
		LinkPointer& operator=(const LinkPointer &p)
		{
			pointer = p.pointer;
			return *this;
		}
		LinkPointer& operator ++()                    
		{
			this->pointer = this->pointer->pNext;
			return *this;
		}
		bool operator==(const LinkPointer &l);
		bool operator!=(const LinkPointer &l);
		T operator&()const;
		void Change(T _data);
		friend List;
	};
	LinkPointer Begin()
	{
		LinkPointer n;
		n.pointer = pFirst;
		return n;
	}

	LinkPointer End()
	{
		LinkPointer n;
		Node<T> *res = pFirst;
		if (!IsEmpty())
		{
			while (res->pNext != nullptr)
			{
				res = res->pNext;
			}
			n.pointer = res->pNext;
		}
		else
			n.pointer = pFirst;
		return n;
	}
	void Insert(LinkPointer i, T val);    //вставка по указателю
	void RemoveAt(LinkPointer i);   //удаление по указателю
};

template<class T>
inline bool List<T>::LinkPointer::operator==(const LinkPointer & l)
{
	return (pointer == l.pointer);
}


template<class T>
inline bool List<T>::LinkPointer::operator!=(const LinkPointer & l)
{
	return (pointer != l.pointer);
}

template<class T>
inline T List<T>::LinkPointer::operator&() const
{
	if (pointer == nullptr)
		throw "Error";
	return pointer->data;
}

template<class T>
inline void List<T>::LinkPointer::Change(T _data)
{
	pointer->data = _data;
}

template<class T>
inline List<T>& List<T>::operator=(const List<T>& list)
{
	DeleteAllNodes();
	Node<T> *res = list.pFirst;
	while (res != nullptr)
	{
		PushBack(res->data);
		res = res->pNext;
	}
	return *this;
}

template<class T>
inline bool List<T>::operator==(const List<T>& list)
{
	if (list.Size != Size)
		return 0;
	Node<T> *res1 = pFirst;
	Node<T> *res2 = list.pFirst;
	while (res1 != nullptr)
	{
		if (res1->data == res2->data)
		{
			res1 = res1->pNext;
			res2 = res2->pNext;
		}
		else
			return 0;
	}
	return 1;
}

template<class T>
inline void List<T>::Insert(LinkPointer i, T val)
{
	Node<T> *tmp = pFirst;
	Node<T> *prev;
	Node<T> *insert = new Node<T>(val);
	int m = 0;
	while (tmp != i.pointer)
	{
		prev = tmp;
		tmp = tmp->pNext;
		m++;
	}
	if (m == 0)
	{
		insert->pNext = tmp;
		pFirst = insert;
		Size++;
	}
	else
	{
		insert->pNext = tmp;
		prev->pNext = insert;
		Size++;
	}
}

template<class T>
inline void List<T>::Insert1(Node<T> *previousNode, T val)
{
	if (previousNode == nullptr)
	{
		Node<T>* tmp = new Node<T>(val, pFirst);
		pFirst = tmp;
	}
	else
	{
		Node<T>* tmp = new Node<T>(val, previousNode->pNext);
		previousNode->pNext = tmp;
	}
	Size++;
}

template<class T>
inline void List<T>::DeleteAllNodes()
{
	while (pFirst != nullptr)
	{
		Node<T> *res = pFirst;
		pFirst = pFirst->pNext;
		delete res;
	}
}

template<class T>
inline void List<T>::PushBack(T key)
{
	Size++;
	if (IsEmpty())
	{
		Node<T> *res = new Node<T>;
		res->data = key;
		pFirst = res;
	}
	else
	{
		if (Size > (MaxSize-1))
			throw "Error";
		Node<T> *res = pFirst;
		while (res->pNext != nullptr)
		{
			res = res->pNext;
		}
		Node<T> *tmp = new Node<T>;
		tmp->data = key;
		tmp->pPrev = res;
		res->pNext = tmp;
	}
}

template<class T>
void List<T>::RemoveAt(LinkPointer i)
{
	Node<T> *tmp = pFirst;
	Node<T> *prev;
	int l = 0;
	while (tmp != i.pointer)
	{
		prev = tmp;
		tmp = tmp->pNext;
		l++;
	}
	if (l == 0)
	{
		pFirst = pFirst->pNext;
		delete tmp;
		Size--;
	}
	else
	{
		prev->pNext = tmp->pNext;
		delete tmp;
		Size--;
	}
}

template<class T>
inline bool List<T>::operator!=(const List<T>& list)
{
	return !(*this == list);
}

#endif