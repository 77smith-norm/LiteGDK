#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <filesystem>

#include "DarkGDK.h"
#include "helpers/RuntimeTestContext.h"

namespace {
std::string fixtureAudioPath() {
    return (std::filesystem::current_path().parent_path() / "tests/fixtures/assets/test_sound.wav").string();
}

std::string missingAudioPath() {
    return (std::filesystem::current_path().parent_path() / "tests/fixtures/assets/missing_sound.wav").string();
}
}  // namespace

TEST_CASE("sound commands load, play, stop, delete, and update volume", "[sound]") {
    litegdk::tests::RuntimeTestContext context;
    const auto fixturePath = fixtureAudioPath();

    context.backend().configuredSounds.insert(fixturePath);

    dbLoadSound(fixturePath.c_str(), 5);

    const auto* loaded = context.app().sounds().find(5);
    REQUIRE(loaded != nullptr);
    REQUIRE(loaded->sourcePath == fixturePath);
    REQUIRE(loaded->volume == 100);
    REQUIRE_FALSE(loaded->playing);
    REQUIRE_FALSE(loaded->paused);

    dbPlaySound(5);
    REQUIRE(context.backend().playedSoundIds == std::vector<int>{5});
    REQUIRE(context.app().sounds().find(5)->playing);
    REQUIRE_FALSE(context.app().sounds().find(5)->paused);

    dbSetSoundVolume(5, 35);
    REQUIRE(context.app().sounds().find(5)->volume == 35);
    REQUIRE(context.backend().soundVolumeChanges.size() == 1);
    REQUIRE(context.backend().soundVolumeChanges.front().soundId == 5);
    REQUIRE(context.backend().soundVolumeChanges.front().volume == Catch::Approx(0.35f));

    dbStopSound(5);
    REQUIRE(context.backend().stoppedSoundIds == std::vector<int>{5});
    REQUIRE_FALSE(context.app().sounds().find(5)->playing);
    REQUIRE_FALSE(context.app().sounds().find(5)->paused);

    dbDeleteSound(5);
    REQUIRE(context.app().sounds().find(5) == nullptr);
    REQUIRE(context.backend().unloadedSoundIds == std::vector<int>{5});
}

TEST_CASE("music commands load, play, pause, resume, stop, delete, and update volume", "[sound]") {
    litegdk::tests::RuntimeTestContext context;
    const auto fixturePath = fixtureAudioPath();

    context.backend().configuredMusic.insert(fixturePath);

    dbLoadMusic(fixturePath.c_str(), 7);

    const auto* loaded = context.app().music().find(7);
    REQUIRE(loaded != nullptr);
    REQUIRE(loaded->sourcePath == fixturePath);
    REQUIRE(loaded->volume == 100);
    REQUIRE_FALSE(loaded->playing);
    REQUIRE_FALSE(loaded->paused);

    dbPlayMusic(7);
    REQUIRE(context.backend().playedMusicIds == std::vector<int>{7});
    REQUIRE(context.app().music().find(7)->playing);
    REQUIRE_FALSE(context.app().music().find(7)->paused);

    dbPauseMusic(7);
    REQUIRE(context.backend().pausedMusicIds == std::vector<int>{7});
    REQUIRE_FALSE(context.app().music().find(7)->playing);
    REQUIRE(context.app().music().find(7)->paused);

    dbResumeMusic(7);
    REQUIRE(context.backend().resumedMusicIds == std::vector<int>{7});
    REQUIRE(context.app().music().find(7)->playing);
    REQUIRE_FALSE(context.app().music().find(7)->paused);

    dbSetMusicVolume(7, 65);
    REQUIRE(context.app().music().find(7)->volume == 65);
    REQUIRE(context.backend().musicVolumeChanges.size() == 1);
    REQUIRE(context.backend().musicVolumeChanges.front().musicId == 7);
    REQUIRE(context.backend().musicVolumeChanges.front().volume == Catch::Approx(0.65f));

    dbStopMusic(7);
    REQUIRE(context.backend().stoppedMusicIds == std::vector<int>{7});
    REQUIRE_FALSE(context.app().music().find(7)->playing);
    REQUIRE_FALSE(context.app().music().find(7)->paused);

    dbDeleteMusic(7);
    REQUIRE(context.app().music().find(7) == nullptr);
    REQUIRE(context.backend().unloadedMusicIds == std::vector<int>{7});
}

TEST_CASE("audio commands record diagnostics for invalid handles and missing assets", "[sound]") {
    litegdk::tests::RuntimeTestContext context;
    const auto fixturePath = fixtureAudioPath();

    dbLoadSound(fixturePath.c_str(), 0);
    dbPlaySound(99);
    dbLoadMusic(missingAudioPath().c_str(), 4);

    REQUIRE(context.app().diagnostics().count() == 3);

    const auto& warnings = context.app().diagnostics().warnings();
    REQUIRE(warnings[0].command == "dbLoadSound");
    REQUIRE(warnings[0].code == litegdk::CompatibilityCode::invalidSlotUsage);
    REQUIRE(warnings[1].command == "dbPlaySound");
    REQUIRE(warnings[1].code == litegdk::CompatibilityCode::failedPrecondition);
    REQUIRE(warnings[2].command == "dbLoadMusic");
    REQUIRE(warnings[2].detail.find("Music file not found:") != std::string::npos);
}
