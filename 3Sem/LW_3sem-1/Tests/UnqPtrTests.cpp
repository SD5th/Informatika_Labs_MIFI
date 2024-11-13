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