#include "FrameState.h"

namespace {
constexpr int kDefaultSyncRate = 60;
constexpr litegdk::Color kDefaultClearColor{0, 0, 0, 255};
constexpr litegdk::Color kDefaultTextColor{255, 255, 255, 255};
}  // namespace

namespace litegdk {
FrameState::FrameState() {
    reset();
}

void FrameState::reset() {
    frameCount_ = 0;
    clearRequested_ = false;
    syncEnabled_ = true;
    syncRate_ = kDefaultSyncRate;
    clearColor_ = kDefaultClearColor;
    textColor_ = kDefaultTextColor;
}

void FrameState::advanceFrame() {
    ++frameCount_;
}

std::uint64_t FrameState::frameCount() const {
    return frameCount_;
}

bool FrameState::clearRequested() const {
    return clearRequested_;
}

bool FrameState::syncEnabled() const {
    return syncEnabled_;
}

int FrameState::syncRate() const {
    return syncRate_;
}

Color FrameState::clearColor() const {
    return clearColor_;
}

Color FrameState::textColor() const {
    return textColor_;
}

void FrameState::setClearRequested(bool requested) {
    clearRequested_ = requested;
}

void FrameState::setSyncEnabled(bool enabled) {
    syncEnabled_ = enabled;
}

void FrameState::setSyncRate(int rate) {
    syncRate_ = rate < 0 ? 0 : rate;
}

void FrameState::setClearColor(Color color) {
    clearColor_ = color;
}

void FrameState::setTextColor(Color color) {
    textColor_ = color;
}
}  // namespace litegdk
