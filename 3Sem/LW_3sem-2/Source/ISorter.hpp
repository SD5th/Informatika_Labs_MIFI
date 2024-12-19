#pragma once

#include "../../LW_3sem-1/Source/DynamicArray.hpp"
#include "Person.hpp"

class ISorter
{
protected :
  void swap(DynamicArray<Person> & array, size_t l, size_t r)
  {
    Person buffer = std::move(array[l]);
    array[l] = std::move(array[r]);
    array[r] = std::move(buffer);
  }

public:
  virtual DynamicArray<Person> Sort(DynamicArray<Person> const &, bool (*) (Person const &, Person const &)) = 0;
  virtual std::string GetType() = 0;
  virtual ~ISorter() {}
};