#pragma once

#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

#include "basic3d/Types.h"
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

struct Camera3DDrawCommand {
    Vector3 position{};
    Vector3 target{};
    Vector3 up{0.0f, 1.0f, 0.0f};
    float fovDegrees{45.0f};
    ProjectionMode projectionMode{ProjectionMode::perspective};
};

struct Object3DDrawCommand {
    int objectId{0};
    PrimitiveType primitiveType{PrimitiveType::cube};
    Vector3 dimensions{1.0f, 1.0f, 1.0f};
    float radius{0.5f};
    Vector3 position{};
    Vector3 rotation{};
    Vector3 scale{1.0f, 1.0f, 1.0f};
};

struct ImageLoadResult {
    int width{0};
    int height{0};
};

struct SoundVolumeChange {
    int soundId{0};
    float volume{1.0f};
};

struct MusicVolumeChange {
    int musicId{0};
    float volume{1.0f};
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
    virtual void begin3D(const Camera3DDrawCommand& command) = 0;
    virtual void drawObject3D(const Object3DDrawCommand& command) = 0;
    virtual void end3D() = 0;
    virtual void drawText(const TextDrawCommand& command) = 0;
    virtual void drawSprite(const SpriteDrawCommand& command) = 0;
    virtual void updateAudio() = 0;
    virtual void endFrame() = 0;

    virtual std::optional<ImageLoadResult> loadImage(int imageId, std::string_view path) = 0;
    virtual bool unloadImage(int imageId) = 0;
    virtual bool loadSound(int soundId, std::string_view path) = 0;
    virtual bool unloadSound(int soundId) = 0;
    virtual bool playSound(int soundId) = 0;
    virtual bool stopSound(int soundId) = 0;
    virtual bool setSoundVolume(int soundId, float volume) = 0;
    virtual bool loadMusic(int musicId, std::string_view path) = 0;
    virtual bool unloadMusic(int musicId) = 0;
    virtual bool playMusic(int musicId) = 0;
    virtual bool stopMusic(int musicId) = 0;
    virtual bool pauseMusic(int musicId) = 0;
    virtual bool resumeMusic(int musicId) = 0;
    virtual bool setMusicVolume(int musicId, float volume) = 0;
    virtual BackendInputState pollInput() const = 0;
};

std::unique_ptr<Backend> makeDefaultBackend();
}  // namespace litegdk
