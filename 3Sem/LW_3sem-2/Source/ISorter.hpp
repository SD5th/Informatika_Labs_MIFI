#pragma once

#include "../../LW_3sem-1/Source/DynamicArray.hpp"
#include "Person.hpp"

class ISorter
{
  public:
  virtual DynamicArray<Person> Sort(DynamicArray<Person> const &, bool (*) (Person const &, Person const &)) = 0;
  virtual ~ISorter() {}
};