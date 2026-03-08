#include <catch2/catch_test_macros.hpp>

#include <chrono>
#include <thread>

#include "DarkGDK.h"
#include "helpers/RuntimeTestContext.h"

TEST_CASE("System helpers expose screen size, deterministic random, and timer values", "[system]") {
    litegdk::tests::RuntimeTestContext context;

    dbSetDisplayMode(1024, 768, 32);
    REQUIRE(dbScreenWidth() == 1024);
    REQUIRE(dbScreenHeight() == 768);

    dbRandomize(42);
    const auto first = dbRnd(10);
    const auto second = dbRnd(10);

    dbRandomize(42);
    REQUIRE(dbRnd(10) == first);
    REQUIRE(dbRnd(10) == second);
    REQUIRE(first >= 0);
    REQUIRE(first <= 10);
    REQUIRE(second >= 0);
    REQUIRE(second <= 10);

    const auto start = dbTimer();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
    REQUIRE(dbTimer() >= start);
}
