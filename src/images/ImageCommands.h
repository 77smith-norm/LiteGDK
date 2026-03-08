#pragma once

#include <string_view>

namespace litegdk {
void loadImage(std::string_view filename, int imageId);
bool imageExists(int imageId);
int imageWidth(int imageId);
int imageHeight(int imageId);
}  // namespace litegdk
