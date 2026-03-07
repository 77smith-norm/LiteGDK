#include <catch2/catch_test_macros.hpp>

#include <string>

#include "runtime/HandlePolicies.h"
#include "runtime/Registry.h"

TEST_CASE("Registry inserts and finds values by handle", "[runtime][registry]") {
    litegdk::Registry<std::string> registry;

    REQUIRE(registry.insertOrAssign(1, "alpha"));
    REQUIRE(registry.insertOrAssign(3, "gamma"));
    REQUIRE(registry.activeCount() == 2);

    const auto* first = registry.find(1);
    REQUIRE(first != nullptr);
    REQUIRE(*first == "alpha");

    REQUIRE(registry.find(2) == nullptr);

    const auto* third = registry.find(3);
    REQUIRE(third != nullptr);
    REQUIRE(*third == "gamma");
}

TEST_CASE("Registry remove clears occupied slots", "[runtime][registry]") {
    litegdk::Registry<int> registry;
    REQUIRE(registry.insertOrAssign(2, 99));

    REQUIRE(registry.remove(2));
    REQUIRE(registry.activeCount() == 0);
    REQUIRE(registry.find(2) == nullptr);
    REQUIRE_FALSE(registry.remove(2));
}

TEST_CASE("Registry replaces existing handles without growing occupancy", "[runtime][registry]") {
    litegdk::Registry<int> registry;
    REQUIRE(registry.insertOrAssign(4, 10));
    REQUIRE(registry.insertOrAssign(4, 20));

    REQUIRE(registry.activeCount() == 1);

    const auto* value = registry.find(4);
    REQUIRE(value != nullptr);
    REQUIRE(*value == 20);
}

TEST_CASE("Registry rejects invalid and missing handles", "[runtime][registry]") {
    litegdk::Registry<int> registry;

    REQUIRE_FALSE(litegdk::isValidHandle(0));
    REQUIRE_FALSE(registry.insertOrAssign(0, 7));
    REQUIRE(registry.find(0) == nullptr);
    REQUIRE_FALSE(registry.remove(0));
    REQUIRE(registry.find(5) == nullptr);
    REQUIRE_FALSE(registry.remove(5));
}
