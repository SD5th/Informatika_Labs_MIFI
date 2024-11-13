#include "../Source/ShrdPtr.hpp"

#include <catch2/catch_all.hpp>

TEST_CASE("ShrdPtr: Constructors")
{
  SECTION("Constructor with nullptr")
  {
    ShrdPtr<int> ShrdPtr;
    REQUIRE(ShrdPtr.get() == nullptr);
  }

  SECTION("Constructor with given ptr")
  {
    int* ptr = new int(5); 
    ShrdPtr<int> ShrdPtr(ptr);
    REQUIRE(ShrdPtr.get() == ptr);
  }

  SECTION("Constructor with given ptr")
  {
    int* ptr = new int(5); 
    ShrdPtr<int> ShrdPtr1(ptr);
    ShrdPtr<int> ShrdPtr2(ShrdPtr1);
    REQUIRE(ShrdPtr2.get() == ptr);
    REQUIRE(ShrdPtr1.getReferenceCount() == 2);
    REQUIRE(ShrdPtr2.getReferenceCount() == 2);
    ShrdPtr1.~ShrdPtr();
    REQUIRE(ShrdPtr2.getReferenceCount() == 1);
  }
}

TEST_CASE("ShrdPtr: Operators")
{
  SECTION("Operator *")
  {
    int* ptr = new int(5);
    ShrdPtr<int> ShrdPtr(ptr);
    *ShrdPtr = 4;
    REQUIRE(*ShrdPtr == 4);
  }

  SECTION("Const version of operator *")
  {
    int* ptr = new int(5); 
    ShrdPtr<int> const ShrdPtr(ptr);
    REQUIRE(*ShrdPtr == 5);    
  }

  SECTION("Operator =")
  {
    int* ptr = new int(5); 
    ShrdPtr<int> ShrdPtr1(ptr);
    ShrdPtr<int> ShrdPtr2;
    ShrdPtr<int> ShrdPtr3;
    ShrdPtr3 = ShrdPtr2 = ShrdPtr1;
    REQUIRE(ShrdPtr1.get() == ptr);
    REQUIRE(ShrdPtr2.get() == ptr);
    REQUIRE(ShrdPtr3.get() == ptr);
    ShrdPtr1.~ShrdPtr();
    REQUIRE(ShrdPtr2.getReferenceCount() == 2);
    ShrdPtr2.~ShrdPtr();
    REQUIRE(ShrdPtr3.getReferenceCount() == 1);
  }
}



TEST_CASE("ShrdPtr[]: Constructors")
{
  SECTION("Constructor with nullptr")
  {
    ShrdPtr<int[]> ShrdPtr;
    REQUIRE(ShrdPtr.get() == nullptr);
  }

  SECTION("Constructor with given ptr")
  {
    int* ptr = new int[3]{1, 2, 3}; 
    ShrdPtr<int[]> ShrdPtr(ptr);
    REQUIRE(ShrdPtr.get() == ptr);
  }

  SECTION("Constructor with given ptr")
  {
    int* ptr = new int[3]{1, 2, 3}; 
    ShrdPtr<int> ShrdPtr1(ptr);
    ShrdPtr<int> ShrdPtr2(ShrdPtr1);
    REQUIRE(ShrdPtr2.get() == ptr);
    REQUIRE(ShrdPtr1.getReferenceCount() == 2);
    REQUIRE(ShrdPtr2.getReferenceCount() == 2);
    ShrdPtr1.~ShrdPtr();
    REQUIRE(ShrdPtr2.getReferenceCount() == 1);
  }
}

TEST_CASE("ShrdPtr[]: Operators")
{
  SECTION("Operator []")
  {
    int* ptr = new int[3]{1, 2, 3};
    ShrdPtr<int[]> ShrdPtr(ptr);
    ShrdPtr[1] = 4;
    REQUIRE(ShrdPtr[1] == 4);
  }

  SECTION("Const version of operator []")
  {
    int* ptr = new int[3]{1, 2, 3}; 
    ShrdPtr<int[]> const ShrdPtr(ptr);
    REQUIRE(ShrdPtr[1] == 2);    
  }

  SECTION("Operator =")
  {
    int* ptr = new int[3]{1, 2, 3}; 
    ShrdPtr<int[]> ShrdPtr1(ptr);
    ShrdPtr<int[]> ShrdPtr2;
    ShrdPtr<int[]> ShrdPtr3;
    ShrdPtr3 = ShrdPtr2 = ShrdPtr1;
    REQUIRE(ShrdPtr1.get() == ptr);
    REQUIRE(ShrdPtr2.get() == ptr);
    REQUIRE(ShrdPtr3.get() == ptr);
    ShrdPtr1.~ShrdPtr();
    REQUIRE(ShrdPtr2.getReferenceCount() == 2);
    ShrdPtr2.~ShrdPtr();
    REQUIRE(ShrdPtr3.getReferenceCount() == 1);
  }
}