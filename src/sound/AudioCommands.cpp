#include "AudioCommands.h"

#include <algorithm>
#include <filesystem>
#include <string>
#include <string_view>

#ifdef __EMSCRIPTEN__
#include <emscripten/emscripten.h>
#endif

#include "runtime/AppRuntime.h"
#include "runtime/HandlePolicies.h"

namespace {
constexpr auto kAudioCommandTier = litegdk::CompatibilityTier::B;

#ifdef __EMSCRIPTEN__
EM_JS(int, litegdkAudioInteractionReady, (), {
    return (typeof window !== "undefined" && window.__litegdkAudioReady) ? 1 : 0;
});
#endif

int clampVolume(int volume) {
    return std::clamp(volume, 0, 100);
}

float normalizeVolume(int volume) {
    return static_cast<float>(clampVolume(volume)) / 100.0f;
}

void ensureInitialized(litegdk::AppRuntime& app) {
    if (!app.isInitialized() && !app.isShutdownRequested()) {
        app.initialize();
    }
}

void warnAudioFailure(litegdk::AppRuntime& app,
                      std::string_view command,
                      std::string_view detail,
                      litegdk::CompatibilityCode code = litegdk::CompatibilityCode::failedPrecondition) {
    app.diagnostics().warn(code, kAudioCommandTier, command, detail);
}

bool validateHandle(litegdk::AppRuntime& app, int handle, std::string_view command, std::string_view label) {
    if (litegdk::isValidHandle(handle)) {
        return true;
    }

    warnAudioFailure(app,
                     command,
                     std::string(label) + " ID must be greater than zero.",
                     litegdk::CompatibilityCode::invalidSlotUsage);
    return false;
}
}  // namespace

namespace litegdk {
bool audioInitializationAllowed() {
#ifdef __EMSCRIPTEN__
    return litegdkAudioInteractionReady() != 0;
#else
    return true;
#endif
}

void loadSound(std::string_view filename, int soundId) {
    auto& app = runtime();
    if (app.isShutdownRequested() || !validateHandle(app, soundId, "dbLoadSound", "Sound")) {
        return;
    }

    const auto path = std::filesystem::path(filename);
    if (path.empty() || !std::filesystem::exists(path)) {
        warnAudioFailure(app, "dbLoadSound", "Sound file not found: " + path.string());
        return;
    }

    ensureInitialized(app);
    if (!app.backend().loadSound(soundId, path.string())) {
        warnAudioFailure(app, "dbLoadSound", "Backend could not load sound: " + path.string());
        return;
    }

    app.sounds().store(soundId, SoundAsset{
        .sourcePath = path.string(),
    });
}

void deleteSound(int soundId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    if (app.sounds().remove(soundId)) {
        app.backend().unloadSound(soundId);
    }
}

void playSound(int soundId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* sound = app.sounds().find(soundId);
    if (sound == nullptr) {
        warnAudioFailure(app, "dbPlaySound", "Sound ID not loaded: " + std::to_string(soundId));
        return;
    }

    if (!app.backend().playSound(soundId)) {
        warnAudioFailure(app, "dbPlaySound", "Backend could not play sound: " + std::to_string(soundId));
        return;
    }

    sound->playing = true;
    sound->paused = false;
}

void stopSound(int soundId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* sound = app.sounds().find(soundId);
    if (sound == nullptr) {
        warnAudioFailure(app, "dbStopSound", "Sound ID not loaded: " + std::to_string(soundId));
        return;
    }

    if (!app.backend().stopSound(soundId)) {
        warnAudioFailure(app, "dbStopSound", "Backend could not stop sound: " + std::to_string(soundId));
        return;
    }

    sound->playing = false;
    sound->paused = false;
}

void setSoundVolume(int soundId, int volume) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* sound = app.sounds().find(soundId);
    if (sound == nullptr) {
        warnAudioFailure(app, "dbSetSoundVolume", "Sound ID not loaded: " + std::to_string(soundId));
        return;
    }

    const auto clampedVolume = clampVolume(volume);
    if (!app.backend().setSoundVolume(soundId, normalizeVolume(clampedVolume))) {
        warnAudioFailure(app, "dbSetSoundVolume", "Backend could not set sound volume: " + std::to_string(soundId));
        return;
    }

    sound->volume = clampedVolume;
}

void loadMusic(std::string_view filename, int musicId) {
    auto& app = runtime();
    if (app.isShutdownRequested() || !validateHandle(app, musicId, "dbLoadMusic", "Music")) {
        return;
    }

    const auto path = std::filesystem::path(filename);
    if (path.empty() || !std::filesystem::exists(path)) {
        warnAudioFailure(app, "dbLoadMusic", "Music file not found: " + path.string());
        return;
    }

    ensureInitialized(app);
    if (!app.backend().loadMusic(musicId, path.string())) {
        warnAudioFailure(app, "dbLoadMusic", "Backend could not load music: " + path.string());
        return;
    }

    app.music().store(musicId, MusicAsset{
        .sourcePath = path.string(),
    });
}

void deleteMusic(int musicId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    if (app.music().remove(musicId)) {
        app.backend().unloadMusic(musicId);
    }
}

void playMusic(int musicId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* music = app.music().find(musicId);
    if (music == nullptr) {
        warnAudioFailure(app, "dbPlayMusic", "Music ID not loaded: " + std::to_string(musicId));
        return;
    }

    if (!app.backend().playMusic(musicId)) {
        warnAudioFailure(app, "dbPlayMusic", "Backend could not play music: " + std::to_string(musicId));
        return;
    }

    music->playing = true;
    music->paused = false;
}

void stopMusic(int musicId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* music = app.music().find(musicId);
    if (music == nullptr) {
        warnAudioFailure(app, "dbStopMusic", "Music ID not loaded: " + std::to_string(musicId));
        return;
    }

    if (!app.backend().stopMusic(musicId)) {
        warnAudioFailure(app, "dbStopMusic", "Backend could not stop music: " + std::to_string(musicId));
        return;
    }

    music->playing = false;
    music->paused = false;
}

void pauseMusic(int musicId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* music = app.music().find(musicId);
    if (music == nullptr) {
        warnAudioFailure(app, "dbPauseMusic", "Music ID not loaded: " + std::to_string(musicId));
        return;
    }

    if (!app.backend().pauseMusic(musicId)) {
        warnAudioFailure(app, "dbPauseMusic", "Backend could not pause music: " + std::to_string(musicId));
        return;
    }

    music->playing = false;
    music->paused = true;
}

void resumeMusic(int musicId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* music = app.music().find(musicId);
    if (music == nullptr) {
        warnAudioFailure(app, "dbResumeMusic", "Music ID not loaded: " + std::to_string(musicId));
        return;
    }

    if (!app.backend().resumeMusic(musicId)) {
        warnAudioFailure(app, "dbResumeMusic", "Backend could not resume music: " + std::to_string(musicId));
        return;
    }

    music->playing = true;
    music->paused = false;
}

void setMusicVolume(int musicId, int volume) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* music = app.music().find(musicId);
    if (music == nullptr) {
        warnAudioFailure(app, "dbSetMusicVolume", "Music ID not loaded: " + std::to_string(musicId));
        return;
    }

    const auto clampedVolume = clampVolume(volume);
    if (!app.backend().setMusicVolume(musicId, normalizeVolume(clampedVolume))) {
        warnAudioFailure(app, "dbSetMusicVolume", "Backend could not set music volume: " + std::to_string(musicId));
        return;
    }

    music->volume = clampedVolume;
}
}  // namespace litegdk
