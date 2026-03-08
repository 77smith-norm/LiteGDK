#include "FrameRunner.h"

#include "runtime/AppRuntime.h"

namespace {
void ensureInitialized(litegdk::AppRuntime& app) {
    if (!app.isInitialized() && !app.isShutdownRequested()) {
        app.initialize();
    }
}
}  // namespace

namespace litegdk {
void beginFrame() {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    ensureInitialized(app);
    app.frameState().setFrameActive(true);
}

void syncFrame() {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    ensureInitialized(app);
    if (!app.frameState().frameActive()) {
        beginFrame();
    }

    app.renderFrame();
    app.input().capture(app.backend().pollInput());
    app.frameState().setClearRequested(false);
    app.frameState().advanceFrame();
    app.frameState().setFrameActive(false);
}
}  // namespace litegdk
