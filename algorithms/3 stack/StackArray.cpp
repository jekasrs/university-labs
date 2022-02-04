#include"StackArray.h"

#include <utility>
#include "StackOverflow.h"
#include "StackUnderflow.h"
#include "WrongStackSize.h"

// метод swap - закрытый
template<class T>
inline void StackArray<T>::swap(StackArray<T>& src) noexcept
{
  std::swap(array_, src.array_);
  std::swap(top_, src.top_);
  std::swap(size_, src.size_);
}

// конструктор 
template<class T>
StackArray<T>::StackArray(int size) :
	size_(size),
	top_(0)
{
	try { // массив будем начнать с 1, в [0] - ничего нет 
		array_ = new T[size + 1]; // заказ памяти под stackarray
	}
	catch (...) { // ... - если что-то случилось 
		throw WrongStackSize();
	}
}

// конструктор копирования 
template<class T>
StackArray<T>::StackArray(const StackArray<T>& src) :
	size_(src.size_),
	top_(src.top_)
{
	try
	{
		array_ = new T[src.size_ + 1];
	}
	catch (...)
	{
		throw WrongStackSize();
	}

	// копирование массива 
	for (int i = 0; i <= src.top_; i++) {
		array_[i] = src.array_[i];
	}
}

// конструктор перемещения 
template<class T>
StackArray<T>::StackArray(StackArray<T>&& src) noexcept
	//size_(src.size_),
	//top_(src.top_),
	//array_(src.array_)
{
	swap(src);
	src.size_ = 0;
	src.top_ = 0;
	src.array_ = nullptr;
}

// оператор копирования 
template<class T>
StackArray<T>& StackArray<T>::operator=(const StackArray<T>& src)
{
	// очищаем все слева 
	delete[] array_;
	array_ = nullptr;

	// копируем из r-v в l-v
	size_ = src.size_;
	top_ = src.top_;
	
	try
	{
		array_ = new T[src.size_ + 1];
	}
	catch (...)
	{
		throw WrongStackSize();
	}
	for (int i = 0; i <= src.top_; i++) {
		array_[i] = src.array_[i];
	}
}

// оператор перемещения 
template<class T>
StackArray<T>& StackArray<T>::operator=(StackArray<T>&& src)
{
	// очищаем все слева
	delete[] array_;
	array_ = nullptr;

	// перемещаем
	size_ = src.size_;
	top_ = src.top_;
	array_ = src.array_;

	// очищаем r-v
	src.size_ = 0;
	src.top_ = 0;
	src.array_ = nullptr;
}

// деструткор 
template<class T>
StackArray<T>::~StackArray()
{
	delete[] array_;
	array_ = nullptr;
	size_ = 0;
	top_ = 0;
}

template<class T>
void StackArray<T>::push(const T& e)
{
	if (top_ == size_) {
		throw StackOverflow(); // нет места для нового элемента 
	}
	else {
		array_[++top_] = e; // занесение элемента в стек 
	}
}

template<class T>
const T& StackArray<T>::pop()
{
	// стек - пуст 
	if (top_ == 0) {
		throw StackUnderFlow();
	}
	// элемент "физически" остается 
	return *(array_+top_--); // адресная 
}

template<class T>
const size_t& StackArray<T>::getTop()
{
	return top_;
}

template<class T>
bool StackArray<T>::isEmpty() const noexcept
{
	if (top_==0)
		return true;
	else return false;
}
