#pragma once

#include "Diagnostics.h"
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
    bool isShutdownRequested() const;

    Diagnostics& diagnostics();
    const Diagnostics& diagnostics() const;

    FrameState& frameState();
    const FrameState& frameState() const;

private:
    bool initialized_{false};
    bool running_{false};
    bool shutdownRequested_{false};
    Diagnostics diagnostics_{};
    FrameState frameState_{};
};

AppRuntime& runtime();
}  // namespace litegdk
