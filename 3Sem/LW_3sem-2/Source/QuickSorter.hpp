#pragma once

#include "ISorter.hpp"

class QuickSorter : public ISorter
{
private:
  size_t partition(DynamicArray<Person> & array, size_t const & low, size_t const & high, bool (*compare) (Person const &, Person const &)) {
    Person pivot = array[high];
    size_t i = low;

    for (size_t j = low; j < high; j++) {
      if (compare(pivot, array[j])) {            
        swap(array, i, j);
        i++;
      }
    }
    swap(array, i, high);

    return i;
  }

  void QuickSort(DynamicArray<Person> & array, size_t const & low, size_t const & high, bool (*compare) (Person const &, Person const &)) {
    if (low < high) {
      size_t pi = partition(array, low, high, compare);

      if (pi != 0)
        QuickSort(array, low, pi - 1, compare);
      if (pi + 1 != high)
      QuickSort(array, pi + 1, high, compare);
    }
  }

public:
  DynamicArray<Person> Sort(DynamicArray<Person> const & array, bool (*compare) (Person const &, Person const &)) override
  {
    if (array.getSize() == 0)
      return DynamicArray<Person>();
    DynamicArray<Person> answer(array);
    QuickSort(answer, 0, answer.getSize() - 1, compare);
    return answer;
  }

  std::string GetType() override
  {
    return "Quick";
  }
};

