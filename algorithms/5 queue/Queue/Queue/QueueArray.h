#include "Queue.h"
#include "QueueOverflow.h"
#include "QueueUnderFlow.h"
#include "WrongQueueSize.h"

#include <iostream>

template <class T>
class QueueArray final : public Queue<T>
{
public:
	QueueArray(int size = 100);
	QueueArray(const QueueArray<T>& src);
	QueueArray(QueueArray<T>&& src) noexcept;
	virtual ~QueueArray();

	QueueArray<T>& operator= (const QueueArray<T>& src);
	QueueArray<T>& operator= (QueueArray<T>&& src) noexcept;

	void enQueue(const T& e);
	const T& deQueue();
	bool isEmpty();
	void print();
private:
	T* array_;
	int head_;
	int tail_;
	int size_;

	void swap(QueueArray<T>& right);
};

template <class T>
QueueArray<T>::QueueArray(int size) :
	head_(-1),
	tail_(-1),
	size_(size)
{
	try
	{
		array_ = new T[size];
	}
	catch (...)
	{
		throw WrongQueueSize();
	}
}

template <class T>
QueueArray<T>::QueueArray(const QueueArray<T>& src) :
	head_(src.head_),
	tail_(src.tail_)
{
	try 
	{
		array_ = new T[src.size_];
	}
	catch (...)
	{
		throw WrongQueueSize();
	}

	size_ = src.size_;
	for (int i = 0; i < size_; i++)
	{
		array_[i] = src.array_[i];
	}
}

template<class T>
QueueArray<T>::QueueArray(QueueArray<T>&& src) noexcept
{
	swap(src);
}

template<class T>
QueueArray<T>::~QueueArray()
{
	delete[] array_;
}

template<class T>
QueueArray<T>& QueueArray<T>::operator=(const QueueArray<T>& src)
{
	QueueArray<T> temp(src);
	swap(temp);

	return *this;
}

template<class T>
QueueArray<T>& QueueArray<T>::operator=(QueueArray<T>&& src) noexcept
{
	QueueArray<T> temp(std::move(src));
	swap(temp);
	
	return *this;
}

template <typename T>
void QueueArray<T>::swap(QueueArray<T>& right)
{
	std::swap(this->array_, right.array_);
	std::swap(this->head_, right.head_);
	std::swap(this->tail_, right.tail_);
	std::swap(this->size_, right.size_);
}

template<class T>
bool QueueArray<T>::isEmpty()
{
	return head_ == tail_ && head_ == -1;
}

template <class T>
void QueueArray<T>::enQueue(const T& q)
{
	if ((head_ == 0 && tail_ == size_ - 1) || // очередь просто заполнена  - самый простой случай
		(tail_ == (head_ - 1) % (size_ - 1))) // хвост стоит перед головой 
	{
		throw QueueOverflow();
		return;
	}
	else if (head_ == -1) // добавление в пустую очередь 
	{
		head_ = tail_ = 0;
		array_[tail_] = q;
	}
	else if (tail_ == size_ - 1 && head_ != 0) // если мы что-то удалили и хвост подходит к 0 "индексу"
	{
		tail_ = 0;
		array_[tail_] = q;
	}
	else
	{
		tail_++;
		array_[tail_] = q;
	}
}

template <class T>
const T& QueueArray<T>::deQueue()
{
	if (head_ == -1) throw QueueUnderFlow();
	
	T& data = array_[head_];
	//array_[head_] = -1; // Надо ли ? 
	if (head_ == tail_) // 1 элемент добавлен и сразу его удаляем 
	{
		head_ = -1;
		tail_ = -1;
	}
	else if (head_ == size_ - 1) head_ = 0;
	else head_++;

	return data;
}

template <class T>
void QueueArray<T>::print()
{
	if (head_ == -1)
	{
		std::cout << "Queue is Empty!";
	}
	else if (tail_ >= head_)
	{
		for (int i = head_; i <= tail_; i++)
		std::cout << array_[i] << " ";
	}
	else
	{
		for (int i = head_; i < size_; i++)
			std::cout << array_[i] << " ";

		for (int i = 0; i <= tail_; i++)
			std::cout << array_[i] << " ";
	}

	std::cout << std::endl;
}
