#pragma once

#include <cstdint>

#include "FrameState.h"

namespace litegdk {
constexpr Color colorFromRgbValue(std::uint32_t value) {
    return Color{
        static_cast<std::uint8_t>((value >> 16U) & 0xFFU),
        static_cast<std::uint8_t>((value >> 8U) & 0xFFU),
        static_cast<std::uint8_t>(value & 0xFFU),
        0xFFU,
    };
}
}  // namespace litegdk
