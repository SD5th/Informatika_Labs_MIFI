#include <iostream>
#include <fstream>
#include "Source/Person.hpp"
#include "Source/BubbleSorter.hpp"

using namespace std;

void writeToFile(DynamicArray<Person> const & people, string const & filename) {
  ofstream outFile(filename);
  if (!outFile) {
    cout << "Error with opening "<< filename << " output file!" << std::endl;
    return;
  }
  for (size_t index = 0; index < people.getSize(); index++) {
    outFile << 
    people[index].gender << "\n" <<
    people[index].age << "\n" <<
    people[index].name << "\n" <<
    people[index].surname << "\n" <<
    people[index].height << "\n" <<
    people[index].isEmployed << "\n" <<
    people[index].salary << "\n" <<
    "\n";
  }
  outFile.close();
}

void readFromFile(DynamicArray<Person> & people, string const & filename) {
  ifstream inFile(filename);
  if (!inFile) {
    std::cerr << "Ошибка открытия файла для чтения!" << std::endl;
    return;
  }

  while (inFile) {
    Person buffer;
    inFile >> buffer.gender;
    inFile.ignore();
    inFile >> buffer.age;
    inFile.ignore();
    inFile >> buffer.name; 
    inFile.ignore();
    inFile >> buffer.surname;
    inFile.ignore();
    inFile >> buffer.height;
    inFile.ignore();
    inFile >> buffer.isEmployed;
    inFile.ignore();
    inFile >> buffer.salary;
    inFile.ignore();
    inFile.ignore();

    if (inFile) { // Проверяем, что чтение прошло успешно
      people.append(buffer);
    }
  }

  inFile.close();
}

void printArray(DynamicArray<Person> & array)
{
  size_t const size = array.getSize();
  for (size_t index = 0; index < size; index++)
  {
    cout << "Index:       " << index << endl;
    cout << "Gender:      " << array[index].gender << endl;
    cout << "Age:         " << array[index].age << endl;
    cout << "Name:        " << array[index].name << endl;
    cout << "Surname:     " << array[index].surname << endl;
    cout << "Height:      " << array[index].height << endl;
    cout << "Is Employed: " << array[index].isEmployed << endl;
    cout << "Salary:      " << array[index].salary << endl;
    cout << endl;
  }
}

int main() {
  DynamicArray<Person> unsorted_array(5000);
  fillArrayRandomly(unsorted_array); 
  writeToFile(unsorted_array, "/home/whistling_daddy47/MyFolder/shkool_Labs/3Sem/LW_3sem-2/Data/unsorted.txt");
  BubbleSorter sorter;
  DynamicArray<Person> sortedBySalary_array(sorter.Sort(unsorted_array, compareSalary));
  writeToFile(sortedBySalary_array, "/home/whistling_daddy47/MyFolder/shkool_Labs/3Sem/LW_3sem-2/Data/sortedBySalary.txt");
  DynamicArray<Person> sortedByAge_array(sorter.Sort(unsorted_array, compareAge));
  writeToFile(sortedByAge_array, "/home/whistling_daddy47/MyFolder/shkool_Labs/3Sem/LW_3sem-2/Data/sortedByAge.txt");
  DynamicArray<Person> sortedByHeight_array(sorter.Sort(unsorted_array, compareHeight));
  writeToFile(sortedByHeight_array, "/home/whistling_daddy47/MyFolder/shkool_Labs/3Sem/LW_3sem-2/Data/sortedByHeight.txt");
  
  //printArray(sorted_array);

//  DynamicArray<Person> arraytest;
}