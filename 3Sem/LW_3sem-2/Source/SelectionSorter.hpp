#pragma once

#include "ISorter.hpp"

class SelectionSorter : public ISorter
{
private:
  void SelectionSort(DynamicArray<Person> & array, size_t const & low, size_t const & high, bool (*compare) (Person const &, Person const &)) {
    for (size_t i = low; i < high; i++)
    {
      size_t min_index = i;
      for (size_t j = i + 1; j <= high; j++)
        if (compare(array[min_index], array[j]))
          min_index = j;
      swap(array, i, min_index);
    }
  }

public:
  DynamicArray<Person> Sort(DynamicArray<Person> const & array, bool (*compare) (Person const &, Person const &)) override
  {
    if (array.getSize() == 0)
      return DynamicArray<Person>();
    DynamicArray<Person> answer(array);
    SelectionSort(answer, 0, answer.getSize() - 1, compare);
    return answer;
  }

  std::string GetType() override
  {
    return "Selection";
  }

};

