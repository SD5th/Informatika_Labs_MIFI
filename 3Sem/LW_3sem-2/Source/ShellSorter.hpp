#pragma once

#include "ISorter.hpp"

class ShellSorter : ISorter
{
private:
  void ShellSort(DynamicArray<Person> & array, size_t const & low, size_t const & high, bool (*compare) (Person const &, Person const &)) {
    size_t size = high - low + 1;
    for (size_t gap = size / 2; gap > 0; gap /= 2)
      for (size_t i = low + gap; i <= high; i++)
      {
        Person temp = array[i];
        size_t j;
        for (j = i; (j >= low + gap) && compare(array[j - gap], temp); j -= gap)
          array[j] = array[j - gap];
        array[j] = temp;
      }
  }

public:
  DynamicArray<Person> Sort(DynamicArray<Person> const & array, bool (*compare) (Person const &, Person const &)) override
  {
    if (array.getSize() == 0)
      return DynamicArray<Person>();
    DynamicArray<Person> answer(array);
    ShellSort(answer, 0, answer.getSize() - 1, compare);
    return answer;
  }
};

