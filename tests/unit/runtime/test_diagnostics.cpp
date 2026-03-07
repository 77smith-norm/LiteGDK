#include <catch2/catch_test_macros.hpp>

#include <string>

#include "LiteGDK/Compatibility.h"
#include "runtime/AppRuntime.h"

TEST_CASE("AppRuntime records structured compatibility warnings", "[runtime][diagnostics]") {
    litegdk::AppRuntime runtime;

    REQUIRE(runtime.diagnostics().empty());

    runtime.diagnostics().warn(
        litegdk::CompatibilityCode::approximateBehavior,
        litegdk::CompatibilityTier::C,
        "dbLoadImage",
        "Texture filtering may differ from DarkGDK");

    REQUIRE(runtime.diagnostics().count() == 1);

    const auto& warnings = runtime.diagnostics().warnings();
    REQUIRE(warnings.size() == 1);
    CHECK(warnings.front().code == litegdk::CompatibilityCode::approximateBehavior);
    CHECK(warnings.front().tier == litegdk::CompatibilityTier::C);
    CHECK(warnings.front().command == "dbLoadImage");
    CHECK(warnings.front().detail == "Texture filtering may differ from DarkGDK");

    runtime.reset();

    REQUIRE(runtime.diagnostics().empty());
}
