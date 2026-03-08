#include <catch2/catch_test_macros.hpp>

#include "DarkGDK.h"
#include "core/Lifecycle.h"
#include "helpers/RuntimeTestContext.h"

TEST_CASE("Core lifecycle commands update runtime state", "[core][lifecycle]") {
    litegdk::tests::RuntimeTestContext context;
    auto& app = context.app();

    REQUIRE_FALSE(app.isInitialized());

    dbSyncOff();
    REQUIRE(app.isInitialized());
    REQUIRE_FALSE(app.frameState().syncEnabled());

    dbSyncOn();
    REQUIRE(app.frameState().syncEnabled());

    dbSyncRate(30);
    REQUIRE(app.frameState().syncRate() == 30);

    dbCLS();
    REQUIRE(app.frameState().clearRequested());

    REQUIRE(LoopGDK());

    litegdk::requestShutdown();
    REQUIRE_FALSE(LoopGDK());
    REQUIRE_FALSE(app.isRunning());
}
