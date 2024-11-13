#include "../Source/UnqPtr.hpp"

#include <catch2/catch_all.hpp>


TEST_CASE("UnqPtr: Constructors")
{
  SECTION("Constructor with nullptr")
  {
    UnqPtr<int> UnqPtr;
    REQUIRE(UnqPtr.get() == nullptr);
  }

  SECTION("Constructor with given ptr")
  {
    int* ptr = new int(5); 
    UnqPtr<int> UnqPtr(ptr);
    REQUIRE(UnqPtr.get() == ptr);
  }
}

TEST_CASE("UnqPtr: Operators")
{
  SECTION("Operator *")
  {
    int* ptr = new int(5);
    UnqPtr<int> UnqPtr(ptr);
    *UnqPtr = 4;
    REQUIRE(*UnqPtr == 4);
  }

  SECTION("Const version of operator *")
  {
    int* ptr = new int(5); 
    UnqPtr<int> const UnqPtr(ptr);
    REQUIRE(*UnqPtr == 5);    
  }
}


TEST_CASE("UnqPtr[]: Constructors")
{
  SECTION("Constructor with nullptr")
  {
    UnqPtr<int[]> UnqPtr;
    REQUIRE(UnqPtr.get() == nullptr);
  }

  SECTION("Constructor with given ptr")
  {
    int* ptr = new int[3]{1, 2, 3}; 
    UnqPtr<int[]> UnqPtr(ptr);
    REQUIRE(UnqPtr.get() == ptr);
  }
}

TEST_CASE("UnqPtr[]: Operators")
{
  SECTION("Operator []")
  {
    int* ptr = new int[3]{1, 2, 3};
    UnqPtr<int[]> UnqPtr(ptr);
    UnqPtr[1] = 4;
    REQUIRE(UnqPtr[1] == 4);
  }

  SECTION("Const version of operator []")
  {
    int* ptr = new int[3]{1, 2, 3}; 
    UnqPtr<int[]> const UnqPtr(ptr);
    REQUIRE(UnqPtr[0] == 1);    
  }
}