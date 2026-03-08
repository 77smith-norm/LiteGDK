#pragma once

#include <cstddef>
#include <string>

#include "runtime/Registry.h"

namespace litegdk {
struct ImageAsset {
    std::string sourcePath{};
    int width{0};
    int height{0};
};

class ImageRegistry {
public:
    bool store(int imageId, ImageAsset asset);

    ImageAsset* find(int imageId);
    const ImageAsset* find(int imageId) const;

    bool exists(int imageId) const;
    bool remove(int imageId);
    std::size_t activeCount() const;
    void reset();

private:
    Registry<ImageAsset> images_{};
};
}  // namespace litegdk
