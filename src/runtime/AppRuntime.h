#pragma once

#include "FrameState.h"

namespace litegdk {
class AppRuntime {
public:
    AppRuntime();

    void initialize();
    void shutdown();
    void reset();

    bool isInitialized() const;
    bool isRunning() const;

    FrameState& frameState();
    const FrameState& frameState() const;

private:
    bool initialized_{false};
    bool running_{false};
    FrameState frameState_{};
};

AppRuntime& runtime();
}  // namespace litegdk
