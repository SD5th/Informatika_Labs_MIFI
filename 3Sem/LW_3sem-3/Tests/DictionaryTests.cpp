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

  SECTION("Copy-constructor")
  {
    Dictionary<int, char> Dict1;
    Dict1[1] = '1';
    Dict1[2] = '2';
    Dict1[3] = '3';
    Dict1[4] = '4';
    const Dictionary<int, char> Dict2(Dict1);
    REQUIRE(Dict2[1] == '1');
    REQUIRE(Dict2[2] == '2');
    REQUIRE(Dict2[3] == '3');
    REQUIRE(Dict2[4] == '4');
    REQUIRE(Dict2.getCount() == 4);
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
    Dictionary<int, char> Dict1;
    Dict1[1] = '1';
    REQUIRE(Dict1[1] == '1');
    const Dictionary<int, char> Dict2(Dict1);
    REQUIRE(Dict2[1] == '1');
    REQUIRE_THROWS(Dict2[2] == '2');
    const Dictionary<int, char> Dict3;
    REQUIRE_THROWS(Dict3[2] == '2');
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

  SECTION("At methods 1")
  {
    Dictionary<int, char> Dict1;
    Dict1[1] = '1';
    REQUIRE(Dict1.at(1) == '1');
    REQUIRE_THROWS(Dict1.at(2) == '2');
    const Dictionary<int, char> Dict2(Dict1);
    REQUIRE(Dict2.at(1) == '1');
    REQUIRE_THROWS(Dict2.at(2) == '2');
  }

  SECTION("At methods 2")
  {
    Dictionary<int, char> Dict1;
    REQUIRE_THROWS(Dict1.at(1) == '1');
    const Dictionary<int, char> Dict2(Dict1);
    REQUIRE_THROWS(Dict2.at(1) == '1');
  }
}

TEST_CASE("Dictionary: InOrderIterator")
{
  SECTION("1")
  {
    Dictionary<int, char> Dict1;
    for (int i = 0; i < 10; i++)
      Dict1[i] = i + 48;
    Dictionary<int, char>::InOrderIterator it1 = Dict1.createInOrderIterator();
    int i = 0;
    do {
      REQUIRE(it1.value() == i + 48);
      REQUIRE(it1.key() == i);
      i++;
    } while (it1.next());

    const Dictionary<int, char> Dict2(Dict1);
    const Dictionary<int, char>::InOrderIterator it2 = Dict2.createInOrderIterator();
    i = 0;
    do {
      REQUIRE(it2.value() == i + 48);
      REQUIRE(it2.key() == i);
      i++;
    } while (it2.next());
  }
  
  SECTION("2")
  {
    Dictionary<int, char> Dict1;
    Dict1[1] = '1';
    Dict1[2] = '2';
    Dict1[3] = '3';
    Dict1[4] = '4';
    Dictionary<int, char>::InOrderIterator it1 = Dict1.createInOrderIterator();
    it1.value() = 'l';
    it1.next();
    it1.next();
    it1.value() = 'E';
    REQUIRE(Dict1[1] == 'l');
    REQUIRE(Dict1[3] == 'E');
  }
}

/*
*/