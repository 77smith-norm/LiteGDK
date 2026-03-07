#include "AppRuntime.h"

namespace litegdk {
AppRuntime::AppRuntime() {
    reset();
}

void AppRuntime::initialize() {
    initialized_ = true;
    running_ = true;
}

void AppRuntime::shutdown() {
    running_ = false;
    initialized_ = false;
}

void AppRuntime::reset() {
    initialized_ = false;
    running_ = false;
    frameState_.reset();
}

bool AppRuntime::isInitialized() const {
    return initialized_;
}

bool AppRuntime::isRunning() const {
    return running_;
}

FrameState& AppRuntime::frameState() {
    return frameState_;
}

const FrameState& AppRuntime::frameState() const {
    return frameState_;
}

AppRuntime& runtime() {
    static AppRuntime instance;
    return instance;
}
}  // namespace litegdk
