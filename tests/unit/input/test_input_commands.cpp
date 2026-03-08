#include <catch2/catch_test_macros.hpp>

#include "DarkGDK.h"
#include "helpers/RuntimeTestContext.h"
#include "input/InputKeys.h"

TEST_CASE("keyboard public commands reflect the captured input snapshot", "[input]") {
    litegdk::tests::RuntimeTestContext context;

    context.app().input().capture({
        .downKeys = {
            litegdk::kInputKeyUp,
            litegdk::kInputKeySpace,
        },
    });

    REQUIRE(dbUpKey() == TRUE);
    REQUIRE(dbDownKey() == FALSE);
    REQUIRE(dbLeftKey() == FALSE);
    REQUIRE(dbRightKey() == FALSE);
    REQUIRE(dbSpaceKey() == TRUE);
    REQUIRE(dbEscapeKey() == FALSE);
    REQUIRE(dbReturnKey() == FALSE);
    REQUIRE(dbKeyState(litegdk::kInputKeyUp) == TRUE);
    REQUIRE(dbKeyState(litegdk::kInputKeyEscape) == FALSE);
}

TEST_CASE("mouse public commands reflect the captured input snapshot", "[input]") {
    litegdk::tests::RuntimeTestContext context;

    context.app().input().capture({
        .mouseX = 144,
        .mouseY = 233,
        .leftButtonDown = true,
    });

    REQUIRE(dbMouseX() == 144);
    REQUIRE(dbMouseY() == 233);
    REQUIRE(dbMouseClick() == 1);

    context.app().input().capture({
        .mouseX = 144,
        .mouseY = 233,
        .rightButtonDown = true,
    });

    REQUIRE(dbMouseClick() == 2);

    context.app().input().capture({
        .mouseX = 144,
        .mouseY = 233,
    });

    REQUIRE(dbMouseClick() == 0);
}
