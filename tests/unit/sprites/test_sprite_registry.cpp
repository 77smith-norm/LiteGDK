#include <catch2/catch_test_macros.hpp>

#include "sprites/SpriteRegistry.h"

TEST_CASE("SpriteRegistry stores sprite state with predictable defaults", "[sprites]") {
    litegdk::SpriteRegistry registry;

    REQUIRE(registry.store(2, {
        .imageId = 7,
        .x = 32.0f,
        .y = 48.0f,
    }));

    const auto* sprite = registry.find(2);
    REQUIRE(sprite != nullptr);
    REQUIRE(sprite->imageId == 7);
    REQUIRE(sprite->x == 32.0f);
    REQUIRE(sprite->y == 48.0f);
    REQUIRE(sprite->visible);
    REQUIRE(sprite->rotationDegrees == 0.0f);
    REQUIRE(sprite->scale == 1.0f);
    REQUIRE(sprite->tint.red == 255);
    REQUIRE(sprite->tint.green == 255);
    REQUIRE(sprite->tint.blue == 255);
    REQUIRE(sprite->tint.alpha == 255);
}

TEST_CASE("SpriteRegistry replaces and removes sprite slots deterministically", "[sprites]") {
    litegdk::SpriteRegistry registry;

    REQUIRE(registry.store(5, {
        .imageId = 1,
        .x = 10.0f,
        .y = 20.0f,
    }));
    REQUIRE(registry.store(5, {
        .imageId = 3,
        .x = 100.0f,
        .y = 200.0f,
        .visible = false,
        .rotationDegrees = 45.0f,
        .scale = 2.0f,
    }));
    REQUIRE(registry.activeCount() == 1);

    const auto* sprite = registry.find(5);
    REQUIRE(sprite != nullptr);
    REQUIRE(sprite->imageId == 3);
    REQUIRE(sprite->x == 100.0f);
    REQUIRE(sprite->y == 200.0f);
    REQUIRE_FALSE(sprite->visible);
    REQUIRE(sprite->rotationDegrees == 45.0f);
    REQUIRE(sprite->scale == 2.0f);

    REQUIRE(registry.remove(5));
    REQUIRE_FALSE(registry.exists(5));
    REQUIRE(registry.find(5) == nullptr);
    REQUIRE_FALSE(registry.remove(5));
    REQUIRE_FALSE(registry.store(0, {
        .imageId = 1,
        .x = 0.0f,
        .y = 0.0f,
    }));
}
