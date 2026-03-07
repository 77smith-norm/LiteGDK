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

    int displayWidth() const;
    int displayHeight() const;
    int displayDepth() const;

    void setDisplayMode(int width, int height, int depth);

    Diagnostics& diagnostics();
    const Diagnostics& diagnostics() const;

    FrameState& frameState();
    const FrameState& frameState() const;

private:
    bool initialized_{false};
    bool running_{false};
    bool shutdownRequested_{false};
    int displayWidth_{800};
    int displayHeight_{600};
    int displayDepth_{32};
    Diagnostics diagnostics_{};
    FrameState frameState_{};
};

AppRuntime& runtime();
}  // namespace litegdk
