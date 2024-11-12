#include "../Source/UnqPtr.hpp"

#include <catch2/catch_all.hpp>


TEST_CASE("UnqPtr: Constructors", "UnqPtr")
{
    SECTION("Empty constructor")
    {
        UnqPtr<int> x;
        REQUIRE(1 == 1);
        //REQUIRE_THROWS()
        //REQUIRE_NOTHROW()
    }
}
