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