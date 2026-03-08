#include "SpriteCommands.h"

#include <string>

#include "runtime/AppRuntime.h"
#include "runtime/HandlePolicies.h"

namespace {
constexpr auto kSpriteCommandTier = litegdk::CompatibilityTier::B;

void warnSpriteFailure(litegdk::AppRuntime& app,
                       std::string_view detail,
                       litegdk::CompatibilityCode code = litegdk::CompatibilityCode::failedPrecondition) {
    app.diagnostics().warn(code, kSpriteCommandTier, "dbSprite", detail);
}
}  // namespace

namespace litegdk {
void createSprite(int spriteId, int x, int y, int imageId) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    if (!isValidHandle(spriteId)) {
        warnSpriteFailure(app, "Sprite ID must be greater than zero.", CompatibilityCode::invalidSlotUsage);
        return;
    }

    if (!app.images().exists(imageId)) {
        warnSpriteFailure(app, "Image ID not loaded: " + std::to_string(imageId));
        return;
    }

    app.sprites().store(spriteId, SpriteState{
        .imageId = imageId,
        .x = static_cast<float>(x),
        .y = static_cast<float>(y),
    });
}

void deleteSprite(int spriteId) {
    runtime().sprites().remove(spriteId);
}

void hideSprite(int spriteId) {
    if (auto* sprite = runtime().sprites().find(spriteId)) {
        sprite->visible = false;
    }
}

void showSprite(int spriteId) {
    if (auto* sprite = runtime().sprites().find(spriteId)) {
        sprite->visible = true;
    }
}

void setSpriteX(int spriteId, int x) {
    if (auto* sprite = runtime().sprites().find(spriteId)) {
        sprite->x = static_cast<float>(x);
    }
}

void setSpriteY(int spriteId, int y) {
    if (auto* sprite = runtime().sprites().find(spriteId)) {
        sprite->y = static_cast<float>(y);
    }
}

bool spriteExists(int spriteId) {
    return runtime().sprites().exists(spriteId);
}
}  // namespace litegdk
