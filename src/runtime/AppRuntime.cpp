#include "AppRuntime.h"

namespace litegdk {
namespace {
constexpr int kDefaultDisplayWidth = 800;
constexpr int kDefaultDisplayHeight = 600;
constexpr int kDefaultDisplayDepth = 32;
}  // namespace

AppRuntime::AppRuntime()
    : backend_(makeDefaultBackend()) {
    reset();
}

void AppRuntime::initialize() {
    applyBackendSettings();
    initialized_ = true;
    running_ = true;
    shutdownRequested_ = false;
}

void AppRuntime::shutdown() {
    if (backend_) {
        backend_->shutdown();
    }

    running_ = false;
    initialized_ = false;
    shutdownRequested_ = true;
}

void AppRuntime::reset() {
    if (backend_) {
        backend_->reset();
    }

    initialized_ = false;
    running_ = false;
    shutdownRequested_ = false;
    displayWidth_ = kDefaultDisplayWidth;
    displayHeight_ = kDefaultDisplayHeight;
    displayDepth_ = kDefaultDisplayDepth;
    diagnostics_.clear();
    frameState_.reset();
    images_.reset();
    text_.reset();
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

void AppRuntime::applyBackendSettings() {
    if (backend_) {
        backend_->applySettings(displayWidth_, displayHeight_, displayDepth_, frameState_.syncRate());
    }
}

void AppRuntime::setDisplayMode(int width, int height, int depth) {
    displayWidth_ = width;
    displayHeight_ = height;
    displayDepth_ = depth;

    if (initialized_) {
        applyBackendSettings();
    }
}

Diagnostics& AppRuntime::diagnostics() {
    return diagnostics_;
}

const Diagnostics& AppRuntime::diagnostics() const {
    return diagnostics_;
}

Backend& AppRuntime::backend() {
    return *backend_;
}

const Backend& AppRuntime::backend() const {
    return *backend_;
}

void AppRuntime::setBackend(std::unique_ptr<Backend> backend) {
    if (backend_) {
        backend_->shutdown();
    }

    backend_ = std::move(backend);
    if (!backend_) {
        backend_ = makeDefaultBackend();
    }

    if (initialized_) {
        applyBackendSettings();
    }
}

FrameState& AppRuntime::frameState() {
    return frameState_;
}

const FrameState& AppRuntime::frameState() const {
    return frameState_;
}

ImageRegistry& AppRuntime::images() {
    return images_;
}

const ImageRegistry& AppRuntime::images() const {
    return images_;
}

TextService& AppRuntime::text() {
    return text_;
}

const TextService& AppRuntime::text() const {
    return text_;
}

void AppRuntime::renderFrame() {
    if (!initialized_ || !backend_) {
        return;
    }

    backend_->beginFrame(frameState_.clearColor());

    for (const auto& command : text_.queuedCommands()) {
        backend_->drawText(command);
    }

    backend_->endFrame();
    text_.clearQueuedCommands();
}

AppRuntime& runtime() {
    static AppRuntime instance;
    return instance;
}
}  // namespace litegdk
