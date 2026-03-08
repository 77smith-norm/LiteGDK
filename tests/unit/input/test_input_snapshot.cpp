#include <catch2/catch_test_macros.hpp>

#include "input/InputSnapshot.h"

TEST_CASE("InputSnapshot tracks key pressed, held, and released transitions", "[input]") {
    litegdk::InputSnapshot snapshot;

    snapshot.capture({
        .downKeys = {38},
    });

    REQUIRE(snapshot.isKeyDown(38));
    REQUIRE(snapshot.wasKeyPressed(38));
    REQUIRE_FALSE(snapshot.wasKeyReleased(38));

    snapshot.capture({
        .downKeys = {38},
    });

    REQUIRE(snapshot.isKeyDown(38));
    REQUIRE_FALSE(snapshot.wasKeyPressed(38));
    REQUIRE_FALSE(snapshot.wasKeyReleased(38));

    snapshot.capture({});

    REQUIRE_FALSE(snapshot.isKeyDown(38));
    REQUIRE_FALSE(snapshot.wasKeyPressed(38));
    REQUIRE(snapshot.wasKeyReleased(38));
}

TEST_CASE("InputSnapshot tracks mouse position and button transitions", "[input]") {
    litegdk::InputSnapshot snapshot;

    snapshot.capture({
        .mouseX = 120,
        .mouseY = 45,
        .leftButtonDown = true,
    });

    REQUIRE(snapshot.mouseX() == 120);
    REQUIRE(snapshot.mouseY() == 45);
    REQUIRE(snapshot.isLeftButtonDown());
    REQUIRE(snapshot.wasLeftButtonPressed());
    REQUIRE_FALSE(snapshot.wasLeftButtonReleased());

    snapshot.capture({
        .mouseX = 121,
        .mouseY = 46,
        .leftButtonDown = true,
    });

    REQUIRE(snapshot.mouseX() == 121);
    REQUIRE(snapshot.mouseY() == 46);
    REQUIRE(snapshot.isLeftButtonDown());
    REQUIRE_FALSE(snapshot.wasLeftButtonPressed());
    REQUIRE_FALSE(snapshot.wasLeftButtonReleased());

    snapshot.capture({
        .mouseX = 121,
        .mouseY = 46,
        .leftButtonDown = false,
    });

    REQUIRE_FALSE(snapshot.isLeftButtonDown());
    REQUIRE_FALSE(snapshot.wasLeftButtonPressed());
    REQUIRE(snapshot.wasLeftButtonReleased());
}
