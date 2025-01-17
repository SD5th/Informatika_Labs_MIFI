#define CATCH_CONFIG_MAIN

#include <fstream>
#include <iostream>

#include <catch2/catch_all.hpp>

using namespace std;

TEST_CASE("empty")
{
  SECTION("empty")
  {
    REQUIRE(true);
  }
}