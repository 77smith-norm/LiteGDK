#include "Basic3DCommands.h"

#include <string>
#include <string_view>

#include "runtime/AppRuntime.h"
#include "runtime/HandlePolicies.h"

namespace {
constexpr auto kBasic3DCommandTier = litegdk::CompatibilityTier::B;

void warnBasic3DFailure(litegdk::AppRuntime& app,
                        std::string_view command,
                        std::string_view detail,
                        litegdk::CompatibilityCode code = litegdk::CompatibilityCode::failedPrecondition) {
    app.diagnostics().warn(code, kBasic3DCommandTier, command, detail);
}

bool validateObjectHandle(litegdk::AppRuntime& app, int objectId, std::string_view command) {
    if (litegdk::isValidHandle(objectId)) {
        return true;
    }

    warnBasic3DFailure(app,
                       command,
                       "Object ID must be greater than zero.",
                       litegdk::CompatibilityCode::invalidSlotUsage);
    return false;
}
}  // namespace

namespace litegdk {
void makeObjectCube(int objectId, float size) {
    auto& app = runtime();
    if (app.isShutdownRequested() || !validateObjectHandle(app, objectId, "dbMakeObjectCube")) {
        return;
    }

    if (size <= 0.0f) {
        warnBasic3DFailure(app, "dbMakeObjectCube", "Cube size must be greater than zero.");
        return;
    }

    app.objects().store(objectId, Object3D{
        .primitiveType = PrimitiveType::cube,
        .dimensions = {size, size, size},
    });
}

void positionObject(int objectId, float x, float y, float z) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* object = app.objects().find(objectId);
    if (object == nullptr) {
        warnBasic3DFailure(app, "dbPositionObject", "Object ID not found: " + std::to_string(objectId));
        return;
    }

    object->position = {x, y, z};
}

void rotateObject(int objectId, float x, float y, float z) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    auto* object = app.objects().find(objectId);
    if (object == nullptr) {
        warnBasic3DFailure(app, "dbRotateObject", "Object ID not found: " + std::to_string(objectId));
        return;
    }

    object->rotation = {x, y, z};
}

void positionCamera(float x, float y, float z) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    app.camera().setPosition({x, y, z});
}

void pointCamera(float x, float y, float z) {
    auto& app = runtime();
    if (app.isShutdownRequested()) {
        return;
    }

    app.camera().setTarget({x, y, z});
}
}  // namespace litegdk
