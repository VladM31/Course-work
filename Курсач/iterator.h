#pragma once
#include "Grup.h"

template<typename T2>
inline iterator_g<T2 > & iterator_g<T2>::SetRevers(bool setRevers)
{
	this->line = setRevers;
	return *this;
}

template<typename T2>
inline iterator_g<T2>::iterator_g(iterator_g& other):vList(other.vList), vHead(other.vHead), vEnd(other.vEnd),sHead(other.sHead),
sEnd(other.sEnd),excepList(other.excepList),line(other.line) {}

template<typename T2>
inline iterator_g<T2>::iterator_g(Grup<T2>* object) : line(true)
{
	if (!object)
	{
		throw std::exception("iterator_g(Grup<T2>* object) >> Grup<T2>* object == nullptr");
	}
	vHead  = object->head;
	this->excepList = &object->ExceptionsList;
	this->vEnd = vList  = object->lend;
	this->sEnd = object->SideLend;
	this->sHead = object->SideHead;
}

template<typename T2>
inline iterator_g<T2>::iterator_g(Grup<T2>& object): line(false)
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
	return iterator_g(*this);
}

template<typename T2>
inline Node<T2>* iterator_g<T2>::end()
{
	return (this->line) ? this->sHead :this->sEnd;
}

template<typename T2>
inline iterator_g<T2>& iterator_g<T2>::operator=(const iterator_g<T2>& other)
{
	if (this == &other)
	{
		return *this;
	}
	this->excepList = other.excepList;
	this->line = other.line;
	this->sEnd = other.sEnd;
	this->sHead = other.sHead;
	this->vEnd = other.vEnd;
	this->vHead = other.vHead;
	this->vList = other.vList;
	return *this;
}

template<typename T2>
inline  iterator_g<T2> iterator_g<T2>::rbegin()
{
	return iterator_g(*this).SetRevers(true);

}

template<typename T2>
inline Node<T2>* iterator_g<T2>::rend()
{
	return this->sHead;
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
	vList = (!this->line) ? vList->pNext : vList->pLast;
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
	vList = (!this->line) ? vList->pNext : vList->pLast;
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
	(!this->line) ? vList = vList->pLast : vList = vList->pNext;
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