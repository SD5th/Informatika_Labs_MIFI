#pragma once

#include "ISorter.hpp"

class BubbleSorter : ISorter
{
private:
  void BubbleSort(DynamicArray<Person> & array, size_t const & low, size_t const & high, bool (*compare) (Person const &, Person const &))
  {
    for (size_t i = low; i < high; i++)
      for (size_t j = low; j < high - i; j++)
        if (compare(array[j], array[j+1]))
          swap(array, j, j + 1);
  }

public:
  DynamicArray<Person> Sort(DynamicArray<Person> const & array, bool (*compare) (Person const &, Person const &)) override
  {
    if (array.getSize() == 0)
      return DynamicArray<Person>();
    DynamicArray<Person> answer(array);
    BubbleSort(answer, 0, answer.getSize() - 1, compare);
    return answer;
  }
};