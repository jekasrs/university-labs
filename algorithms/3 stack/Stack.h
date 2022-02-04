#ifndef STACK_HPP
#define STACK_HPP

template <class T>
class Stack
{
public:
  virtual ~Stack() = default;
  virtual void push(const T& e) = 0; // добавление элемента в стек
  virtual const T& pop() = 0; // удаление и возвращение верхнего элемента. // если элементов нет, может возникнуть StackUnderflow	  
  virtual bool isEmpty() const = 0; // проверка стека на пустоту
};

#endif 
