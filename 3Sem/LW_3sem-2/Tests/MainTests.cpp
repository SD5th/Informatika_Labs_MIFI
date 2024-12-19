#define CATCH_CONFIG_MAIN

#include "../Source/BubbleSorter.hpp"
#include "../Source/QuickSorter.hpp"
#include "../Source/ShellSorter.hpp"
#include "../Source/SelectionSorter.hpp"
#include <fstream>
#include <iostream>

#include <catch2/catch_all.hpp>

using namespace std;

TEST_CASE("QuickSort")
{
  SECTION("TEST1000")
  {
    ifstream inFile("TEST1000.txt");
    DynamicArray<Person> unsorted;
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
        unsorted.append(buffer);
      }
  }
  inFile.close();
  QuickSorter qs;
  DynamicArray<Person> sorted (qs.Sort(unsorted, compareAge));
  REQUIRE(unsorted.getSize() == sorted.getSize());
  for (size_t i = 0; i < sorted.getSize()-1; i++)
    REQUIRE(compareAge(sorted[i], sorted[i+1]) == false);
  }
}

TEST_CASE("BubbleSort")
{
  SECTION("TEST1000")
  {
    ifstream inFile("TEST1000.txt");
    DynamicArray<Person> unsorted;
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
        unsorted.append(buffer);
      }
  }
  inFile.close();
  BubbleSorter bs;
  DynamicArray<Person> sorted (bs.Sort(unsorted, compareAge));
  REQUIRE(unsorted.getSize() == sorted.getSize());
  for (size_t i = 0; i < sorted.getSize()-1; i++)
    REQUIRE(compareAge(sorted[i], sorted[i+1]) == false);
  }
}

TEST_CASE("ShellSort")
{
  SECTION("TEST1000")
  {
    ifstream inFile("TEST1000.txt");
    DynamicArray<Person> unsorted;
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
        unsorted.append(buffer);
      }
  }
  inFile.close();
  ShellSorter ss;
  DynamicArray<Person> sorted (ss.Sort(unsorted, compareAge));
  REQUIRE(unsorted.getSize() == sorted.getSize());
  for (size_t i = 0; i < sorted.getSize()-1; i++)
    REQUIRE(compareAge(sorted[i], sorted[i+1]) == false);
  }
}

TEST_CASE("SelectionSort")
{
  SECTION("TEST1000")
  {
    ifstream inFile("TEST1000.txt");
    DynamicArray<Person> unsorted;
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
        unsorted.append(buffer);
      }
  }
  inFile.close();
  SelectionSorter ss;
  DynamicArray<Person> sorted (ss.Sort(unsorted, compareAge));
  REQUIRE(unsorted.getSize() == sorted.getSize());
  for (size_t i = 0; i < sorted.getSize()-1; i++)
    REQUIRE(compareAge(sorted[i], sorted[i+1]) == false);
  }
}

