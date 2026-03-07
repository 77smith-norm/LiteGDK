#pragma once

#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

#include "LiteGDK/Compatibility.h"

namespace litegdk {
struct DiagnosticEntry {
    CompatibilityCode code{CompatibilityCode::failedPrecondition};
    CompatibilityTier tier{CompatibilityTier::X};
    std::string command{};
    std::string detail{};
};

class Diagnostics {
public:
    void clear();
    void warn(CompatibilityCode code,
              CompatibilityTier tier,
              std::string_view command,
              std::string_view detail);

    bool empty() const;
    std::size_t count() const;
    const std::vector<DiagnosticEntry>& warnings() const;

private:
    std::vector<DiagnosticEntry> warnings_{};
};
}  // namespace litegdk
