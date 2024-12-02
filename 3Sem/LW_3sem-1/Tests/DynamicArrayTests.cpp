#include "../Source/SmartDynamicArray.hpp"

#include <catch2/catch_all.hpp>

#include <iostream>

TEST_CASE("SmartDynamicArray: Constructors")
{
  SECTION("Constructor of zero-array")
  {
    DynamicArray<int> DynArr;
    REQUIRE(DynArr.getSize() == 0);
  }

  SECTION("Constructor of empty array of given size")
  {
    DynamicArray<int> DynArr(5);
    REQUIRE(DynArr.getSize() == 5);
  }
  
  SECTION("Constructor of array with given objects of given size")
  {
    int arr[2] {1, 2};
    DynamicArray<int> DynArr(arr, 2);
    REQUIRE(DynArr.getSize() == 2);
    REQUIRE(DynArr[0] == 1);
    REQUIRE(DynArr[1] == 2);
  }
  
  SECTION("Copy-constructor")
  {
    int arr[2] {1, 2};
    DynamicArray<int> DynArr1(arr, 2);
    DynamicArray<int> DynArr2(DynArr1);
    REQUIRE(DynArr1.getSize() == 2);
    REQUIRE(DynArr1[0] == 1);
    REQUIRE(DynArr1[1] == 2);
    REQUIRE(DynArr2.getSize() == 2);
    REQUIRE(DynArr2[0] == 1);
    REQUIRE(DynArr2[1] == 2);
  }

  SECTION("Move-constructor")
  {
    int arr[2] {1, 2};
    DynamicArray<int> DynArr1(arr, 2);
    DynamicArray<int> DynArr2(std::move(DynArr1));
    REQUIRE(DynArr1.getSize() == 0);
    REQUIRE(DynArr2.getSize() == 2);
    REQUIRE(DynArr2[0] == 1);
    REQUIRE(DynArr2[1] == 2);
  }
}

TEST_CASE("SmartDynamicArray: Getters")
{
  SECTION("Get size")
  {
    DynamicArray<int> DynArr(5);
    REQUIRE(DynArr.getSize() == 5);
  }

  SECTION("Get subsequence")
  {
    int arr[5] {1, 2, 3, 4, 5};
    DynamicArray<int> DynArr1(arr, 5);
    DynamicArray<int> DynArr2 = DynArr1.getSubsequence(1, 3);
    REQUIRE(DynArr2.getSize() == 3);
    REQUIRE(DynArr2[0] == 2);
    REQUIRE(DynArr2[1] == 3); 
    REQUIRE(DynArr2[2] == 4); 
  }
}


TEST_CASE("SmartDynamicArray: Modifying Operations")
{
  SECTION("Resize")
  {
    int arr[2] {1, 2};
    DynamicArray<int> DynArr(arr, 2);
    DynArr.resize(4);
    REQUIRE(DynArr.getSize() == 4);
    REQUIRE(DynArr[0] == 1);
    REQUIRE(DynArr[1] == 2); 
  }

  SECTION("Insert")
  {
    int arr[2] {1, 2};
    DynamicArray<int> DynArr(arr, 2);
    DynArr.insert(0, 0);
    DynArr.insert(3, 3);
    REQUIRE(DynArr[0] == 0);
    REQUIRE(DynArr[1] == 1);
    REQUIRE(DynArr[2] == 2); 
    REQUIRE(DynArr[3] == 3); 
    REQUIRE(DynArr.getSize() == 4);
  }

  SECTION("Append, Prepend")
  {
    int arr[2] {1, 2};
    DynamicArray<int> DynArr(arr, 2);
    DynArr.prepend(0);
    DynArr.append(3); 
    std::cout << DynArr[0] << " " << DynArr[1] << " " << DynArr[2] << " " << DynArr[3] << std::endl; 
    REQUIRE(DynArr[0] == 0);
    REQUIRE(DynArr[1] == 1);
    REQUIRE(DynArr[2] == 2); 
    REQUIRE(DynArr[3] == 3); 
    REQUIRE(DynArr.getSize() == 4);
  }
  
  SECTION("Concatenation")
  {
    int arr1[2] {1, 2};
    int arr2[2] {3, 4};
    DynamicArray<int> DynArr1(arr1, 2);
    DynamicArray<int> DynArr2(arr2, 2);
    DynArr1.concat(DynArr2);
    REQUIRE(DynArr1[0] == 1);
    REQUIRE(DynArr1[1] == 2);
    REQUIRE(DynArr1[2] == 3); 
    REQUIRE(DynArr1[3] == 4); 
    REQUIRE(DynArr1.getSize() == 4);
  }
}

TEST_CASE("SmartDynamicArray: Operators")
{
  SECTION("Operator []")
  {
    int arr[2] {3, 4};
    DynamicArray<int> DynArr(arr, 2);
    DynArr[0] = 1;    
    DynArr[1] = 2;    
    REQUIRE(DynArr[0] == 1);
    REQUIRE(DynArr[1] == 2);
  }

  SECTION("Const version of operator []")
  {
    int arr[2] {1, 2};
    DynamicArray<int> const DynArr(arr, 2);
    REQUIRE(DynArr[0] == 1);  
  }
}