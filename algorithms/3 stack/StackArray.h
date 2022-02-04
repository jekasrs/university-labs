#ifndef STACK_ARRAY_HPP
#define STACK_ARRAY_HPP

#include "Stack.h"

template <class T>
class StackArray : public Stack<T> {

public:
  StackArray(int size = 30); // size задает размер стека "по умолчанию"

  StackArray(const StackArray<T>& src);
  StackArray(StackArray<T>&& src) noexcept;
  StackArray& operator=(const StackArray<T>& src);
  StackArray& operator=(StackArray<T>&& src);
  ~StackArray() override;

  void push(const T& e);
  const T& pop();
  const size_t& getTop();
  bool isEmpty() const noexcept;

private:
  T* array_; // массив элементов стека: !!! array_[0] – не используется, top_ от 1 до size_
  size_t top_; // вершина стека, элемент занесенный в стек последним
  size_t size_; // размер стека
  void swap(StackArray<T>& src) noexcept;
};

#endif
