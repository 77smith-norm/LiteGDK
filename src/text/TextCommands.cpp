#include "TextCommands.h"

#include "runtime/AppRuntime.h"

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
}  // namespace litegdk
