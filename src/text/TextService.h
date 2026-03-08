#pragma once

#include <string_view>
#include <vector>

#include "runtime/Backend.h"
#include "runtime/FrameState.h"

namespace litegdk {
class TextService {
public:
    void reset();
    void queueText(int x, int y, std::string_view text, const FrameState& frameState);

    const std::vector<TextDrawCommand>& queuedCommands() const;
    void clearQueuedCommands();

private:
    std::vector<TextDrawCommand> queuedCommands_{};
};
}  // namespace litegdk
