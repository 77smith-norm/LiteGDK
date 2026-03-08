#include "TextService.h"

namespace {
constexpr int kDefaultTextSize = 20;
}

namespace litegdk {
void TextService::reset() {
    queuedCommands_.clear();
}

void TextService::queueText(int x, int y, std::string_view text, const FrameState& frameState) {
    queuedCommands_.push_back(TextDrawCommand{
        .x = x,
        .y = y,
        .size = kDefaultTextSize,
        .text = std::string(text),
        .color = frameState.textColor(),
    });
}

const std::vector<TextDrawCommand>& TextService::queuedCommands() const {
    return queuedCommands_;
}

void TextService::clearQueuedCommands() {
    queuedCommands_.clear();
}
}  // namespace litegdk
