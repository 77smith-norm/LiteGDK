#pragma once

#include <cstddef>

namespace litegdk {
constexpr bool isValidHandle(int handle) {
    return handle > 0;
}

constexpr std::size_t handleToIndex(int handle) {
    return static_cast<std::size_t>(handle - 1);
}
}  // namespace litegdk
