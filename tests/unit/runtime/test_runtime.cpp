#include <catch2/catch_test_macros.hpp>
#include "LiteGDK/Runtime.h"

TEST_CASE("Runtime initializes correctly", "[runtime]") {
    litegdk::Runtime rt;
    REQUIRE_FALSE(rt.isRunning());
}
