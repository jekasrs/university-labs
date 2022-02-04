#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include "keystone.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <random>
#include <functional>

namespace utilities
{
  template <typename T>
  std::function<bool(T, T)> directionType(const char* direction)
  {
    if (!direction)
    {
      throw std::invalid_argument("There is no access order! Error! nullptr\n");
    }
    else if (std::string(direction) == "ascending")
    {
      return std::greater<const T>();
    }
    else if (std::string(direction) =="descending")
    {
      return std::less<const T>();
    }
    else
    {
      throw std::invalid_argument("Error! Wrong direction\n");
    }
  }

  template <template <class> class Type, class Conteiner>
  void bubbleSort(Conteiner& container,
       std::function<bool(typename Conteiner::value_type, typename Conteiner::value_type)> compare)
  {
    auto begin = Type<Conteiner>::begin(container);
    auto end = Type<Conteiner>::end(container);

    for (auto i = begin; i != end; ++i)
    {
      for (auto j = i; j != end; ++j)
      {
        if (compare(Type<Conteiner>::getElement(container, i), Type<Conteiner>::getElement(container, j)))
          std::swap(Type<Conteiner>::getElement(container, i), Type<Conteiner>::getElement(container, j));
      }
    }
  }

  template <class Container>
  void print(const Container& container, const char* space="")
  {
    for (auto i = container.begin(); i != container.end(); ++i)
    {
      std::cout << *i << space;
    }
    std::cout << std::endl;
  }

  inline void fillRandom(double* array, long size)
  {
    if (array == nullptr)
    {
      throw std::invalid_argument("Error! Null pointer - nothing to fill. Task 4");
    }
    if (size <= 0)
    {
      throw std::invalid_argument("Error! Incorrect value of size: " + std::to_string(size) + ". It should be > 0");
    }
    std::random_device randomDevice;
    std::mt19937 generator(randomDevice());
    std::uniform_real_distribution<double> distribution(-1, 1);
    for (int i = 0; i < size; i++)
    {
      array[i] = distribution(generator);
    }
  }
}
#endif
