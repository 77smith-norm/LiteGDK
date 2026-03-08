#include <filesystem>
#include <iostream>

#include "DarkGDK.h"
#include "helpers/TestBackend.h"
#include "runtime/AppRuntime.h"

int main() {
    auto& app = litegdk::runtime();
    auto* backend = litegdk::tests::installTestBackend(app);
    const auto fixturePath = (std::filesystem::current_path().parent_path() / "tests/fixtures/assets/test_sound.wav").string();

    backend->configuredSounds.insert(fixturePath);
    backend->configuredMusic.insert(fixturePath);

    dbLoadSound(fixturePath.c_str(), 1);
    dbPlaySound(1);
    dbSetSoundVolume(1, 35);

    dbLoadMusic(fixturePath.c_str(), 2);
    dbPlayMusic(2);
    dbPauseMusic(2);
    dbResumeMusic(2);

    std::cout << "Sound plays=" << backend->playedSoundIds.size()
              << " volume=" << litegdk::runtime().sounds().find(1)->volume
              << " Music plays=" << backend->playedMusicIds.size()
              << " paused=" << backend->pausedMusicIds.size()
              << " resumed=" << backend->resumedMusicIds.size() << "\n";
    return 0;
}
