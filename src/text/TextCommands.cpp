#include "TextCommands.h"

#include "runtime/AppRuntime.h"
#include "runtime/ColorUtils.h"

namespace litegdk {
void drawText(int x, int y, std::string_view text) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    if (!app.isInitialized()) {
        app.initialize();
    }

    app.text().queueText(x, y, text, app.frameState());
}

void setTextInk(std::uint32_t foreground, std::uint32_t background) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    app.frameState().setTextColor(colorFromRgbValue(foreground));
    app.frameState().setTextBackgroundColor(colorFromRgbValue(background));
}
}  // namespace litegdk
