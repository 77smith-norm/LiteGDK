#include "AppRuntime.h"

namespace litegdk {
namespace {
constexpr int kDefaultDisplayWidth = 800;
constexpr int kDefaultDisplayHeight = 600;
constexpr int kDefaultDisplayDepth = 32;
}  // namespace

AppRuntime::AppRuntime() {
    reset();
}

void AppRuntime::initialize() {
    initialized_ = true;
    running_ = true;
    shutdownRequested_ = false;
}

void AppRuntime::shutdown() {
    running_ = false;
    initialized_ = false;
    shutdownRequested_ = true;
}

void AppRuntime::reset() {
    initialized_ = false;
    running_ = false;
    shutdownRequested_ = false;
    displayWidth_ = kDefaultDisplayWidth;
    displayHeight_ = kDefaultDisplayHeight;
    displayDepth_ = kDefaultDisplayDepth;
    diagnostics_.clear();
    frameState_.reset();
}

bool AppRuntime::isInitialized() const {
    return initialized_;
}

bool AppRuntime::isRunning() const {
    return running_;
}

bool AppRuntime::isShutdownRequested() const {
    return shutdownRequested_;
}

int AppRuntime::displayWidth() const {
    return displayWidth_;
}

int AppRuntime::displayHeight() const {
    return displayHeight_;
}

int AppRuntime::displayDepth() const {
    return displayDepth_;
}

void AppRuntime::setDisplayMode(int width, int height, int depth) {
    displayWidth_ = width;
    displayHeight_ = height;
    displayDepth_ = depth;
}

Diagnostics& AppRuntime::diagnostics() {
    return diagnostics_;
}

const Diagnostics& AppRuntime::diagnostics() const {
    return diagnostics_;
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
