#ifndef QUEUE_H
#define QUEUE_H

template <class T>
class Queue
{
public:
	virtual ~Queue() = default;
	virtual void enQueue(const T& e) = 0; // Добавление элемента
	virtual const T& deQueue() = 0;// Удаление и возвращение верхнего элемента.
	virtual bool isEmpty() = 0; // Проверка на пустоту
	virtual void print() = 0; 
};
#endif
