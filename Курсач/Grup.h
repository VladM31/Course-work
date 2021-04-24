#pragma once
#include "GraduateSD.h"
enum class eList {
	off, on
};
template<typename T>
class iterator_g;

template<typename T>
class Grup
{
private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		Node* pLast;
		T data;
		bool Side;
		Node(T sdata = T(), Node* sNext = nullptr, Node* sLast = nullptr):data(sdata),Side(true)
		{
			this->pNext = sNext;
			this->pLast = sLast;
		}
		Node(Node *other) :data(other->data), Side(other->Side),pNext(other->pNext),pLast(other->pLast) {}

		explicit Node(bool sSide) :Side(sSide), pNext(nullptr), pLast(nullptr) {}
	};
	bool ExceptionsList = false;
	
	size_t Size;
	Node<T>* head;
	Node<T>* lend;

	Node<T>* SideHead;
	Node<T>* SideLend;
	//Виберіть варіант знизу або зверху
	bool ChooseAnOptionFromTheBottomOrTop(size_t index);
 public:
	 Grup();
	 ~Grup();
	 Grup(const Grup& other);
	 //удаление первого элемента в списке
	 void pop_front();
	 //удаление элемента в списке по указанному индексу
	 void removeAt(size_t index);
	 //удаление последнего элемента в списке
	 void pop_back();
	 // очистить список
	 void clear();
	 // получить количество елементов в списке
	 size_t GetSize() { return Size; }
	 // перегруженный оператор [] 
	 T& operator[](const size_t index);
	 //добавление элемента в начало списка
	 void push_front(T data );
	 //добавление элемента в конец списка
	 void push_back(T data );
	 //добавление элемента в список по указанному индексу
	 void insert(T data, size_t index);
	 // Присваює ліст
	 Grup<T>& operator=(Grup<T>& asd);
	 // зрівнює два листа
	 bool operator==(const Grup<T>& Asd);
	 // зрівнює два листа на не совпадение 
	 bool operator!=(const Grup<T>& Asd);
	 // Виключає винятки або включає
	 bool SetExceptionsInList(eList);
	 template<typename T2>
	 class iterator_g
	 {
		 Node<T2>* vList;
		 Node<T2>* vHead;
		 Node<T2>* vEnd;
		 Node<T2>* sHead;
		 Node<T2>* sEnd;
		 bool* excepList;
		 bool line = true;
		 iterator_g(iterator_g&other, Node<T2>* set,bool vLine);
	 public:
		 iterator_g(Grup<T2>& object);
		 T2& operator*();
		 iterator_g& operator++(int);
		 iterator_g& operator++();
		 iterator_g& operator--();
		 bool operator==(Node<T2>* other);
		 bool operator!=(Node<T2>* other);
		 bool operator==(iterator_g &other);
		 bool operator!=(iterator_g &other);
		 iterator_g begin();
		 Node<T2>* end();
		 iterator_g rbegin();
		 Grup<T>::Node<T2>* rend();

	 };
};



