#include <iostream>
#include "SinglyLinkedOrderedList.h"
#include "SinglyLinkedOrderedList.cpp"

void Test();
int main()
{
	setlocale(LC_ALL, "RUS");
	Test();
	return 0;
}

void Test()
{
	SinglyLinkedOrderedList <int> test1;
	std::cout << "Вывод пустого списка" << std::endl << std::endl;
	test1.print();

	for (int i = 0; i <= 20; i++)
	{
		// заполнение 
		test1.insertItem(i);
	}

	test1.insertItem(10); // повторное слово не добовляется 

	SinglyLinkedOrderedList <int> test2;
	for (int i = 10; i <= 30; i++)
	{
		test2.insertItem(i);
	}

	// поиск по значению
	int search = 5;
	if (test1.searchItem(search)) {
		std::cout << "Find" << std::endl;
	}
	else {
		std::cout << "not Find" << std::endl;
	}
	if (test2.searchItem(search)) {
		std::cout << "Find" << std::endl;
	}
	else {
		std::cout << "not Find" << std::endl;
	}

	// вывод спискска 
	std::cout << "Вывод первого списка" << std::endl;
	test1.print();
	std::cout << "Вывод второго списка" << std::endl;
	test2.print();

	// add list из 2 списка в первой неповторяющиеся и 2 список будет пустой 
	test1.addList(test2);
	std::cout << "Вывод списков 1 и 2 после метода addlist списка" << std::endl << std::endl;
	test1.print();
	test2.print();

	for (int i = 10; i <= 31; i++)
	{
		test2.insertItem(i);
	}
	// удаляет все слова из 1 списка,которые есть во втором 
	std::cout << "Вывод списков 1 и 2 после метода substractionList списка" << std::endl << std::endl;
	test1.substractionList(test2);

	test1.print();
	test2.print();

	SinglyLinkedOrderedList <std::string> test3;
	SinglyLinkedOrderedList <std::string> test6; // пустой словарь 

	test3.insertItem("Aaa");
	test3.insertItem("AAa");
	test3.insertItem("Bbb");
	test3.insertItem("Ccc");
	test3.insertItem("daa");
	test3.insertItem("Saq");
	test3.insertItem("Saa");
	test3.insertItem("aaaa");
	
	std::cout << "проврека на правельность выволнения при пустом списке(тест 6):" << std::endl;

	test6.substractionList(test3);
	std::cout << "Вывод третьего списка" << std::endl;
	test3.print();
	std::cout << "Вывод шестого списка" << std::endl;
	test6.print();


	// копирование 
	SinglyLinkedOrderedList <std::string> test4 = test3;

	std::cout << "удаляем из тест 3 элемент" << std::endl;
	test3.deleteItem("aaaa"); // удаляет элемент по значению  

	std::cout << "Вывод третьего списка" << std::endl;
	test3.print();
	std::cout << std::endl;
	std::cout << "Вывод четветрого списка" << std::endl;
	test4.print();
	std::cout << std::endl;

	SinglyLinkedOrderedList <std::string> test5;
	test5 = mergeList(test3, test4); // формуирует новый список из значений, которые есть и в первом и во втором. 
	std::cout << "Новый список после метода mergeList" << std::endl;
	std::cout << std::endl;
	test5.print();
}
