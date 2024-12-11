#include <iostream>

#include "../LW_3sem-1/Source/SmartDynamicArray.hpp"
#include "Source/BubbleSorter.hpp"
#include "Source/Person.hpp"

using namespace std;

int main() {
  DynamicArray<Person> unsorted_array(10);
  fillRandomly(unsorted_array); 
  BubbleSorter sorter;
  DynamicArray<Person> sorted_array(sorter.Sort(unsorted_array));
  for (size_t index = 0; index < unsorted_array.getSize(); index++)
  {
    cout << "Index:       " << index << endl;
    cout << "Gender:      " << unsorted_array[index].gender << endl;
    cout << "Age:         " << unsorted_array[index].age << endl;
    cout << "Name:        " << unsorted_array[index].name << endl;
    cout << "Surname:     " << unsorted_array[index].surname << endl;
    cout << "Height:      " << unsorted_array[index].height << endl;
    cout << "Is Employed: " << unsorted_array[index].isEmployed << endl;
    cout << "Salary:      " << unsorted_array[index].salary << endl;
    cout << endl;
  }
  cout << "---------------------" << endl;
  for (size_t index = 0; index < sorted_array.getSize(); index++)
  {
    cout << "Index:       " << index << endl;
    cout << "Gender:      " << sorted_array[index].gender << endl;
    cout << "Age:         " << sorted_array[index].age << endl;
    cout << "Name:        " << sorted_array[index].name << endl;
    cout << "Surname:     " << sorted_array[index].surname << endl;
    cout << "Height:      " << sorted_array[index].height << endl;
    cout << "Is Employed: " << sorted_array[index].isEmployed << endl;
    cout << "Salary:      " << sorted_array[index].salary << endl;
    cout << endl;
  }
}