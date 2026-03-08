#pragma once

#include <memory>

#include "images/ImageRegistry.h"
#include "input/InputSnapshot.h"
#include "Backend.h"
#include "Diagnostics.h"
#include "FrameState.h"
#include "sound/MusicRegistry.h"
#include "sound/SoundRegistry.h"
#include "sprites/SpriteRegistry.h"
#include "text/TextService.h"

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

    void applyBackendSettings();
    void setDisplayMode(int width, int height, int depth);

    Diagnostics& diagnostics();
    const Diagnostics& diagnostics() const;

    Backend& backend();
    const Backend& backend() const;
    void setBackend(std::unique_ptr<Backend> backend);

    FrameState& frameState();
    const FrameState& frameState() const;

    ImageRegistry& images();
    const ImageRegistry& images() const;
    InputSnapshot& input();
    const InputSnapshot& input() const;
    SoundRegistry& sounds();
    const SoundRegistry& sounds() const;
    MusicRegistry& music();
    const MusicRegistry& music() const;
    SpriteRegistry& sprites();
    const SpriteRegistry& sprites() const;
    TextService& text();
    const TextService& text() const;
    void renderFrame();

private:
    bool initialized_{false};
    bool running_{false};
    bool shutdownRequested_{false};
    int displayWidth_{800};
    int displayHeight_{600};
    int displayDepth_{32};
    std::unique_ptr<Backend> backend_{};
    Diagnostics diagnostics_{};
    FrameState frameState_{};
    ImageRegistry images_{};
    InputSnapshot input_{};
    SoundRegistry sounds_{};
    MusicRegistry music_{};
    SpriteRegistry sprites_{};
    TextService text_{};
};

AppRuntime& runtime();
}  // namespace litegdk
