#include "MusicRegistry.h"

#include <utility>

namespace litegdk {
bool MusicRegistry::store(int musicId, MusicAsset asset) {
    return tracks_.insertOrAssign(musicId, std::move(asset));
}

MusicAsset* MusicRegistry::find(int musicId) {
    return tracks_.find(musicId);
}

const MusicAsset* MusicRegistry::find(int musicId) const {
    return tracks_.find(musicId);
}

bool MusicRegistry::exists(int musicId) const {
    return tracks_.contains(musicId);
}

bool MusicRegistry::remove(int musicId) {
    return tracks_.remove(musicId);
}

std::size_t MusicRegistry::activeCount() const {
    return tracks_.activeCount();
}

void MusicRegistry::reset() {
    tracks_ = {};
}
}  // namespace litegdk
