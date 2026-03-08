#include <catch2/catch_test_macros.hpp>

#include "basic3d/ObjectRegistry.h"

TEST_CASE("ObjectRegistry stores primitive transforms by object ID", "[basic3d][objects]") {
    litegdk::ObjectRegistry registry;

    REQUIRE(registry.store(2, {
        .primitiveType = litegdk::PrimitiveType::cube,
        .dimensions = {10.0f, 20.0f, 30.0f},
        .position = {1.0f, 2.0f, 3.0f},
        .rotation = {15.0f, 30.0f, 45.0f},
        .scale = {1.0f, 2.0f, 3.0f},
    }));
    REQUIRE(registry.exists(2));
    REQUIRE(registry.activeCount() == 1);

    const auto* object = registry.find(2);
    REQUIRE(object != nullptr);
    REQUIRE(object->primitiveType == litegdk::PrimitiveType::cube);
    REQUIRE(object->dimensions.x == 10.0f);
    REQUIRE(object->dimensions.y == 20.0f);
    REQUIRE(object->dimensions.z == 30.0f);
    REQUIRE(object->position.x == 1.0f);
    REQUIRE(object->position.y == 2.0f);
    REQUIRE(object->position.z == 3.0f);
    REQUIRE(object->rotation.x == 15.0f);
    REQUIRE(object->rotation.y == 30.0f);
    REQUIRE(object->rotation.z == 45.0f);
    REQUIRE(object->scale.x == 1.0f);
    REQUIRE(object->scale.y == 2.0f);
    REQUIRE(object->scale.z == 3.0f);
    REQUIRE(object->visible);
}

TEST_CASE("ObjectRegistry preserves default transform values for sphere primitives", "[basic3d][objects]") {
    litegdk::ObjectRegistry registry;

    REQUIRE(registry.store(3, {
        .primitiveType = litegdk::PrimitiveType::sphere,
        .radius = 6.0f,
    }));

    const auto* object = registry.find(3);
    REQUIRE(object != nullptr);
    REQUIRE(object->primitiveType == litegdk::PrimitiveType::sphere);
    REQUIRE(object->radius == 6.0f);
    REQUIRE(object->position.x == 0.0f);
    REQUIRE(object->position.y == 0.0f);
    REQUIRE(object->position.z == 0.0f);
    REQUIRE(object->rotation.x == 0.0f);
    REQUIRE(object->rotation.y == 0.0f);
    REQUIRE(object->rotation.z == 0.0f);
    REQUIRE(object->scale.x == 1.0f);
    REQUIRE(object->scale.y == 1.0f);
    REQUIRE(object->scale.z == 1.0f);
    REQUIRE(object->visible);
}

TEST_CASE("ObjectRegistry replaces and removes object slots deterministically", "[basic3d][objects]") {
    litegdk::ObjectRegistry registry;

    REQUIRE(registry.store(5, {
        .primitiveType = litegdk::PrimitiveType::sphere,
        .radius = 2.5f,
        .visible = false,
    }));
    REQUIRE(registry.store(5, {
        .primitiveType = litegdk::PrimitiveType::cube,
        .dimensions = {8.0f, 8.0f, 8.0f},
        .scale = {4.0f, 5.0f, 6.0f},
    }));
    REQUIRE(registry.activeCount() == 1);

    const auto* object = registry.find(5);
    REQUIRE(object != nullptr);
    REQUIRE(object->primitiveType == litegdk::PrimitiveType::cube);
    REQUIRE(object->dimensions.x == 8.0f);
    REQUIRE(object->scale.x == 4.0f);
    REQUIRE(object->scale.y == 5.0f);
    REQUIRE(object->scale.z == 6.0f);
    REQUIRE(object->visible);

    REQUIRE(registry.remove(5));
    REQUIRE_FALSE(registry.exists(5));
    REQUIRE(registry.find(5) == nullptr);
    REQUIRE(registry.activeCount() == 0);
    REQUIRE_FALSE(registry.remove(5));
    REQUIRE_FALSE(registry.store(0, {
        .primitiveType = litegdk::PrimitiveType::cube,
    }));
}
