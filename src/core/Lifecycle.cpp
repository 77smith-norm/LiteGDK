#include "Lifecycle.h"

#include "runtime/AppRuntime.h"

namespace {
void ensureInitialized(litegdk::AppRuntime& app) {
    if (!app.isInitialized() && !app.isShutdownRequested()) {
        app.initialize();
    }
}
}  // namespace

namespace litegdk {
void syncOn() {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    ensureInitialized(app);
    app.frameState().setSyncEnabled(true);
}

void syncOff() {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    ensureInitialized(app);
    app.frameState().setSyncEnabled(false);
}

void setSyncRate(int rate) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    ensureInitialized(app);
    app.frameState().setSyncRate(rate);
}

void clearScreen() {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    ensureInitialized(app);
    app.frameState().setClearRequested(true);
}

bool loop() {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return false;
    }

    ensureInitialized(app);
    return app.isRunning();
}

void setDisplayMode(int width, int height, int depth) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    ensureInitialized(app);
    (void)width;
    (void)height;
    (void)depth;
}

void requestShutdown() {
    runtime().shutdown();
}
}  // namespace litegdk
