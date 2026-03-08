#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "runtime/AppRuntime.h"
#include "runtime/Backend.h"

namespace litegdk::tests {
class TestBackend final : public Backend {
public:
    void applySettings(int width, int height, int depth, int syncRate) override {
        settings.width = width;
        settings.height = height;
        settings.depth = depth;
        settings.syncRate = syncRate;
        initialized = true;
    }

    void reset() override {
        initialized = false;
        beginFrameCount = 0;
        endFrameCount = 0;
        lastClearColor = {};
        textDraws.clear();
        spriteDraws.clear();
        imageLoadRequests.clear();
        unloadedImageIds.clear();
        configuredImages.clear();
        inputState = {};
        shouldCloseFlag = false;
        settings = {};
    }

    void shutdown() override {
        initialized = false;
    }

    bool shouldClose() const override {
        return shouldCloseFlag;
    }

    void beginFrame(Color clearColor) override {
        ++beginFrameCount;
        lastClearColor = clearColor;
    }

    void drawText(const TextDrawCommand& command) override {
        textDraws.push_back(command);
    }

    void drawSprite(const SpriteDrawCommand& command) override {
        spriteDraws.push_back(command);
    }

    void endFrame() override {
        ++endFrameCount;
    }

    std::optional<ImageLoadResult> loadImage(int imageId, std::string_view path) override {
        imageLoadRequests.emplace_back(std::string(path));

        const auto it = configuredImages.find(std::string(path));
        if (it == configuredImages.end()) {
            return std::nullopt;
        }

        loadedImageIds.push_back(imageId);
        return it->second;
    }

    bool unloadImage(int imageId) override {
        unloadedImageIds.push_back(imageId);
        return true;
    }

    BackendInputState pollInput() const override {
        return inputState;
    }

    struct Settings {
        int width{0};
        int height{0};
        int depth{0};
        int syncRate{0};
    };

    bool initialized{false};
    int beginFrameCount{0};
    int endFrameCount{0};
    bool shouldCloseFlag{false};
    Color lastClearColor{};
    Settings settings{};
    std::vector<TextDrawCommand> textDraws{};
    std::vector<SpriteDrawCommand> spriteDraws{};
    std::vector<std::string> imageLoadRequests{};
    std::vector<int> loadedImageIds{};
    std::vector<int> unloadedImageIds{};
    std::unordered_map<std::string, ImageLoadResult> configuredImages{};
    BackendInputState inputState{};
};

inline TestBackend* installTestBackend(AppRuntime& app) {
    auto backend = std::make_unique<TestBackend>();
    auto* backendPtr = backend.get();
    app.setBackend(std::move(backend));
    app.reset();
    return backendPtr;
}
}  // namespace litegdk::tests
