#pragma once

#include <fstream>

template<typename T>
class SinglyLinkedOrderedList
{
public:
	SinglyLinkedOrderedList();   // онструктор "по умолчанию"
	~SinglyLinkedOrderedList(); //ƒеструктор
	SinglyLinkedOrderedList(SinglyLinkedOrderedList<T>& src) noexcept;
	SinglyLinkedOrderedList(SinglyLinkedOrderedList<T>&& src) noexcept;
	SinglyLinkedOrderedList<T>& operator=(SinglyLinkedOrderedList<T>&& src);
	void addList(SinglyLinkedOrderedList& other); 
	// обьединение словарей ( в вырвый ) без повторений
	// из 2 словарей  - второй становаитс€ пустым 
	void substractionList(SinglyLinkedOrderedList& other); 
	// удаление во втором списке, если они есть в первом  
	void insertItem(T data);   // добааление в список 
	bool deleteItem(T data);  // ”даление узла с заданным значением
	bool searchItem(T data); // ѕоиск записи с заданным значением
	void print() const;     // вывод списка 
	int getSize() { return count_; };

	template<typename T>
	friend SinglyLinkedOrderedList<T> mergeList(SinglyLinkedOrderedList<T>& list1, SinglyLinkedOrderedList<T>& list2);
	// новый словарь только из общих слов двух словарей 

private:
	template<typename T>
	struct Node
	{
		Node* next_;
		T item_;

		Node(T item = T(), Node* next = nullptr) 
			// онструктор дл€ создани€ нового элемента
		{
			this->item_ = item;
			this->next_ = next;
		}
	};
	Node<T>* head_; //”казатель на голову
	int count_; // оличество элементов
	void deleteNode(Node<T>* data);
	// ”даление заданного узла 
	Node<T>* searchNode(T data);
	// ѕоиск узла (адрес) с заданным значением
};

