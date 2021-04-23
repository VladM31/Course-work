#pragma once
enum class eList {
	off , on
};
template<typename T>
struct DList
{
private:
	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		Node* pLast;
		T data;

		Node(T data = T(), Node* pNext = nullptr ,Node* pLast = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pLast = pLast;
		}
		
	};
	bool ExceptionsList = false;
	size_t Size;
	Node<T>* head;
	Node<T>* lend;
	//Виберіть варіант знизу або зверху
	bool ChooseAnOptionFromTheBottomOrTop(size_t index);
public:
	DList() : Size(0), head(nullptr), lend(nullptr) {};
	~DList();
	//удаление первого элемента в списке
	void pop_front();
	//добавление элемента в конец списка
	void push_back(T data);
	// очистить список
	void clear();
	// получить количество елементов в списке
	size_t GetSize() { return Size; }
	// перегруженный оператор [] 
	T& operator[](const int index);
	//добавление элемента в начало списка
	void push_front(T data);
	//добавление элемента в список по указанному индексу
	void insert(T data, size_t index);
	//удаление элемента в списке по указанному индексу
	void removeAt(size_t index);
	// удаление элемента в списке по указанному значению
	bool removeData(T data);
	//удаление последнего элемента в списке
	void pop_back();
	// Присваює ліст
	DList<T>& operator=(DList<T>& asd);
	// зрівнює два листа
	bool operator==(const DList<T>& Asd);
	// зрівнює два листа на не совпадение 
	bool operator!=(const DList<T>& Asd);
	// Виключає винятки або включає
	bool SetExceptionsInList(eList);
	// добавить елемент по индексу
	T& operator + (size_t pos);
};

template<typename T>
bool DList<T>::operator==(const DList<T>& other)
{
	if (this->Size != other.Size)
	{
		return false;
	}
	Node<T>* tempThis = this->head;
	Node<T>* tempOther = other.head;
	while (tempThis != nullptr)
	{
		if (tempThis->data != tempOther->data)
		{
			return false;
		}
	}
	return true;
}

template<typename T>
inline bool DList<T>::operator!=(const DList<T>& Asd)
{
	return !this->operator==(Asd);
}


template<typename T>
inline bool DList<T>::SetExceptionsInList(eList value)
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
inline T& DList<T>::operator+(size_t pos)
{
	this->insert(pos,pos);
	return this->operator[](pos);
}

template<typename T>
inline bool DList<T>::ChooseAnOptionFromTheBottomOrTop(size_t index)
{
	return Size / 2 >= index;

}

template<typename T>
DList<T>::~DList()
{
	clear();
}

template<typename T>
void DList<T>::pop_front()
{
	Node<T>* temp = head;

	head = head->pNext;

	delete temp;

	Size--;
	if (!Size)
	{
		lend = nullptr;
	}
}

template<typename T>
void DList<T>::push_back(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
		lend = head;
	}
	else
	{
		if (!lend)
		{
			Node<T>* pushNext = this->head;
			while (pushNext->pNext != nullptr)
			{
				pushNext = pushNext->pNext;
			}
			pushNext->pNext = new Node<T>(data, nullptr, pushNext);
		}
		else
		{
			lend->pNext = new Node<T>(data, nullptr, lend);
			lend = lend->pNext;
		}
		
	}
	Size++;
}

template<typename T>
void DList<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
T& DList<T>::operator[](const int index)
{
	int counter = 0;
	if (index<0 || index>=Size)
	{
		throw std::exception("Metod <insetr>: index>= Size or index<0");
	}
	if (this->ChooseAnOptionFromTheBottomOrTop(index))
	{
		

		Node<T>* current = this->head;

		while (current != nullptr)
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
		int new_index = Size  - index-1;
		Node<T>* current_end = this->lend;
		while (current_end != nullptr)
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
void DList<T>::push_front(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data, head);
		lend = head;
	}
	else
	{
		head = new Node<T>(data, head);
		head->pNext->pLast = head;
	}

	Size++;
}

template<typename T>
void DList<T>::insert(T data, size_t index)
{
	if (index>Size)
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
	else if (index==Size)
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
void DList<T>::removeAt(size_t index)
{
	if (index == 0)
	{
		pop_front();
	}
	else if (index == Size-1)
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
bool DList<T>::removeData(T data)
{
	if (!Size)
	{
		if (this->ExceptionsList)
		{
			throw std::exception("Metod <removeData>: Size == 0");
		}
		return false;
	}
	Node<T>* previous = this->head;
	Node<T>* toDelete = this->head;
	for (int i = 0; toDelete->data != data; i++)
	{
		previous = toDelete;
		toDelete = toDelete->pNext;
		if (!toDelete->pNext && toDelete->data == data)
		{
			break;
		}
		if (!toDelete->pNext && toDelete->data != data)
		{
			return false;
		}
	}

	if (Size == 1)
	{
		delete head;
		head = lend = nullptr;
	}
	else
	{
		previous->pNext = toDelete->pNext;
		toDelete->pNext->pLast = previous;
		delete toDelete;
	}
	Size--;
	return true;
}

template<typename T>
void DList<T>::pop_back()
{
	if (!Size)//Size==0
	{
		if (this->ExceptionsList)
		{
			throw std::exception("Metod <pop_back>: Size == 0");
		}
		return;
	}
	else if (Size==1)
	{
		delete lend;
		head = lend = nullptr;
	}
	else {
		Node<T>* toDelete = lend;
		lend = lend->pLast;
		lend->pNext = nullptr;
		delete toDelete;
	}
	Size--;
}


template<typename T>
inline DList<T>& DList<T>::operator=(DList<T>& other)
{
	if (head)
	{
		this->clear();
	}
	Node<T> *temp = other.head;
	for (size_t i = 0; i < other.Size; i++)
	{
		this->push_back(temp->data);
		temp = temp->pNext;
	}
	return *this;
}

