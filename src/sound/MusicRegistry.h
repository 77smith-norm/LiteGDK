#pragma once

#include <cstddef>
#include <string>

#include "runtime/Registry.h"

namespace litegdk {
struct MusicAsset {
    std::string sourcePath{};
    int volume{100};
    bool playing{false};
    bool paused{false};
    bool looping{false};
};

class MusicRegistry {
public:
    bool store(int musicId, MusicAsset asset);

    MusicAsset* find(int musicId);
    const MusicAsset* find(int musicId) const;

    bool exists(int musicId) const;
    bool remove(int musicId);
    std::size_t activeCount() const;
    void reset();

private:
    Registry<MusicAsset> tracks_{};
};
}  // namespace litegdk
