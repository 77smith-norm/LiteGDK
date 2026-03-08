#pragma once

#include <cstddef>
#include <string>

#include "runtime/Registry.h"

namespace litegdk {
struct SoundAsset {
    std::string sourcePath{};
    int volume{100};
    bool playing{false};
    bool paused{false};
};

class SoundRegistry {
public:
    bool store(int soundId, SoundAsset asset);

    SoundAsset* find(int soundId);
    const SoundAsset* find(int soundId) const;

    bool exists(int soundId) const;
    bool remove(int soundId);
    std::size_t activeCount() const;
    void reset();

private:
    Registry<SoundAsset> sounds_{};
};
}  // namespace litegdk
