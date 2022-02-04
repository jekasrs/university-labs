#include <iostream>
#include <fstream>
#include "SinglyLinkedOrderedList.h"

// создать пустой словарь 
template<typename T>
SinglyLinkedOrderedList<T>::SinglyLinkedOrderedList()
{
	head_ = nullptr;
	count_ = 0;
}

// Добавить запись в словарь, обеспечивая лексико-графическую упорядоченность
template<typename T>
void SinglyLinkedOrderedList<T>::insertItem(T data)
{

	if (head_ == nullptr)
	{
		head_ = new Node<T>(data);
		count_++;
	}
	else
	{
		Node<T>* current = head_;
		Node<T>* tmp = current;

		while (current and (data >= current->item_))
		{
			tmp = current;
			current = current->next_;
		}

		if (tmp->item_ != data)
		{
			Node<T>* newElement = new Node <T>(data);

			if (current == head_)
			{
				newElement->next_ = head_;
				head_ = newElement;
			}

			else
			{
				// разрыв связи между tmp и cur
				newElement->next_ = current;
				tmp->next_ = newElement;
			}
			count_++;
			
		}


	}
}

// Найти слово в словаре
template<typename T>
bool SinglyLinkedOrderedList<T>::searchItem(T data)
{
	return (searchNode(data) != nullptr);
}

template<typename T>
SinglyLinkedOrderedList<T>::Node<T>* SinglyLinkedOrderedList<T>::searchNode(T data)
{
	Node<T>* temp = head_;

	while ((temp != nullptr) && (temp->item_ != data))
	{
		temp = temp->next_;
	}

	return temp;
}

// Удалить слово из словаря.
template<typename T>
bool SinglyLinkedOrderedList<T>::deleteItem(T data)
{
	if(searchNode(data)){
	deleteNode(searchNode(data));
	return true;
	}
	return false;
}

template<typename T>
void SinglyLinkedOrderedList<T>::deleteNode(Node<T>* data)
{
	Node<T>* cur = head_;

	// если голова 
	if (cur->item_ == data->item_) {
		head_ = head_->next_;
		delete cur;
		count_--;
	}

	else {

		if (data == nullptr)
		{
			throw ("SinglyLinkedList::deleteNode - неверно задан адрес удаляемого узла");
		}

		else
		{
			while (cur->next_ != nullptr)
			{
				if ((cur->next_)->item_ == data->item_)
				{
					Node<T>* deleted = cur->next_;
					cur->next_ = (cur->next_)->next_;
					delete deleted;
					deleted = nullptr;
					break;
				}
				cur = cur->next_;
			}
			count_--;
		}
	}
}

// первое задание 
template<typename T>
void SinglyLinkedOrderedList<T>::addList(SinglyLinkedOrderedList& other)
{
	Node<T>* current = other.head_;
	while (current != nullptr)
	{
		this->insertItem(current->item_);
		current = current->next_;
	}
	current = other.head_;
	Node<T>* temp = current;
	while (current != nullptr)
	{
		temp = current;
		current = current->next_;
		delete temp;
	}
	other.head_ = nullptr;
}

// второе задание 
template<typename T>
void SinglyLinkedOrderedList<T>::substractionList(SinglyLinkedOrderedList& other)
{
	Node<T>* temp = nullptr;
	Node<T>* next = other.head_;
	while (next != nullptr)
	{
		temp = next;
		if (this->searchItem(temp->item_) == 1)
			this->deleteItem(temp->item_);
		next = next->next_;
	}
}

// третье задание 
template<typename T>
SinglyLinkedOrderedList<T> mergeList(SinglyLinkedOrderedList<T>& list1, SinglyLinkedOrderedList<T>& list2)
{
	SinglyLinkedOrderedList<T> list3;
	// SinglyLinkedOrderedList<T>::Node<T>* current = list2.head_;

	while (list2.head_ != nullptr)
	{
		if (list1.searchItem(list2.head_->item_))
		{
			list3.insertItem(list2.head_->item_);
		}
		list2.head_ = list2.head_->next_;
	}

	return list3;
}
template<typename T>
SinglyLinkedOrderedList<T>::SinglyLinkedOrderedList<T>(SinglyLinkedOrderedList<T>&& src) noexcept
{
	head_ = nullptr;
	head_ = src.head_;
	src.head_ = nullptr;

	count_ = 0;
	count_ = src.count_;
	src.count_ = 0;
}

template<typename T>
SinglyLinkedOrderedList<T>& SinglyLinkedOrderedList<T>::operator=(SinglyLinkedOrderedList<T>&& src)
{
	Node<T>* current = head_;
	Node<T>* temp = current;
	while (current != nullptr)
	{
		temp = current;
		current = current->next_;
		delete temp;
	}
	head_ = nullptr;

	head_ = src.head_;
	src.head_ = nullptr;

	return *this;
}

// вывести список 
template<typename T>
void SinglyLinkedOrderedList<T>::print() const
{
	Node<T>* current = head_;

	while (current != nullptr)
	{
		std::cout << current->item_ << ' ';
		current = current->next_;  // Переход к следующему элементу
	}
	std::cout << std::endl;
}

template<typename T>
SinglyLinkedOrderedList<T>::~SinglyLinkedOrderedList()
{
	Node<T>* current = nullptr;
	Node<T>* next = head_;

	while (next != nullptr)
	{
		current = next;
		next = next->next_;
		delete current;
	}
}

//копирование 
template<typename T>
SinglyLinkedOrderedList<T>::SinglyLinkedOrderedList(SinglyLinkedOrderedList<T>& src) noexcept
{
	head_ = nullptr;
	count_ = 0;
	Node<T>* next = src.head_;
	while (next != nullptr) {
		insertItem(next->item_);
		next = next->next_;
	}
}
