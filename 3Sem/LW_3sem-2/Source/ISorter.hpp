#pragma once

#include "../../LW_3sem-1/Source/SmartDynamicArray.hpp"
#include "Person.hpp"

class ISorter
{
  public:
  virtual DynamicArray<Person> Sort(DynamicArray<Person> const &) = 0;
  virtual ~ISorter() {} 
};