#include "Diagnostics.h"

namespace litegdk {
void Diagnostics::clear() {
    warnings_.clear();
}

void Diagnostics::warn(CompatibilityCode code,
                       CompatibilityTier tier,
                       std::string_view command,
                       std::string_view detail) {
    warnings_.push_back(DiagnosticEntry{
        .code = code,
        .tier = tier,
        .command = std::string(command),
        .detail = std::string(detail),
    });
}

bool Diagnostics::empty() const {
    return warnings_.empty();
}

std::size_t Diagnostics::count() const {
    return warnings_.size();
}

const std::vector<DiagnosticEntry>& Diagnostics::warnings() const {
    return warnings_;
}
}  // namespace litegdk
