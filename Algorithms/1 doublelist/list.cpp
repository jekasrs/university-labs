//
// Тестовая функция:   проверка методов работы со списком 
//
#include <iostream>
#include "DoubleLinkedList.h"
DoubleLinkedList DeleteHeadTail(DoubleLinkedList list);
void TestFunction();

int main() {
	setlocale(LC_ALL, "rus");
	TestFunction();
	return 0;
}


void TestFunction()
{
	DoubleLinkedList list1;
	for (int i = 0; i < 11; i++)
	{
		list1.insertTail(i);
	}
	std::cout << "Вывод 1 список" << std::endl;
	std::cout << list1 << std::endl;

	DoubleLinkedList list;
	std::cout << "Вывод пустого списка" << std::endl;
	std::cout << list << std::endl;

	// присвоение ( копирование ) 
	DoubleLinkedList list2 = list1;
	std::cout << "Вывод 2 списока" << std::endl;
	std::cout << list2 << std::endl;

	// инициализация с r-value перемещение  
	DoubleLinkedList list3 = DeleteHeadTail(list1);
	list1.outAll();
	list2.outAll();
	list3.outAll();

	// Оператор перемещающего присваивания
	list2 = DeleteHeadTail(list3);

	std::cout << "Одинаковые ли листы 1 и 2" << std::endl;
	std::cout << ((list1==list2) ? "--да" : "--нет") << std::endl;

	DoubleLinkedList list4;
	for (int i = 10; i >-1; i--)
	{
		list4.insertTail(i);
	}

	std::cout << "Замена одного элемента на другое" << std::endl;
	list4.replaceItem(4, 7);
	list4.outAll();

	std::cout << "Замена вссех элементов на новое" << std::endl;
	list4.replaceItem(4, 7, 1);
	list4.outAll();

	std::cout << "Склеивание списка" << std::endl;
	list4.AddList(list3);
	list4.outAll();
	list3.outAll();
}

DoubleLinkedList DeleteHeadTail(DoubleLinkedList list)
{
	DoubleLinkedList l= list;
	l.deleteHead();
	l.deleteTail();
	return l;
}