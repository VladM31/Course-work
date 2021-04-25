#pragma once
template<typename T>
class Node
{
public:
	Node* pNext;
	Node* pLast;
	T data;
	bool Side;
	Node(T sdata = T(), Node* sNext = nullptr, Node* sLast = nullptr) :data(sdata), Side(true)
	{
		this->pNext = sNext;
		this->pLast = sLast;
	}
	Node(Node* other) :data(other->data), Side(other->Side), pNext(other->pNext), pLast(other->pLast) {}

	explicit Node(bool sSide) :Side(sSide), pNext(nullptr), pLast(nullptr) {}
};