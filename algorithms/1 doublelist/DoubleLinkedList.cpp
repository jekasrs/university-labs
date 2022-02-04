#include "DoubleLinkedList.h"
//  DoubleLinkedList.cpp - Дважды связный список целых чисел - реализация методов класса  
//
#include <iostream>
#include <fstream>

// Конструктор "копирования" – создание копии имеющегося списка
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& src) {

	// std::cout << "Вызвался копирование " << std::endl;
	head_ = nullptr;
	tail_ = nullptr;
	count_ = 0;

	// Голова списка, из которого копируем:
	Node* temp = src.head_;

	// Пока не конец списка:
	while (temp != nullptr)
	{   // Передираем данные:
		this->insertTail(temp->item_);
		temp = temp->next_;
	}
}

// Конструктор "перемещения" принимаем в качестве параметра ссылку rvalue reference
DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& src) noexcept :
	count_(src.count_)
	, head_(src.head_)
	, tail_(src.tail_)
{
	// std::cout << "Вызвался перемещение" << std::endl;
	src.count_ = 0;
	src.head_ = nullptr;
	src.tail_ = nullptr;
}

void DoubleLinkedList::swap(DoubleLinkedList& list) {
	std::swap(head_, list.head_);
	std::swap(tail_, list.tail_);
	std::swap(count_, list.count_);
}
// равно копирование
DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList& list)
{
	// std::cout << "Вызвался копирование =" << std::endl;
	DoubleLinkedList tmp(list);
	this->swap(tmp);
	return *this;
}
// равное пермещение 
DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& list) noexcept
{
	// std::cout << "Вызвался пермещение = " << std::endl;
	this->swap(list);
	list.head_ = nullptr;
	list.tail_ = nullptr;
	list.count_ = 0;
	return *this;
}

// Вставить сформированный узел в хвост списка
void DoubleLinkedList::insertTail(Node* x)
{
	// task 5 
	x->prev_ = tail_;
	if (tail_ == nullptr) {
		// список был пуст – новый элемент будет и первым, и последним
		head_ = x;
	}
	else {
		tail_->next_ = x;
	}
	tail_ = x;
	count_++;  // число элементов списка увеличилось
}

// Вставить сформированный узел в начало списка
void DoubleLinkedList::insertHead(Node* x)
{
	x->next_ = head_;
	if (head_ != nullptr) {
		// список был НЕ пуст – новый элемент будет и первым, и последним
		head_->prev_ = x;
	}
	else {
		// список был пуст – новый элемент будет и первым, и последним
		tail_ = x;
	}
	head_ = x;
	count_++;  // число элементов списка увеличилось
}

// Удаление заданного узла 
void DoubleLinkedList::deleteNode(Node* x)
{
	if (x == nullptr) {
		throw ("DoubleLinkedList::deleteNode  - неверно задан адрес удаляемого узла");
	}
	if (x->prev_ != nullptr) {
		// удаляется НЕ голова списка
		(x->prev_)->next_ = x->next_;
	}
	else {
		// удаляется голова списка,  второй элемент становится первым
		head_ = x->next_;
	}
	if (x->next_ != nullptr) {
		// удаляется НЕ хвост
		(x->next_)->prev_ = x->prev_;
	}
	else {
		// удаляется хвост
		tail_ = x->prev_;
	}
	delete x;      // 
	count_--;     // число элементов списка уменьшилось
}

// Поиск узла (адрес) с заданным значением  
DoubleLinkedList::Node* DoubleLinkedList::searchNode(int item)
{
	Node* x = head_;
	while (x != nullptr && x->item_ != item) {
		x = x->next_;
	}
	return x;
}

// Замена информации узла на новое 
DoubleLinkedList::Node* DoubleLinkedList::replaceNode(DoubleLinkedList::Node* x, int item)
{
	// task 6
	x->item_ = item;
	return x;
}

// Доступ к информации головного узла списка
int DoubleLinkedList::headItem() const
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - список пуст!");
}
int& DoubleLinkedList::headItem()
{
	if (head_ != nullptr) {
		return head_->item_;
	}
	throw ("headItem - список пуст!");
}

// Доступ к информации хвостового узла списка
int DoubleLinkedList::tailItem() const
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - список пуст!");
}
int& DoubleLinkedList::tailItem()
{
	if (tail_ != nullptr) {
		return tail_->item_;
	}
	throw ("tailItem - список пуст!");
}

