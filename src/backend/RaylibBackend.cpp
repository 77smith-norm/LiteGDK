#include "runtime/Backend.h"

#include <string>
#include <unordered_map>
#include <utility>

#include "input/InputKeys.h"
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

        ensureAudioDeviceOpen();
    }

    void reset() override {
        unloadAudio();
        unloadTextures();

        if (windowOpen_) {
            CloseWindow();
            windowOpen_ = false;
        }

        if (audioOpen_) {
            CloseAudioDevice();
            audioOpen_ = false;
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

    void updateAudio() override {
        if (!audioOpen_) {
            return;
        }

        for (auto& [musicId, music] : music_) {
            (void)musicId;
            UpdateMusicStream(music);
        }
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

    bool loadSound(int soundId, std::string_view path) override {
        ensureAudioDeviceOpen();
        if (!audioOpen_) {
            return false;
        }

        const auto sound = LoadSound(std::string(path).c_str());
        if (sound.frameCount == 0 || sound.stream.buffer == nullptr) {
            return false;
        }

        auto replaced = sounds_.find(soundId);
        if (replaced != sounds_.end()) {
            UnloadSound(replaced->second);
            replaced->second = sound;
        } else {
            sounds_.insert_or_assign(soundId, sound);
        }

        return true;
    }

    bool unloadSound(int soundId) override {
        const auto it = sounds_.find(soundId);
        if (it == sounds_.end()) {
            return false;
        }

        UnloadSound(it->second);
        sounds_.erase(it);
        return true;
    }

    bool playSound(int soundId) override {
        const auto it = sounds_.find(soundId);
        if (it == sounds_.end()) {
            return false;
        }

        PlaySound(it->second);
        return true;
    }

    bool stopSound(int soundId) override {
        const auto it = sounds_.find(soundId);
        if (it == sounds_.end()) {
            return false;
        }

        StopSound(it->second);
        return true;
    }

    bool setSoundVolume(int soundId, float volume) override {
        const auto it = sounds_.find(soundId);
        if (it == sounds_.end()) {
            return false;
        }

        SetSoundVolume(it->second, volume);
        return true;
    }

    bool loadMusic(int musicId, std::string_view path) override {
        ensureAudioDeviceOpen();
        if (!audioOpen_) {
            return false;
        }

        auto music = LoadMusicStream(std::string(path).c_str());
        if (music.frameCount == 0 || music.stream.buffer == nullptr) {
            return false;
        }

        auto replaced = music_.find(musicId);
        if (replaced != music_.end()) {
            UnloadMusicStream(replaced->second);
            replaced->second = music;
        } else {
            music_.insert_or_assign(musicId, music);
        }

        return true;
    }

    bool unloadMusic(int musicId) override {
        const auto it = music_.find(musicId);
        if (it == music_.end()) {
            return false;
        }

        UnloadMusicStream(it->second);
        music_.erase(it);
        return true;
    }

    bool playMusic(int musicId) override {
        const auto it = music_.find(musicId);
        if (it == music_.end()) {
            return false;
        }

        PlayMusicStream(it->second);
        return true;
    }

    bool stopMusic(int musicId) override {
        const auto it = music_.find(musicId);
        if (it == music_.end()) {
            return false;
        }

        StopMusicStream(it->second);
        return true;
    }

    bool pauseMusic(int musicId) override {
        const auto it = music_.find(musicId);
        if (it == music_.end()) {
            return false;
        }

        PauseMusicStream(it->second);
        return true;
    }

    bool resumeMusic(int musicId) override {
        const auto it = music_.find(musicId);
        if (it == music_.end()) {
            return false;
        }

        ResumeMusicStream(it->second);
        return true;
    }

    bool setMusicVolume(int musicId, float volume) override {
        const auto it = music_.find(musicId);
        if (it == music_.end()) {
            return false;
        }

        SetMusicVolume(it->second, volume);
        return true;
    }

    litegdk::BackendInputState pollInput() const override {
        if (!windowOpen_) {
            return {};
        }

        litegdk::BackendInputState state;
        if (IsKeyDown(KEY_UP)) {
            state.downKeys.push_back(litegdk::kInputKeyUp);
        }

        if (IsKeyDown(KEY_DOWN)) {
            state.downKeys.push_back(litegdk::kInputKeyDown);
        }

        if (IsKeyDown(KEY_LEFT)) {
            state.downKeys.push_back(litegdk::kInputKeyLeft);
        }

        if (IsKeyDown(KEY_RIGHT)) {
            state.downKeys.push_back(litegdk::kInputKeyRight);
        }

        if (IsKeyDown(KEY_SPACE)) {
            state.downKeys.push_back(litegdk::kInputKeySpace);
        }

        if (IsKeyDown(KEY_ESCAPE)) {
            state.downKeys.push_back(litegdk::kInputKeyEscape);
        }

        if (IsKeyDown(KEY_ENTER)) {
            state.downKeys.push_back(litegdk::kInputKeyReturn);
        }

        state.mouseX = GetMouseX();
        state.mouseY = GetMouseY();
        state.leftButtonDown = IsMouseButtonDown(MOUSE_BUTTON_LEFT);
        state.rightButtonDown = IsMouseButtonDown(MOUSE_BUTTON_RIGHT);
        return state;
    }

private:
    void ensureAudioDeviceOpen() {
        if (!audioOpen_) {
            InitAudioDevice();
            audioOpen_ = IsAudioDeviceReady();
        }
    }

    void unloadTextures() {
        for (auto& [imageId, texture] : textures_) {
            (void)imageId;
            UnloadTexture(texture);
        }

        textures_.clear();
    }

    void unloadAudio() {
        for (auto& [soundId, sound] : sounds_) {
            (void)soundId;
            UnloadSound(sound);
        }
        sounds_.clear();

        for (auto& [musicId, music] : music_) {
            (void)musicId;
            UnloadMusicStream(music);
        }
        music_.clear();
    }

    bool windowOpen_{false};
    bool audioOpen_{false};
    std::unordered_map<int, Texture2D> textures_{};
    std::unordered_map<int, Sound> sounds_{};
    std::unordered_map<int, Music> music_{};
};
}  // namespace

namespace litegdk {
std::unique_ptr<Backend> makeDefaultBackend() {
    return std::make_unique<RaylibBackend>();
}
}  // namespace litegdk
