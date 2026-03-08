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
