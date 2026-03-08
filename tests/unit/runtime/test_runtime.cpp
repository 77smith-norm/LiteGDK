#include <catch2/catch_test_macros.hpp>

#include "helpers/TestBackend.h"
#include "runtime/AppRuntime.h"
#include "runtime/FrameState.h"

TEST_CASE("AppRuntime starts from deterministic defaults", "[runtime]") {
    litegdk::AppRuntime runtime;

    REQUIRE_FALSE(runtime.isInitialized());
    REQUIRE_FALSE(runtime.isRunning());

    const auto& frame = runtime.frameState();
    REQUIRE(frame.frameCount() == 0);
    REQUIRE(frame.syncEnabled());
    REQUIRE(frame.syncRate() == 60);

    const auto clear = frame.clearColor();
    REQUIRE(clear.red == 0);
    REQUIRE(clear.green == 0);
    REQUIRE(clear.blue == 0);
    REQUIRE(clear.alpha == 255);

    const auto text = frame.textColor();
    REQUIRE(text.red == 255);
    REQUIRE(text.green == 255);
    REQUIRE(text.blue == 255);
    REQUIRE(text.alpha == 255);

    const auto background = frame.textBackgroundColor();
    REQUIRE(background.red == 0);
    REQUIRE(background.green == 0);
    REQUIRE(background.blue == 0);
    REQUIRE(background.alpha == 255);
}

TEST_CASE("FrameState tracks mutable frame settings", "[runtime]") {
    litegdk::FrameState frame;

    frame.advanceFrame();
    frame.setSyncEnabled(false);
    frame.setSyncRate(30);
    frame.setClearColor({12, 34, 56, 200});

    REQUIRE(frame.frameCount() == 1);
    REQUIRE_FALSE(frame.syncEnabled());
    REQUIRE(frame.syncRate() == 30);

    const auto clear = frame.clearColor();
    REQUIRE(clear.red == 12);
    REQUIRE(clear.green == 34);
    REQUIRE(clear.blue == 56);
    REQUIRE(clear.alpha == 200);
}

TEST_CASE("AppRuntime reset restores defaults", "[runtime]") {
    litegdk::AppRuntime runtime;
    litegdk::tests::installTestBackend(runtime);
    runtime.initialize();
    runtime.frameState().advanceFrame();
    runtime.frameState().setSyncEnabled(false);
    runtime.frameState().setSyncRate(15);
    runtime.frameState().setClearColor({90, 80, 70, 255});
    runtime.frameState().setTextColor({10, 20, 30, 255});
    runtime.frameState().setTextBackgroundColor({30, 20, 10, 255});

    runtime.reset();

    REQUIRE_FALSE(runtime.isInitialized());
    REQUIRE_FALSE(runtime.isRunning());

    const auto& frame = runtime.frameState();
    REQUIRE(frame.frameCount() == 0);
    REQUIRE(frame.syncEnabled());
    REQUIRE(frame.syncRate() == 60);

    const auto clear = frame.clearColor();
    REQUIRE(clear.red == 0);
    REQUIRE(clear.green == 0);
    REQUIRE(clear.blue == 0);
    REQUIRE(clear.alpha == 255);

    const auto text = frame.textColor();
    REQUIRE(text.red == 255);
    REQUIRE(text.green == 255);
    REQUIRE(text.blue == 255);
    REQUIRE(text.alpha == 255);

    const auto background = frame.textBackgroundColor();
    REQUIRE(background.red == 0);
    REQUIRE(background.green == 0);
    REQUIRE(background.blue == 0);
    REQUIRE(background.alpha == 255);
}