// Вставить элемент в голову списка
void DoubleLinkedList::insertHead(int item)
{   // создаем новый элемент списка и добавляем в голову 
	insertHead(new Node(item));
}

// Вставить элемент в хвост списка
void DoubleLinkedList::insertTail(int item)
{   // создаем новый элемент списка и добавляем в хвост 
	insertTail(new Node(item));
}

// Удалить элемент с головы списка
bool DoubleLinkedList::deleteHead()
{
	if (head_ == nullptr) {
		return 0;  // список пуст, удалений нет
	}
	deleteNode(head_);
	return 1;      // список был НЕ пуст, удаление головы
}

// Удалить элемент из хвоста списка
bool DoubleLinkedList::deleteTail()
{
	// task 7
	if (tail_ == nullptr) {
		return 0;  // список пуст, удалений нет
	}
	deleteNode(tail_);
	return 1;
}

// Удаление узла с заданным значением  
bool DoubleLinkedList::deleteItem(const int item)
{
	// task 8
	if (searchItem(item) == false) {
		return false;
	}
	else {
		Node* prevDdel = this->head_;
		while (prevDdel->item_ != item) {
			prevDdel = prevDdel->next_;
		}
		deleteNode(prevDdel);
	}
	return true;
}

// Поиск записи с заданным значением  
bool DoubleLinkedList::searchItem(int item)
{   // возвращаем TRUE, если узел найден 
	return (searchNode(item) != nullptr);
}

// Замена информации узла на новое 
bool DoubleLinkedList::replaceItem(int itemOld, int itemNew, bool all)
{
	// если нужно заменить на одно значение 
	if (!all) {
		if (itemOld == itemNew) {
			return true;
		}
		else if (searchItem(itemOld) == false) {
			return false;
		}
		else {
			Node* prevDdel = this->head_;
			while (prevDdel->item_ != itemOld) {
				prevDdel = prevDdel->next_;
			}
			replaceNode(prevDdel, itemNew);
		}
		
	}
	else{
		Node* prevDdel = this->head_;
		while (prevDdel->next_!= nullptr) {
			replaceNode(prevDdel, itemNew);
			prevDdel = prevDdel->next_;
		}
		replaceNode(prevDdel, itemNew);
	}
	return true;
}

// Вывод элементов списка в текстовом виде в стандартный выходной поток 
void DoubleLinkedList::outAll()
{
	Node* current = head_;       // Указатель на элемент
	while (current != nullptr) {
		std::cout << current->item_ << ' ';
		current = current->next_;  // Переход к следующему элементу
	}
	std::cout << std::endl;
}

bool DoubleLinkedList::operator==(const DoubleLinkedList& list)
{
	Node* l = this->head_;
	Node* r = list.head_;
	if (this->count_ != list.count_) {
		return false;
	}
	else {
		if (l->item_ != r->item_) return false;
		while (l->item_ == r->item_ && l->next_ != nullptr) {
			if (l->item_ != r->item_) {
				return false;
			}
			l = l->next_; r = r->next_;
		}
	}
	return true;
}

// Деструктор списка	
DoubleLinkedList::~DoubleLinkedList()
{
	// std::cout << "Вызвался деструктор" << std::endl;
	Node* current = nullptr;   // указатель на элемент, подлежащий удалению
	Node* next = head_;        // указатель на следующий элемент
	while (next != nullptr) {  // пока есть еще элементы в списке
		current = next;
		next = next->next_;    // переход к следующему элементу
		delete current;        // освобождение памяти
	}
}

std::ostream& operator<<(std::ostream& out, DoubleLinkedList list)
{
	DoubleLinkedList::Node* current = list.head_;       // Указатель на элемент
	while (current != nullptr) {
		out << current->item_ << ' ';
		current = current->next_;  // Переход к следующему элементу
	}
	out << std::endl;
	return out;
}

// task  12 
void DoubleLinkedList::AddList(DoubleLinkedList& src) {
	if (src == *this) {

	}
	else {
		Node* noder = src.head_;
		while (noder != nullptr) {
			this->insertTail(noder);
			noder = noder->next_;

		}
		src.count_ = 0;
		src.head_ = nullptr;
		src.tail_ = nullptr;
	}
}