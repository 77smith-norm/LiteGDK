#include "SpriteRegistry.h"

namespace litegdk {
bool SpriteRegistry::store(int spriteId, SpriteState sprite) {
    return sprites_.insertOrAssign(spriteId, std::move(sprite));
}

SpriteState* SpriteRegistry::find(int spriteId) {
    return sprites_.find(spriteId);
}

const SpriteState* SpriteRegistry::find(int spriteId) const {
    return sprites_.find(spriteId);
}

bool SpriteRegistry::exists(int spriteId) const {
    return sprites_.contains(spriteId);
}

bool SpriteRegistry::remove(int spriteId) {
    return sprites_.remove(spriteId);
}

std::size_t SpriteRegistry::activeCount() const {
    return sprites_.activeCount();
}

void SpriteRegistry::reset() {
    sprites_ = {};
}
}  // namespace litegdk
