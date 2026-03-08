#include <catch2/catch_test_macros.hpp>

#include "sound/MusicRegistry.h"
#include "sound/SoundRegistry.h"

TEST_CASE("SoundRegistry stores sound assets by slot with playback defaults", "[sound]") {
    litegdk::SoundRegistry registry;

    REQUIRE(registry.store(2, {
        .sourcePath = "tests/fixtures/assets/test_sound.wav",
    }));
    REQUIRE(registry.exists(2));
    REQUIRE(registry.activeCount() == 1);

    const auto* sound = registry.find(2);
    REQUIRE(sound != nullptr);
    REQUIRE(sound->sourcePath == "tests/fixtures/assets/test_sound.wav");
    REQUIRE(sound->volume == 100);
    REQUIRE_FALSE(sound->playing);
    REQUIRE_FALSE(sound->paused);
}

TEST_CASE("SoundRegistry replaces and unloads sound slots deterministically", "[sound]") {
    litegdk::SoundRegistry registry;

    REQUIRE(registry.store(4, {
        .sourcePath = "old.wav",
        .volume = 30,
        .playing = true,
    }));
    REQUIRE(registry.store(4, {
        .sourcePath = "new.wav",
        .volume = 75,
    }));
    REQUIRE(registry.activeCount() == 1);

    const auto* sound = registry.find(4);
    REQUIRE(sound != nullptr);
    REQUIRE(sound->sourcePath == "new.wav");
    REQUIRE(sound->volume == 75);
    REQUIRE_FALSE(sound->playing);
    REQUIRE_FALSE(sound->paused);

    REQUIRE(registry.remove(4));
    REQUIRE_FALSE(registry.exists(4));
    REQUIRE(registry.find(4) == nullptr);
    REQUIRE(registry.activeCount() == 0);
    REQUIRE_FALSE(registry.remove(4));
    REQUIRE_FALSE(registry.store(0, {
        .sourcePath = "invalid.wav",
    }));
}

TEST_CASE("MusicRegistry stores music assets by slot with playback defaults", "[sound]") {
    litegdk::MusicRegistry registry;

    REQUIRE(registry.store(3, {
        .sourcePath = "tests/fixtures/assets/test_music.ogg",
    }));
    REQUIRE(registry.exists(3));
    REQUIRE(registry.activeCount() == 1);

    const auto* music = registry.find(3);
    REQUIRE(music != nullptr);
    REQUIRE(music->sourcePath == "tests/fixtures/assets/test_music.ogg");
    REQUIRE(music->volume == 100);
    REQUIRE_FALSE(music->playing);
    REQUIRE_FALSE(music->paused);
    REQUIRE_FALSE(music->looping);
}

TEST_CASE("MusicRegistry replaces and unloads music slots deterministically", "[sound]") {
    litegdk::MusicRegistry registry;

    REQUIRE(registry.store(6, {
        .sourcePath = "old.ogg",
        .volume = 20,
        .playing = true,
        .paused = true,
        .looping = true,
    }));
    REQUIRE(registry.store(6, {
        .sourcePath = "new.ogg",
        .volume = 55,
    }));
    REQUIRE(registry.activeCount() == 1);

    const auto* music = registry.find(6);
    REQUIRE(music != nullptr);
    REQUIRE(music->sourcePath == "new.ogg");
    REQUIRE(music->volume == 55);
    REQUIRE_FALSE(music->playing);
    REQUIRE_FALSE(music->paused);
    REQUIRE_FALSE(music->looping);

    REQUIRE(registry.remove(6));
    REQUIRE_FALSE(registry.exists(6));
    REQUIRE(registry.find(6) == nullptr);
    REQUIRE(registry.activeCount() == 0);
    REQUIRE_FALSE(registry.remove(6));
    REQUIRE_FALSE(registry.store(-1, {
        .sourcePath = "invalid.ogg",
    }));
}
