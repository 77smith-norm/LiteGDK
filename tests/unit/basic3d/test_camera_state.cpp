#include <catch2/catch_test_macros.hpp>

#include "basic3d/CameraState.h"

TEST_CASE("CameraState starts from deterministic 3D defaults", "[basic3d][camera]") {
    litegdk::CameraState camera;

    const auto position = camera.position();
    REQUIRE(position.x == 0.0f);
    REQUIRE(position.y == 0.0f);
    REQUIRE(position.z == -10.0f);

    const auto target = camera.target();
    REQUIRE(target.x == 0.0f);
    REQUIRE(target.y == 0.0f);
    REQUIRE(target.z == 0.0f);

    const auto up = camera.up();
    REQUIRE(up.x == 0.0f);
    REQUIRE(up.y == 1.0f);
    REQUIRE(up.z == 0.0f);

    const auto rotation = camera.rotation();
    REQUIRE(rotation.x == 0.0f);
    REQUIRE(rotation.y == 0.0f);
    REQUIRE(rotation.z == 0.0f);

    REQUIRE(camera.fovDegrees() == 45.0f);
    REQUIRE(camera.projectionMode() == litegdk::ProjectionMode::perspective);
}

TEST_CASE("CameraState mutates and resets independently of rendering", "[basic3d][camera]") {
    litegdk::CameraState camera;

    camera.setPosition({12.0f, 24.0f, -36.0f});
    camera.setTarget({4.0f, 5.0f, 6.0f});
    camera.setUp({0.0f, 0.0f, 1.0f});
    camera.setRotation({15.0f, 30.0f, 45.0f});
    camera.setFovDegrees(60.0f);
    camera.setProjectionMode(litegdk::ProjectionMode::orthographic);

    REQUIRE(camera.position().x == 12.0f);
    REQUIRE(camera.position().y == 24.0f);
    REQUIRE(camera.position().z == -36.0f);
    REQUIRE(camera.target().x == 4.0f);
    REQUIRE(camera.target().y == 5.0f);
    REQUIRE(camera.target().z == 6.0f);
    REQUIRE(camera.up().z == 1.0f);
    REQUIRE(camera.rotation().x == 15.0f);
    REQUIRE(camera.rotation().y == 30.0f);
    REQUIRE(camera.rotation().z == 45.0f);
    REQUIRE(camera.fovDegrees() == 60.0f);
    REQUIRE(camera.projectionMode() == litegdk::ProjectionMode::orthographic);

    camera.reset();

    REQUIRE(camera.position().z == -10.0f);
    REQUIRE(camera.target().z == 0.0f);
    REQUIRE(camera.up().y == 1.0f);
    REQUIRE(camera.rotation().x == 0.0f);
    REQUIRE(camera.fovDegrees() == 45.0f);
    REQUIRE(camera.projectionMode() == litegdk::ProjectionMode::perspective);
}
