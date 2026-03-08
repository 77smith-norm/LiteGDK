#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "FrameState.h"

namespace litegdk {
struct TextDrawCommand {
    int x{0};
    int y{0};
    int size{20};
    std::string text{};
    Color color{255, 255, 255, 255};
};

struct SpriteDrawCommand {
    int spriteId{0};
    int imageId{0};
    float x{0.0f};
    float y{0.0f};
    float rotation{0.0f};
    float scale{1.0f};
    Color tint{255, 255, 255, 255};
};

struct ImageLoadResult {
    int width{0};
    int height{0};
};

struct BackendInputState {
    std::vector<int> downKeys{};
    int mouseX{0};
    int mouseY{0};
    bool leftButtonDown{false};
    bool rightButtonDown{false};
};

class Backend {
public:
    virtual ~Backend() = default;

    virtual void applySettings(int width, int height, int depth, int syncRate) = 0;
    virtual void reset() = 0;
    virtual void shutdown() = 0;
    virtual bool shouldClose() const = 0;

    virtual void beginFrame(Color clearColor) = 0;
    virtual void drawText(const TextDrawCommand& command) = 0;
    virtual void drawSprite(const SpriteDrawCommand& command) = 0;
    virtual void endFrame() = 0;

    virtual std::optional<ImageLoadResult> loadImage(int imageId, std::string_view path) = 0;
    virtual bool unloadImage(int imageId) = 0;
    virtual BackendInputState pollInput() const = 0;
};

std::unique_ptr<Backend> makeDefaultBackend();
}  // namespace litegdk
