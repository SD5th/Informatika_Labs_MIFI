#pragma once

#include "ISorter.hpp"

class BubbleSorter : ISorter
{
public:
  DynamicArray<Person> Sort(DynamicArray<Person> const & array, bool (*compare) (Person const &, Person const &)) override
  {
    if (array.getSize() == 0)
      return DynamicArray<Person>();
    DynamicArray<Person> answer(array);
    const size_t size = answer.getSize();
    for (size_t ind1 = 0; ind1 < size - 1; ind1++)
    {
      for (size_t ind2 = 0; ind2 < size - ind1 - 1; ind2++)
      {
        if (compare(answer[ind2], answer[ind2+1]))
        {
          Person buffer = std::move(answer[ind2]);
          answer[ind2] = std::move(answer[ind2+1]); 
          answer[ind2+1] = std::move(buffer); 
        } 
      }
    }
    return answer;
  }
};