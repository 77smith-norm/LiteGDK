#pragma once

#include <cstdint>
#include <string_view>

namespace litegdk {
void drawText(int x, int y, std::string_view text);
void setTextInk(std::uint32_t foreground, std::uint32_t background);
}  // namespace litegdk
