#include "QueueArray.h"
#include <iostream>

void DeafaultFunction();
void ErrorsCatch();

int main()
{
  DeafaultFunction();
  std::cout << "\n";
  ErrorsCatch();
  return 0;
}


void DeafaultFunction()
{
  std::cout << "Test on coorerct life of queue:\n";
  QueueArray<int> queue(4);
  queue.print();
  queue.enQueue(10004);
  queue.enQueue(10005);
  queue.enQueue(9);
  queue.enQueue(0);
  queue.deQueue();
  queue.deQueue();

  queue.enQueue(4);
  queue.enQueue(5);
  queue.deQueue();

  queue.print();

  // копирование 
  QueueArray<int> qCopy(queue);
  std::cout << "qCopy queue: ";
  qCopy.print();
  qCopy.enQueue(8);
  std::cout << "Add 8 to qCopy" << std::endl;
  std::cout << "qCopy: "; qCopy.print();

  // перемещение 
  QueueArray<int> qMove(std::move(queue));
  std::cout << "qMove queue: ";
  qMove.print();
  std::cout << "Add 7 to qMove" << std::endl;
  qMove.enQueue(7);
  std::cout << "qMove: ";
  qMove.print();
  
  // = копирования 
  queue = qCopy;
  std::cout << "qCopy queue = ";
  qCopy.print();

  // = перемещения 
  queue = std::move(qMove);
  std::cout << "queue after moving qMove = ";
  queue.print();
}

void ErrorsCatch()
{
  std::cout << "Test on coorerct exception handling:\n";
  try
  {
    QueueArray<int> q(-5);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }

  QueueArray<int> q(5);

  q.enQueue(1);
  q.enQueue(2);
  q.enQueue(3);
  q.enQueue(4);
  q.enQueue(5);

  try 
  {
    q.enQueue(6);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
  q.deQueue();
  q.deQueue();
  q.deQueue();
  q.deQueue();
  q.deQueue();
  try
  {
    q.deQueue();
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl;
  }
}