template<typename T>
bool Grup<T>::operator==(const Grup<T>& other)
{
	if (this->Size != other.Size)
	{
		return false;
	}
	Node<T>* tempThis = this->head;
	Node<T>* tempOther = other.head;
	while (!tempThis->Side)
	{
		if (tempThis->data != tempOther->data)
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline bool Grup<T>::operator!=(const Grup<T>& Asd)
{
	return !this->operator==(Asd);
}

template<typename T>
inline bool Grup<T>::SetExceptionsInList(eList value)
{
	if (value == eList::off)
	{
		this->ExceptionsList = false;
		return true;
	}
	else if (value == eList::on)
	{
		this->ExceptionsList = true;
		return true;
	}
	return false;
}

template<typename T>
inline bool Grup<T>::ChooseAnOptionFromTheBottomOrTop(size_t index)
{
	return Size / 2 >= index;
}

template<typename T>
Grup<T>::Grup() : Size(0),head(nullptr),lend(nullptr),
SideHead(new Node<T>(false)), SideLend(new Node<T>(false)){}

template<typename T>
inline Grup<T>::Grup(const Grup& other): Size(0),head(nullptr), 
lend(nullptr), SideHead(new Node<T>(false)), SideLend(new Node<T>(false))
{
	if (other.head)
	{
		Node<T> run(other.head);
		for (size_t i = 0; run.Side; i++)
		{
			this->push_back(run.data);
			run = run.pNext;
		}
	}

}

template<typename T>
Grup<T>::~Grup()
{
	clear();
	delete SideHead, SideLend;
}

template<typename T>
void Grup<T>::pop_front()
{
	Node<T>* temp = head;

	head = head->pNext;
	head->pLast = SideHead;
	delete temp;

	Size--;
	if (!Size)
	{
		lend = nullptr;
	}
}

template<typename T>
void Grup<T>::pop_back()
{
	if (!Size)//Size==0
	{
		if (this->ExceptionsList)
		{
			throw std::exception("Metod <pop_back>: Size == 0");
		}
		return;
	}
	else if (Size == 1)
	{
		delete lend;
		head = lend = nullptr;
	}
	else {
		Node<T>* toDelete = lend;
		lend = lend->pLast;
		lend->pNext = SideLend;
		delete toDelete;
	}
	Size--;
}

template<typename T>
void Grup<T>::push_back(T data )
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
		lend = head;
		head->pLast = SideHead;
		lend->pNext = SideLend;
	}
	else
	{
		lend->pNext = new Node<T>(data, nullptr, lend);
		lend = lend->pNext;
	    lend->pNext = SideLend;
	}
	Size++;
}

template<typename T>
T& Grup<T>::operator[](const size_t index)
{
	size_t counter = 0;
	if (index >= Size)
	{
		throw std::exception("Metod <insetr>: index>= Size or index<0");
	}
	if (this->ChooseAnOptionFromTheBottomOrTop(index))
	{


		Node<T>* current = this->head;

		while (current->Side)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
		throw std::exception("Index does not exist");
	}
	else
	{
		int new_index = Size - index - 1;
		Node<T>* current_end = this->lend;
		while (current_end->Side)
		{
			if (counter == new_index)
			{
				return current_end->data;
			}
			current_end = current_end->pLast;
			counter++;
		}
	}
	return head->data;
}

template<typename T>
void Grup<T>::push_front(T data )
{
	if (head == nullptr)
	{
		head = new Node<T>(data, head);
		lend = head;
		lend->pNext = SideLend;
		head->pLast = SideHead;
	}
	else
	{
		head = new Node<T>(data, head);
		head->pNext->pLast = head;
		head->pLast = SideHead;
	}
	Size++;
}

template<typename T>
void Grup<T>::insert(T data, size_t index)
{
	if (index > Size)
	{
		if (this->ExceptionsList)
		{
			throw std::exception("Metod <insetr>: index> Size");
		}
		return;
	}
	if (!index)//index == 0
	{
		push_front(data);
	}
	else if (index == Size)
	{
		lend->pNext = new Node<T>(data, nullptr, lend);
		lend = lend->pNext;
		Size++;
	}
	else
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext, previous);
		previous->pNext->pLast = newNode;
		previous->pNext = newNode;

		Size++;
	}

}

template<typename T>
void Grup<T>::removeAt(size_t index)
{
	if (index == 0)
	{
		pop_front();
	}
	else if (index == Size - 1)
	{
		pop_back();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
			if (previous == nullptr)
			{
				throw std::exception("Metod <removeAt>: Index does not exist");
			}
		}
		if (previous->pNext == nullptr)
		{
			throw std::exception("Metod <removeAt>: Index does not exist");
		}

		Node<T>* toDelete = previous->pNext;

		previous->pNext = toDelete->pNext;

		toDelete->pNext->pLast = previous;
		delete toDelete;

		Size--;
	}

}

template<typename T>
inline Grup<T>& Grup<T>::operator=(Grup<T>& other)
{
	if (head)
	{
		this->clear();
	}
	Node<T>* temp = other.head;
	for (size_t i = 0; i < other.Size; i++)
	{
		this->push_back(temp->data);
		temp = temp->pNext;
	}
	
	return *this;
}

template<typename T>
void Grup<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
	this->head = nullptr;
	this->lend = nullptr;
}