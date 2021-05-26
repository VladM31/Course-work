#pragma once
#include "GraduateSD.h"
#include "Node.h"
enum class eList {
	off, on
};
template<typename T2>
class Grup;
template<typename T2>
class iterator_g
{
	
	Node<T2>* vList;//Вказівник ,яки рухається від початку до кінця
	Node<T2>* vHead;//Перший елемент контейнеру групи
	Node<T2>* vEnd;// Останій елемент контейнера групи
	Node<T2>* sHead;// Граничний елемент з початку
	Node<T2>* sEnd;// Граничний елемент з кінця
	bool* excepList;// Вказівник на стан включення "виключень"
	bool line;// Рухатися з верху в низ або з низу в верх
	iterator_g& SetRevers(bool setRevers);//Встановлюю значення
public:
	iterator_g(Grup<T2>* object);// Конструктор з вказівником на Групу
	iterator_g(iterator_g& other);// Конструктор копіювання
	iterator_g(Grup<T2>& object);// Конструктор з об'єктом типа Група
	T2& operator*();// Оператор розеіменування
	iterator_g& operator++(int);// Оператор переміщення в перед
	iterator_g& operator++();// Оператор переміщення в перед
	iterator_g& operator--();// Оператор переміщення в назад
	bool operator==(Node<T2>* other);// Оператор порівнення з нодою
	bool operator!=(Node<T2>* other);// Оператор не равно з нодою
	bool operator==(iterator_g& other);// Оператор порівнення з іншим итератором
	bool operator!=(iterator_g& other);// Оператор не равно з іншим итератором
	iterator_g & operator=(const iterator_g& other);// Оператор присваивания
	iterator_g begin();// Повертає ітератор ,який стоїть на початку й рухається з верху в низ
	Node<T2>* end();
	iterator_g rbegin();// Повертає ітератор ,який стоїть на кінець й рухається з низу в верх
	Node<T2>* rend();
};

template<typename T>
class Grup
{
private:
	std::string Name;
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
	 // Повертає ітератор на початок
	 iterator_g<T> begin();
	 Node<T>* end();
	 // Повертає ітератор на обратний початок
	 iterator_g<T> rbegin();
	 Node<T>* rend();
	 friend iterator_g<T>;
	 // Встановлює значення імені групи 
	 void SetNameGroop(std::string set);
	 // повертає значення імені
	 std::string GetNameGroop();
	 // Повертає істину ,якщо ліст пуст
	 bool empty();
};

template<typename T>
inline bool Grup<T>::empty()
{
	return !this->Size;
}

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
		return false;
	}
	else if (value == eList::on)
	{
		this->ExceptionsList = true;
		return true;
	}
	throw "Введене не правильне значення перелчення eList";
}

template<typename T>
inline iterator_g<T> Grup<T>::begin()
{
	return iterator_g<T>(*this);
}

template<typename T>
inline Node<T>* Grup<T>::end()
{
	return this->SideLend;
}

template<typename T>
iterator_g<T> Grup<T>::rbegin()
{
	return iterator_g<T>(this).rbegin();
}

template<typename T>
inline Node<T>* Grup<T>::rend()
{
	return this->SideHead;
}

template<typename T>
inline bool Grup<T>::ChooseAnOptionFromTheBottomOrTop(size_t index)
{
	return Size / 2 >= index;
}

template<typename T>
Grup<T>::Grup() : Size(0),head(nullptr),lend(nullptr),
SideHead(new Node<T>(false)), SideLend(new Node<T>(false)) {}

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
		head = lend = nullptr;
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
void Grup<T>::removeAt(size_t index){
	if (index == 0){
		pop_front();
	}
	else if (index == Size - 1){
		pop_back();
	}
	else{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++){
			previous = previous->pNext;
			if (previous == nullptr)
			{
				throw std::exception("Metod <removeAt>: Index does not exist");
			}
		}
		if (previous->pNext == nullptr){
			throw std::exception("Metod <removeAt>: Index does not exist");
		}
		if (Size==1){
			Size--;
			delete this->head;
			this->head = this->lend = nullptr;
			return;
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
	if (this == &other)
	{
		return *this;
	}
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

template<typename T>
inline void Grup<T>::SetNameGroop(std::string set)
{
	this->Name = set;
}

template<typename T>
inline std::string Grup<T>::GetNameGroop()
{
	return this->Name;
}