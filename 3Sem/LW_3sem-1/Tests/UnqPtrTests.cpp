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

  SECTION("Moving constructor")
  {
    int* ptr = new int(5); 
    UnqPtr<int> UnqPtr1(ptr);
    UnqPtr<int> UnqPtr2(std::move(UnqPtr1));

    REQUIRE(UnqPtr1.get() == nullptr);
    REQUIRE(UnqPtr2.get() == ptr);
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

  SECTION("Operator ->")
  {
    struct test_struct
    {
      int value;
    };
    test_struct* ptr = new test_struct();
    UnqPtr<test_struct> UnqPtr(ptr);
    UnqPtr->value = 5;
    REQUIRE((*UnqPtr).value == 5);
    REQUIRE(UnqPtr->value == 5);
  }

  SECTION("Const version of operator ->")
  {
    struct test_struct
    {
      int value;
      test_struct(int value):
        value(value)
      { }
    };
    test_struct* ptr = new test_struct(5);
    const UnqPtr<test_struct> UnqPtr(ptr);
    REQUIRE(UnqPtr->value == 5);
  }

  SECTION("Assignment with moving an object")
  {
    int* ptr = new int(5); 
    UnqPtr<int> UnqPtr1(ptr);
    UnqPtr<int> UnqPtr2;
    REQUIRE_NOTHROW(UnqPtr1.operator=(std::move(UnqPtr1)));
    UnqPtr2 = std::move(UnqPtr1);
    REQUIRE(UnqPtr1.get() == nullptr);    
    REQUIRE(UnqPtr2.get() == ptr);    
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
  
  SECTION("Moving constructor")
  {
    int* ptr = new int[3] {1, 2, 3}; 
    UnqPtr<int[]> UnqPtr1(ptr);
    UnqPtr<int[]> UnqPtr2(std::move(UnqPtr1));

    REQUIRE(UnqPtr1.get() == nullptr);
    REQUIRE(UnqPtr2.get() == ptr);
  }
}

TEST_CASE("UnqPtr[]: Operators")
{
  SECTION("Operator *")
  {
    int* ptr = new int[3] {1, 2, 3};
    UnqPtr<int[]> UnqPtr(ptr);
    *UnqPtr = 4;
    REQUIRE(*UnqPtr == 4);
    REQUIRE(UnqPtr[0] == 4);
  }

  SECTION("Const version of operator *")
  {
    int* ptr = new int[3] {1, 2, 3};
    const UnqPtr<int[]> UnqPtr(ptr);
    REQUIRE(*UnqPtr == 1);
  }

  SECTION("Operator ->")
  {
    struct test_struct
    {
      int value;
    };
    test_struct* ptr = new test_struct[3];
    UnqPtr<test_struct[]> UnqPtr(ptr);
    UnqPtr->value = 5;
    REQUIRE(UnqPtr[0].value == 5);
    REQUIRE(UnqPtr->value == 5);
  }

  SECTION("Const version of operator ->")
  {
    struct test_struct
    {
      int value;
      test_struct(int value):
        value(value)
      { }
    };
    test_struct* ptr = new test_struct(5);
    const UnqPtr<test_struct> UnqPtr(ptr);
    REQUIRE(UnqPtr->value == 5);
  }

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
  
  SECTION("Assignment with moving an object")
  {
    int* ptr = new int[3]{1, 2, 3}; 
    UnqPtr<int[]> UnqPtr1(ptr);
    UnqPtr<int[]> UnqPtr2;
    REQUIRE_NOTHROW(UnqPtr1.operator=(std::move(UnqPtr1)));
    UnqPtr2 = std::move(UnqPtr1);
    REQUIRE(UnqPtr1.get() == nullptr);    
    REQUIRE(UnqPtr2.get() == ptr);    
  }
}