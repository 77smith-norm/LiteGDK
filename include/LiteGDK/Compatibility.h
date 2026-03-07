#pragma once

#include <string_view>

namespace litegdk {
enum class CompatibilityTier {
    A,
    B,
    C,
    X,
};

enum class CompatibilityCode {
    approximateBehavior,
    unsupportedCommand,
    invalidSlotUsage,
    failedPrecondition,
    initializationWarning,
};

constexpr std::string_view toString(CompatibilityTier tier) {
    switch (tier) {
    case CompatibilityTier::A:
        return "A";
    case CompatibilityTier::B:
        return "B";
    case CompatibilityTier::C:
        return "C";
    case CompatibilityTier::X:
        return "X";
    }

    return "X";
}

constexpr std::string_view toString(CompatibilityCode code) {
    switch (code) {
    case CompatibilityCode::approximateBehavior:
        return "approximateBehavior";
    case CompatibilityCode::unsupportedCommand:
        return "unsupportedCommand";
    case CompatibilityCode::invalidSlotUsage:
        return "invalidSlotUsage";
    case CompatibilityCode::failedPrecondition:
        return "failedPrecondition";
    case CompatibilityCode::initializationWarning:
        return "initializationWarning";
    }

    return "failedPrecondition";
}
}  // namespace litegdk
