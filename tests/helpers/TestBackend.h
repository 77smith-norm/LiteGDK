#pragma once

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "runtime/AppRuntime.h"
#include "runtime/Backend.h"

namespace litegdk::tests {
struct RecordedDrawCall {
    std::string label{};
};

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
        audioUpdateCount = 0;
        lastClearColor = {};
        textDraws.clear();
        spriteDraws.clear();
        drawCallSequence.clear();
        imageLoadRequests.clear();
        soundLoadRequests.clear();
        musicLoadRequests.clear();
        loadedImageIds.clear();
        unloadedImageIds.clear();
        loadedSoundIds.clear();
        unloadedSoundIds.clear();
        playedSoundIds.clear();
        stoppedSoundIds.clear();
        loadedMusicIds.clear();
        unloadedMusicIds.clear();
        playedMusicIds.clear();
        stoppedMusicIds.clear();
        pausedMusicIds.clear();
        resumedMusicIds.clear();
        soundVolumeChanges.clear();
        musicVolumeChanges.clear();
        configuredImages.clear();
        configuredSounds.clear();
        configuredMusic.clear();
        soundSlots.clear();
        musicSlots.clear();
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
        drawCallSequence.push_back(RecordedDrawCall{
            .label = "text:" + command.text,
        });
    }

    void drawSprite(const SpriteDrawCommand& command) override {
        spriteDraws.push_back(command);
        drawCallSequence.push_back(RecordedDrawCall{
            .label = "sprite:" + std::to_string(command.spriteId),
        });
    }

    void updateAudio() override {
        ++audioUpdateCount;
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

    bool loadSound(int soundId, std::string_view path) override {
        soundLoadRequests.emplace_back(std::string(path));

        if (!configuredSounds.contains(std::string(path))) {
            return false;
        }

        loadedSoundIds.push_back(soundId);
        soundSlots.insert(soundId);
        return true;
    }

    bool unloadSound(int soundId) override {
        if (!soundSlots.contains(soundId)) {
            return false;
        }

        unloadedSoundIds.push_back(soundId);
        soundSlots.erase(soundId);
        return true;
    }

    bool playSound(int soundId) override {
        if (!soundSlots.contains(soundId)) {
            return false;
        }

        playedSoundIds.push_back(soundId);
        return true;
    }

    bool stopSound(int soundId) override {
        if (!soundSlots.contains(soundId)) {
            return false;
        }

        stoppedSoundIds.push_back(soundId);
        return true;
    }

    bool setSoundVolume(int soundId, float volume) override {
        if (!soundSlots.contains(soundId)) {
            return false;
        }

        soundVolumeChanges.push_back(SoundVolumeChange{
            .soundId = soundId,
            .volume = volume,
        });
        return true;
    }

    bool loadMusic(int musicId, std::string_view path) override {
        musicLoadRequests.emplace_back(std::string(path));

        if (!configuredMusic.contains(std::string(path))) {
            return false;
        }

        loadedMusicIds.push_back(musicId);
        musicSlots.insert(musicId);
        return true;
    }

    bool unloadMusic(int musicId) override {
        if (!musicSlots.contains(musicId)) {
            return false;
        }

        unloadedMusicIds.push_back(musicId);
        musicSlots.erase(musicId);
        return true;
    }

    bool playMusic(int musicId) override {
        if (!musicSlots.contains(musicId)) {
            return false;
        }

        playedMusicIds.push_back(musicId);
        return true;
    }

    bool stopMusic(int musicId) override {
        if (!musicSlots.contains(musicId)) {
            return false;
        }

        stoppedMusicIds.push_back(musicId);
        return true;
    }

    bool pauseMusic(int musicId) override {
        if (!musicSlots.contains(musicId)) {
            return false;
        }

        pausedMusicIds.push_back(musicId);
        return true;
    }

    bool resumeMusic(int musicId) override {
        if (!musicSlots.contains(musicId)) {
            return false;
        }

        resumedMusicIds.push_back(musicId);
        return true;
    }

    bool setMusicVolume(int musicId, float volume) override {
        if (!musicSlots.contains(musicId)) {
            return false;
        }

        musicVolumeChanges.push_back(MusicVolumeChange{
            .musicId = musicId,
            .volume = volume,
        });
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
    int audioUpdateCount{0};
    bool shouldCloseFlag{false};
    Color lastClearColor{};
    Settings settings{};
    std::vector<TextDrawCommand> textDraws{};
    std::vector<SpriteDrawCommand> spriteDraws{};
    std::vector<RecordedDrawCall> drawCallSequence{};
    std::vector<std::string> imageLoadRequests{};
    std::vector<std::string> soundLoadRequests{};
    std::vector<std::string> musicLoadRequests{};
    std::vector<int> loadedImageIds{};
    std::vector<int> unloadedImageIds{};
    std::vector<int> loadedSoundIds{};
    std::vector<int> unloadedSoundIds{};
    std::vector<int> playedSoundIds{};
    std::vector<int> stoppedSoundIds{};
    std::vector<int> loadedMusicIds{};
    std::vector<int> unloadedMusicIds{};
    std::vector<int> playedMusicIds{};
    std::vector<int> stoppedMusicIds{};
    std::vector<int> pausedMusicIds{};
    std::vector<int> resumedMusicIds{};
    std::vector<SoundVolumeChange> soundVolumeChanges{};
    std::vector<MusicVolumeChange> musicVolumeChanges{};
    std::unordered_map<std::string, ImageLoadResult> configuredImages{};
    std::unordered_set<std::string> configuredSounds{};
    std::unordered_set<std::string> configuredMusic{};
    std::unordered_set<int> soundSlots{};
    std::unordered_set<int> musicSlots{};
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
