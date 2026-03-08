#include "ImageRegistry.h"

namespace litegdk {
bool ImageRegistry::store(int imageId, ImageAsset asset) {
    return images_.insertOrAssign(imageId, std::move(asset));
}

ImageAsset* ImageRegistry::find(int imageId) {
    return images_.find(imageId);
}

const ImageAsset* ImageRegistry::find(int imageId) const {
    return images_.find(imageId);
}

bool ImageRegistry::exists(int imageId) const {
    return images_.contains(imageId);
}

bool ImageRegistry::remove(int imageId) {
    return images_.remove(imageId);
}

std::size_t ImageRegistry::activeCount() const {
    return images_.activeCount();
}

void ImageRegistry::reset() {
    images_ = {};
}
}  // namespace litegdk
