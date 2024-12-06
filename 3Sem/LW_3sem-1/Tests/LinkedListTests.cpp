#include "../Source/SmartLinkedList.hpp"

#include <catch2/catch_all.hpp>

#include <iostream>

TEST_CASE("SmartLinkedList: Constructors")
{
  SECTION("Constructor of zero-array")
  {
    LinkedList<int> List;
    REQUIRE(List.getSize() == 0);
  }

  SECTION("Constructor of empty array of given size")
  {
    LinkedList<int> List(5);
    REQUIRE(List.getSize() == 5);
  }
  
  SECTION("Constructor of array with given objects of given size")
  {
    int arr[4] {1, 2, 3, 4};
    LinkedList<int> List(arr, 4);
    REQUIRE(List.getSize() == 4);
    REQUIRE(List[0] == 1);
    REQUIRE(List[1] == 2);
    REQUIRE(List[2] == 3);
    REQUIRE(List[3] == 4);
  }
  
  SECTION("Copy-constructor")
  {
    int arr[2] {1, 2};
    LinkedList<int> List1(arr, 2);
    LinkedList<int> List2(List1);
    REQUIRE(List1.getSize() == 2);
    REQUIRE(List1[0] == 1);
    REQUIRE(List1[1] == 2);
    REQUIRE(List2.getSize() == 2);
    REQUIRE(List2[0] == 1);
    REQUIRE(List2[1] == 2);
  }

  
  SECTION("Move-constructor")
  {
    int arr[2] {1, 2};
    LinkedList<int> List1(arr, 2);
    LinkedList<int> List2(std::move(List1));
    REQUIRE(List1.getSize() == 0);
    REQUIRE(List2.getSize() == 2);
    REQUIRE(List2[0] == 1);
    REQUIRE(List2[1] == 2);
  }
  
}

TEST_CASE("SmartLinkedList: Getters")
{
  SECTION("Get size")
  {
    LinkedList<int> List(5);
    REQUIRE(List.getSize() == 5);
  }

  SECTION("Get subsequence")
  {
    int arr[5] {1, 2, 3, 4, 5};
    LinkedList<int> List1(arr, 5);
    LinkedList<int> List2 = List1.getSubsequence(1, 3);
    REQUIRE(List2.getSize() == 3);
    REQUIRE(List2[0] == 2);
    REQUIRE(List2[1] == 3); 
    REQUIRE(List2[2] == 4); 
  }
}


TEST_CASE("SmartLinkedList: Modifying Operations")
{
  SECTION("Resize")
  {
    int arr[2] {1, 2};
    LinkedList<int> List(arr, 2);
    List.resize(4);
    REQUIRE(List.getSize() == 4);
    REQUIRE(List[0] == 1);
    REQUIRE(List[1] == 2); 
  }

  SECTION("Insert")
  {
    int arr[2] {1, 2};
    LinkedList<int> List(arr, 2);
    List.insert(0, 0);
    List.insert(3, 3);
    REQUIRE(List[0] == 0);
    REQUIRE(List[1] == 1);
    REQUIRE(List[2] == 2); 
    REQUIRE(List[3] == 3); 
    REQUIRE(List.getSize() == 4);
  }

  SECTION("Append, Prepend")
  {
    int arr[2] {1, 2};
    LinkedList<int> List(arr, 2);
    List.prepend(0);
    List.append(3); 
    std::cout << List[0] << " " << List[1] << " " << List[2] << " " << List[3] << std::endl; 
    REQUIRE(List[0] == 0);
    REQUIRE(List[1] == 1);
    REQUIRE(List[2] == 2); 
    REQUIRE(List[3] == 3); 
    REQUIRE(List.getSize() == 4);
  }
  
  SECTION("Concatenation")
  {
    int arr1[2] {1, 2};
    int arr2[2] {3, 4};
    LinkedList<int> List1(arr1, 2);
    LinkedList<int> List2(arr2, 2);
    List1.concat(List2);
    REQUIRE(List1[0] == 1);
    REQUIRE(List1[1] == 2);
    REQUIRE(List1[2] == 3); 
    REQUIRE(List1[3] == 4); 
    REQUIRE(List1.getSize() == 4);
  }
}

TEST_CASE("SmartLinkedList: Operators")
{
  SECTION("Operator []")
  {
    int arr[2] {3, 4};
    LinkedList<int> List(arr, 2);
    List[0] = 1;    
    List[1] = 2;    
    REQUIRE(List[0] == 1);
    REQUIRE(List[1] == 2);
  }

  SECTION("Const version of operator []")
  {
    int arr[2] {1, 2};
    LinkedList<int> const List(arr, 2);
    REQUIRE(List[0] == 1);  
  }
}