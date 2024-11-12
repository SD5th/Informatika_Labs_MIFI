#include "../Source/ShrdPtr.hpp"

#include <catch2/catch_all.hpp>


TEST_CASE("ShrdPtr: Constructors", "ShrdPtr")
{
    SECTION("Empty constructor")
    {
        ShrdPtr<int> x;
        REQUIRE(x.get() == nullptr);
        //REQUIRE_THROWS()
        //REQUIRE_NOTHROW()
    }
}
