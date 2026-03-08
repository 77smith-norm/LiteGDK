#include <catch2/catch_test_macros.hpp>

#include "images/ImageRegistry.h"

TEST_CASE("ImageRegistry stores metadata by image ID", "[images]") {
    litegdk::ImageRegistry registry;

    REQUIRE(registry.store(1, {
        .sourcePath = "tests/fixtures/assets/player.png",
        .width = 64,
        .height = 32,
    }));
    REQUIRE(registry.exists(1));
    REQUIRE(registry.activeCount() == 1);

    const auto* image = registry.find(1);
    REQUIRE(image != nullptr);
    REQUIRE(image->sourcePath == "tests/fixtures/assets/player.png");
    REQUIRE(image->width == 64);
    REQUIRE(image->height == 32);
}

TEST_CASE("ImageRegistry replaces and removes image slots deterministically", "[images]") {
    litegdk::ImageRegistry registry;

    REQUIRE(registry.store(3, {
        .sourcePath = "old.png",
        .width = 16,
        .height = 16,
    }));
    REQUIRE(registry.store(3, {
        .sourcePath = "new.png",
        .width = 32,
        .height = 48,
    }));
    REQUIRE(registry.activeCount() == 1);

    const auto* image = registry.find(3);
    REQUIRE(image != nullptr);
    REQUIRE(image->sourcePath == "new.png");
    REQUIRE(image->width == 32);
    REQUIRE(image->height == 48);

    REQUIRE(registry.remove(3));
    REQUIRE_FALSE(registry.exists(3));
    REQUIRE(registry.find(3) == nullptr);
    REQUIRE(registry.activeCount() == 0);
    REQUIRE_FALSE(registry.remove(3));
    REQUIRE_FALSE(registry.store(0, {
        .sourcePath = "invalid.png",
        .width = 1,
        .height = 1,
    }));
}
