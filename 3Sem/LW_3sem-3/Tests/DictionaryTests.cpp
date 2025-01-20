#include <catch2/catch_all.hpp>

#include <iostream>

#include "../Source/Dictionary.hpp"

TEST_CASE("Dictionary: Constructors")
{
  SECTION("Empty constructor")
  {
    Dictionary<int, char> Dict;
    REQUIRE(Dict.getCount() == 0);
  }
}

TEST_CASE("Dictionary: getCount")
{
  SECTION("Empty dictionary")
  {
    Dictionary<int, char> Dict;
    REQUIRE(Dict.getCount() == 0);
  }
  /*
  */
  SECTION("Non-empty dictionary")
  {
    Dictionary<int, char> Dict;
    Dict[1] = '1';
    Dict[2] = '2';
    Dict[3] = '3';
    Dict[4] = '4';
    REQUIRE(Dict.getCount() == 4);
  }
}

TEST_CASE("Dictionary: containsKey")
{
  SECTION("Empty dictionary")
  {
    Dictionary<int, char> Dict;
    REQUIRE(!Dict.containsKey(1));
  }
  
  SECTION("Contains")
  {
    Dictionary<int, char> Dict;
    Dict[1] = '1';
    Dict[2] = '2';
    Dict[3] = '3';
    Dict[4] = '4';
    REQUIRE(Dict.containsKey(1));
    REQUIRE(Dict.containsKey(2));
    REQUIRE(Dict.containsKey(3));
    REQUIRE(Dict.containsKey(4));
  }

  SECTION("Doesn't Contain")
  {
    Dictionary<int, char> Dict;
    Dict[1] = '1';
    Dict[2] = '2';
    Dict[3] = '3';
    Dict[4] = '4';
    REQUIRE(!Dict.containsKey(5));
    REQUIRE(!Dict.containsKey(6));
    REQUIRE(!Dict.containsKey(7));
    REQUIRE(!Dict.containsKey(8));
  }
/*
*/
}

TEST_CASE("Dictionary: remove")
{
  SECTION("Empty dictionary")
  {
    Dictionary<int, char> Dict;
    Dict.remove(1);
    REQUIRE(Dict.getCount() == 0);
    REQUIRE(!Dict.containsKey(1));
  }
  SECTION("Doesn't remove")
  {
    Dictionary<int, char> Dict;
    Dict[1] = '1';
    Dict[2] = '2';
    Dict.remove(3);
    REQUIRE(Dict.getCount() == 2);
    REQUIRE(!Dict.containsKey(3));
  }
  SECTION("Removes")
  {
    Dictionary<int, char> Dict;
    Dict[1] = '1';
    Dict[2] = '2';
    Dict[3] = '3';
    Dict[4] = '4';
    Dict.remove(3);
    Dict.remove(1);
    REQUIRE(Dict.getCount() == 2);
    REQUIRE(!Dict.containsKey(3));
    REQUIRE(!Dict.containsKey(1));
    Dict[1] = '1';
    Dict[3] = '3';
    Dict.remove(2);
    REQUIRE(Dict.getCount() == 3);
    REQUIRE(!Dict.containsKey(2));
    Dict.remove(4);
    Dict.remove(3);
    Dict.remove(1);
    REQUIRE(Dict.getCount() == 0);
  }
}

TEST_CASE("Dictionary: [] operators")
{
  SECTION("Various")
  {
    Dictionary<int, char> Dict;
    Dict[1] = '1';
    REQUIRE(Dict[1] == '1');
    Dict[1] = 'i';
    REQUIRE(Dict[1] == 'i');
  }

}


TEST_CASE("Dictionary: Various operations")
{
  SECTION("Rotations1")
  {
    Dictionary<int, char> Dict;
    Dict[4] = '4';
    Dict[3] = '3';
    Dict[2] = '2';
    Dict[1] = '1';
    REQUIRE(Dict.containsKey(1));
    REQUIRE(Dict.containsKey(2));
    REQUIRE(Dict.containsKey(3));
    REQUIRE(Dict.containsKey(4));  
  }

  SECTION("Rotations2")
  {
    Dictionary<int, char> Dict;
    Dict[1] = '1';
    Dict[3] = '3';
    Dict[2] = '2';
    REQUIRE(Dict.containsKey(1));
    REQUIRE(Dict.containsKey(2));
    REQUIRE(Dict.containsKey(3));
  }

  SECTION("Rotations3")
  {
    Dictionary<int, char> Dict;
    Dict[4] = '4';
    Dict[2] = '2';
    Dict[3] = '3';
    REQUIRE(Dict.containsKey(2));
    REQUIRE(Dict.containsKey(3));
    REQUIRE(Dict.containsKey(4));
  }

}

/*
*/