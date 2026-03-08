#include "SoundRegistry.h"

#include <utility>

namespace litegdk {
bool SoundRegistry::store(int soundId, SoundAsset asset) {
    return sounds_.insertOrAssign(soundId, std::move(asset));
}

SoundAsset* SoundRegistry::find(int soundId) {
    return sounds_.find(soundId);
}

const SoundAsset* SoundRegistry::find(int soundId) const {
    return sounds_.find(soundId);
}

bool SoundRegistry::exists(int soundId) const {
    return sounds_.contains(soundId);
}

bool SoundRegistry::remove(int soundId) {
    return sounds_.remove(soundId);
}

std::size_t SoundRegistry::activeCount() const {
    return sounds_.activeCount();
}

void SoundRegistry::reset() {
    sounds_ = {};
}
}  // namespace litegdk
