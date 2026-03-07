#include <catch2/catch_test_macros.hpp>

#include "DarkGDK.h"
#include "runtime/AppRuntime.h"

namespace {
struct RuntimeResetGuard {
    ~RuntimeResetGuard() {
        litegdk::runtime().reset();
    }
};
}  // namespace

TEST_CASE("dbSync advances the frame lifecycle", "[core][frame]") {
    RuntimeResetGuard guard;
    auto& app = litegdk::runtime();
    app.reset();

    REQUIRE(LoopGDK());
    REQUIRE(app.frameState().frameActive());

    dbCLS();
    REQUIRE(app.frameState().clearRequested());

    dbSync();

    REQUIRE(app.frameState().frameCount() == 1);
    REQUIRE_FALSE(app.frameState().clearRequested());
    REQUIRE_FALSE(app.frameState().frameActive());
}
