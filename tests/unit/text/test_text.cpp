#include <catch2/catch_test_macros.hpp>

#include "DarkGDK.h"
#include "helpers/RuntimeTestContext.h"

TEST_CASE("dbText queues draw commands using the default text color", "[text]") {
    litegdk::tests::RuntimeTestContext context;

    dbText(32, 48, "LiteGDK");

    const auto& commands = context.app().text().queuedCommands();
    REQUIRE(commands.size() == 1);

    const auto& command = commands.front();
    REQUIRE(command.x == 32);
    REQUIRE(command.y == 48);
    REQUIRE(command.text == "LiteGDK");
    REQUIRE(command.color.red == 255);
    REQUIRE(command.color.green == 255);
    REQUIRE(command.color.blue == 255);
    REQUIRE(command.color.alpha == 255);
}

TEST_CASE("dbInk updates text colors for subsequent draw calls", "[text]") {
    litegdk::tests::RuntimeTestContext context;

    dbInk(0x112233, 0x445566);
    dbText(8, 12, "Colored");

    const auto& command = context.app().text().queuedCommands().back();
    REQUIRE(command.color.red == 0x11);
    REQUIRE(command.color.green == 0x22);
    REQUIRE(command.color.blue == 0x33);
    REQUIRE(command.color.alpha == 0xFF);

    const auto background = context.app().frameState().textBackgroundColor();
    REQUIRE(background.red == 0x44);
    REQUIRE(background.green == 0x55);
    REQUIRE(background.blue == 0x66);
    REQUIRE(background.alpha == 0xFF);
}
