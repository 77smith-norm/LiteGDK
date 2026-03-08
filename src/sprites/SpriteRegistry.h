#pragma once

#include <cstddef>

#include "runtime/FrameState.h"
#include "runtime/Registry.h"

namespace litegdk {
struct SpriteState {
    int imageId{0};
    float x{0.0f};
    float y{0.0f};
    bool visible{true};
    float rotationDegrees{0.0f};
    float scale{1.0f};
    Color tint{255, 255, 255, 255};
};

class SpriteRegistry {
public:
    bool store(int spriteId, SpriteState sprite);

    SpriteState* find(int spriteId);
    const SpriteState* find(int spriteId) const;

    bool exists(int spriteId) const;
    bool remove(int spriteId);
    std::size_t activeCount() const;
    void reset();

private:
    Registry<SpriteState> sprites_{};
};
}  // namespace litegdk
