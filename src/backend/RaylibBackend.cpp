#include "runtime/Backend.h"

#include <string>
#include <unordered_map>
#include <utility>

#include "raylib.h"

namespace {
Color toRaylibColor(litegdk::Color color) {
    return Color{
        color.red,
        color.green,
        color.blue,
        color.alpha,
    };
}

class RaylibBackend final : public litegdk::Backend {
public:
    void applySettings(int width, int height, int depth, int syncRate) override {
        (void)depth;

        if (!windowOpen_) {
            InitWindow(width, height, "LiteGDK");
            windowOpen_ = true;
        } else {
            SetWindowSize(width, height);
        }

        if (syncRate > 0) {
            SetTargetFPS(syncRate);
        }
    }

    void reset() override {
        unloadTextures();

        if (windowOpen_) {
            CloseWindow();
            windowOpen_ = false;
        }
    }

    void shutdown() override {
        reset();
    }

    bool shouldClose() const override {
        return windowOpen_ && WindowShouldClose();
    }

    void beginFrame(litegdk::Color clearColor) override {
        if (!windowOpen_) {
            return;
        }

        BeginDrawing();
        ClearBackground(toRaylibColor(clearColor));
    }

    void drawText(const litegdk::TextDrawCommand& command) override {
        if (!windowOpen_) {
            return;
        }

        DrawText(command.text.c_str(),
                 command.x,
                 command.y,
                 command.size,
                 toRaylibColor(command.color));
    }

    void drawSprite(const litegdk::SpriteDrawCommand& command) override {
        if (!windowOpen_) {
            return;
        }

        const auto it = textures_.find(command.imageId);
        if (it == textures_.end()) {
            return;
        }

        DrawTextureEx(it->second,
                      Vector2{command.x, command.y},
                      command.rotation,
                      command.scale,
                      toRaylibColor(command.tint));
    }

    void endFrame() override {
        if (!windowOpen_) {
            return;
        }

        EndDrawing();
    }

    std::optional<litegdk::ImageLoadResult> loadImage(int imageId, std::string_view path) override {
        if (!windowOpen_) {
            return std::nullopt;
        }

        const Image image = LoadImage(std::string(path).c_str());
        if (image.data == nullptr || image.width <= 0 || image.height <= 0) {
            return std::nullopt;
        }

        const auto result = litegdk::ImageLoadResult{
            .width = image.width,
            .height = image.height,
        };

        const auto newTexture = LoadTextureFromImage(image);
        UnloadImage(image);

        auto replaced = textures_.find(imageId);
        if (replaced != textures_.end()) {
            UnloadTexture(replaced->second);
            replaced->second = newTexture;
        } else {
            textures_.insert_or_assign(imageId, newTexture);
        }

        return result;
    }

    bool unloadImage(int imageId) override {
        const auto it = textures_.find(imageId);
        if (it == textures_.end()) {
            return false;
        }

        UnloadTexture(it->second);
        textures_.erase(it);
        return true;
    }

    litegdk::BackendInputState pollInput() const override {
        return {};
    }

private:
    void unloadTextures() {
        for (auto& [imageId, texture] : textures_) {
            (void)imageId;
            UnloadTexture(texture);
        }

        textures_.clear();
    }

    bool windowOpen_{false};
    std::unordered_map<int, Texture2D> textures_{};
};
}  // namespace

namespace litegdk {
std::unique_ptr<Backend> makeDefaultBackend() {
    return std::make_unique<RaylibBackend>();
}
}  // namespace litegdk
