#pragma once
#include "Grup.h"

template<typename T2>
inline iterator_g<T2>::iterator_g(iterator_g& other):vList(other.vList), vHead(other.vHead), vEnd(other.vEnd),sHead(other.sHead),
sEnd(other.sEnd),excepList(other.excepList),line(other.line) {}

template<typename T2>
inline iterator_g<T2>::iterator_g(Grup<T2>* object, bool vLine) : line(vLine)
{
	if (!object)
	{
		throw std::exception("iterator_g(Grup<T2>* object, bool vLine) >> Grup<T2>* object == nullptr");
	}
	vHead  = object->head;
	this->excepList = &object->ExceptionsList;
	this->vEnd = vList  = object->lend;
	this->sEnd = object->SideLend;
	this->sHead = object->SideHead;
}

template<typename T2>
inline iterator_g<T2>::iterator_g(Grup<T2>& object): line(true)
{
	vHead = vList = object.head;
	this->excepList = &object.ExceptionsList;
	this->vEnd = object.lend;
	this->sEnd = object.SideLend;
	this->sHead = object.SideHead;
}

template<typename T2>
inline iterator_g<T2> iterator_g<T2>::begin()
{
	return iterator_g(*this, this->vHead, true);
}

template<typename T2>
inline Node<T2>* iterator_g<T2>::end()
{
	return this->sEnd;
}

template<typename T2>
inline  iterator_g<T2> iterator_g<T2>::rbegin()
{
	return iterator_g(*this, this->vEnd, false);

}

template<typename T2>
inline Node<T2>* iterator_g<T2>::rend()
{
	return this->sHead;
}

template<typename T2>
iterator_g<T2>::iterator_g(iterator_g& other, Node<T2>* set, bool vLine1) : line(vLine1)
{
	this->vList = set;
	this->vHead = other.vHead;
	this->vEnd = other.vEnd;
	this->sHead = other.sHead;
	this->sEnd = other.sEnd;
	this->excepList = other.excepList;
}


template<typename T2>
T2& iterator_g<T2>::operator*()
{
	if (!this->vList->Side)
	{
		if (*this->excepList)
			throw std::exception("<operator*>: went over the edge");
		else
			this->vList = this->vEnd;
	}
	return this->vList->data;
}


template<typename T>
iterator_g<T>& iterator_g<T>::operator++(int)
{
	if (!vList->Side)
	{
		if (*this->excepList)
			throw std::exception("<operator++>: went over the edge");
		else
			return *this;
	}
	(this->line) ? vList = vList->pNext : vList = vList->pLast;
	return *this;
}


template<typename T>
iterator_g<T>& iterator_g<T>::operator++()
{
	if (!vList->Side)
	{
		if (*this->excepList)
			throw std::exception("<operator++>: went over the edge");
		else
			return *this;
	}
	(this->line) ? vList = vList->pNext : vList = vList->pLast;
	return *this;
}

template<typename T>
inline bool iterator_g<T>::operator==(Node<T>* other)
{
	return this->vList == other;
}


template<typename T2>
inline bool iterator_g<T2>::operator!=(Node<T2>* other)
{
	return this->vList != other;
}


template<typename T2>
inline iterator_g<T2>& iterator_g<T2>::operator--()
{
	if (!vList->Side)
	{
		if (*this->excepList)
			throw std::exception("<operator-->: went over the edge");
		else
			return *this;
	}
	(this->line) ? vList = vList->pLast : vList = vList->pNext;
	return *this;
}

template<typename T2>
bool iterator_g<T2>::operator==(iterator_g& other)
{
	return this->vList->data == other.vList->data;
}

template<typename T2>
bool iterator_g<T2>::operator!=(iterator_g& other)
{
	return this->vList->data != other.vList->data;
}