#include "ImageCommands.h"

#include <filesystem>
#include <string>

#include "runtime/AppRuntime.h"
#include "runtime/HandlePolicies.h"

namespace {
constexpr auto kImageCommandTier = litegdk::CompatibilityTier::B;

void warnImageLoadFailure(litegdk::AppRuntime& app,
                          std::string_view detail,
                          litegdk::CompatibilityCode code = litegdk::CompatibilityCode::failedPrecondition) {
    app.diagnostics().warn(code, kImageCommandTier, "dbLoadImage", detail);
}
}  // namespace

namespace litegdk {
void loadImage(std::string_view filename, int imageId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    if (!isValidHandle(imageId)) {
        warnImageLoadFailure(app, "Image ID must be greater than zero.", CompatibilityCode::invalidSlotUsage);
        return;
    }

    const auto path = std::filesystem::path(filename);
    if (path.empty() || !std::filesystem::exists(path)) {
        warnImageLoadFailure(app, "Image file not found: " + path.string());
        return;
    }

    if (!app.isInitialized()) {
        app.initialize();
    }

    const auto result = app.backend().loadImage(imageId, path.string());
    if (!result.has_value()) {
        warnImageLoadFailure(app, "Backend could not load image: " + path.string());
        return;
    }

    app.images().store(imageId, ImageAsset{
        .sourcePath = path.string(),
        .width = result->width,
        .height = result->height,
    });
}

bool imageExists(int imageId) {
    return runtime().images().exists(imageId);
}

int imageWidth(int imageId) {
    const auto* image = runtime().images().find(imageId);
    return image == nullptr ? 0 : image->width;
}

int imageHeight(int imageId) {
    const auto* image = runtime().images().find(imageId);
    return image == nullptr ? 0 : image->height;
}
}  // namespace litegdk
