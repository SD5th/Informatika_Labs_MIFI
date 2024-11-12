#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>

#include "../Source/UnqPtr.h"

TEST_CASE("Constructors")
{
    SECTION("Empty constructor")
    {
        UnqPtr<int> x;
        REQUIRE(x.get() == nullptr);
        //REQUIRE_THROWS()
        //REQUIRE_NOTHROW()
    }
}