#include <catch2/catch_test_macros.hpp>

#include "DarkGDK.h"
#include "helpers/RuntimeTestContext.h"

TEST_CASE("dbSync advances the frame lifecycle", "[core][frame]") {
    litegdk::tests::RuntimeTestContext context;
    auto& app = context.app();

    REQUIRE(LoopGDK());
    REQUIRE(app.frameState().frameActive());

    dbCLS();
    REQUIRE(app.frameState().clearRequested());

    dbSync();

    REQUIRE(app.frameState().frameCount() == 1);
    REQUIRE_FALSE(app.frameState().clearRequested());
    REQUIRE_FALSE(app.frameState().frameActive());
}
