#ifndef KEYSTONE_HPP
#define KEYSTONE_HPP

template<class TypeContainer>
class IndexConteiner
{
  public:
    static unsigned int begin(TypeContainer&)
    {
      return 0;
    }

    static unsigned int end(TypeContainer& container)
    {
      return container.size();
    }

    static typename TypeContainer::reference getElement(TypeContainer& container, unsigned int index)
    {
      return container[index];
    }
};

template<class TypeContainer>
class AtConteiner
{
  public:
    static unsigned int begin(TypeContainer&)
    {
      return 0;
    }

    static unsigned int end(TypeContainer& container)
    {
      return container.size();
    }

    static typename TypeContainer::reference getElement(TypeContainer& container, unsigned int index)
    {
      return container.at(index);
    }
};

template<class TypeContainer>
class IteratorConteiner
{
  public:
    using iterator_t = typename TypeContainer::iterator;

    static iterator_t begin(TypeContainer& container)
    {
      return container.begin();
    }

    static iterator_t end(TypeContainer& container)
    {
      return container.end();
    }

    static typename TypeContainer::reference getElement(TypeContainer&, iterator_t& iterator)
    {
      return *iterator;
    }
};
#endif
