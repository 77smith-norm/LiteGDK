#include "AppRuntime.h"

namespace litegdk {
namespace {
constexpr int kDefaultDisplayWidth = 800;
constexpr int kDefaultDisplayHeight = 600;
constexpr int kDefaultDisplayDepth = 32;
}  // namespace

AppRuntime::AppRuntime()
    : backend_(makeDefaultBackend()) {
    reset();
}

void AppRuntime::initialize() {
    applyBackendSettings();
    initialized_ = true;
    running_ = true;
    shutdownRequested_ = false;
}

void AppRuntime::shutdown() {
    if (backend_) {
        backend_->shutdown();
    }

    running_ = false;
    initialized_ = false;
    shutdownRequested_ = true;
}

void AppRuntime::reset() {
    if (backend_) {
        backend_->reset();
    }

    initialized_ = false;
    running_ = false;
    shutdownRequested_ = false;
    displayWidth_ = kDefaultDisplayWidth;
    displayHeight_ = kDefaultDisplayHeight;
    displayDepth_ = kDefaultDisplayDepth;
    diagnostics_.clear();
    frameState_.reset();
    camera_.reset();
    objects_.reset();
    images_.reset();
    input_.reset();
    sounds_.reset();
    music_.reset();
    sprites_.reset();
    text_.reset();
}

bool AppRuntime::isInitialized() const {
    return initialized_;
}

bool AppRuntime::isRunning() const {
    return running_;
}

bool AppRuntime::isShutdownRequested() const {
    return shutdownRequested_;
}

int AppRuntime::displayWidth() const {
    return displayWidth_;
}

int AppRuntime::displayHeight() const {
    return displayHeight_;
}

int AppRuntime::displayDepth() const {
    return displayDepth_;
}

void AppRuntime::applyBackendSettings() {
    if (backend_) {
        backend_->applySettings(displayWidth_, displayHeight_, displayDepth_, frameState_.syncRate());
    }
}

void AppRuntime::setDisplayMode(int width, int height, int depth) {
    displayWidth_ = width;
    displayHeight_ = height;
    displayDepth_ = depth;

    if (initialized_) {
        applyBackendSettings();
    }
}

Diagnostics& AppRuntime::diagnostics() {
    return diagnostics_;
}

const Diagnostics& AppRuntime::diagnostics() const {
    return diagnostics_;
}

Backend& AppRuntime::backend() {
    return *backend_;
}

const Backend& AppRuntime::backend() const {
    return *backend_;
}

void AppRuntime::setBackend(std::unique_ptr<Backend> backend) {
    if (backend_) {
        backend_->shutdown();
    }

    backend_ = std::move(backend);
    if (!backend_) {
        backend_ = makeDefaultBackend();
    }

    if (initialized_) {
        applyBackendSettings();
    }
}

FrameState& AppRuntime::frameState() {
    return frameState_;
}

const FrameState& AppRuntime::frameState() const {
    return frameState_;
}

ImageRegistry& AppRuntime::images() {
    return images_;
}

const ImageRegistry& AppRuntime::images() const {
    return images_;
}

InputSnapshot& AppRuntime::input() {
    return input_;
}

const InputSnapshot& AppRuntime::input() const {
    return input_;
}

CameraState& AppRuntime::camera() {
    return camera_;
}

const CameraState& AppRuntime::camera() const {
    return camera_;
}

ObjectRegistry& AppRuntime::objects() {
    return objects_;
}

const ObjectRegistry& AppRuntime::objects() const {
    return objects_;
}

SoundRegistry& AppRuntime::sounds() {
    return sounds_;
}

const SoundRegistry& AppRuntime::sounds() const {
    return sounds_;
}

MusicRegistry& AppRuntime::music() {
    return music_;
}

const MusicRegistry& AppRuntime::music() const {
    return music_;
}

SpriteRegistry& AppRuntime::sprites() {
    return sprites_;
}

const SpriteRegistry& AppRuntime::sprites() const {
    return sprites_;
}

TextService& AppRuntime::text() {
    return text_;
}

const TextService& AppRuntime::text() const {
    return text_;
}

void AppRuntime::renderFrame() {
    if (!initialized_ || !backend_) {
        return;
    }

    backend_->beginFrame(frameState_.clearColor());

    if (objects_.activeCount() > 0) {
        backend_->begin3D(Camera3DDrawCommand{
            .position = camera_.position(),
            .target = camera_.target(),
            .up = camera_.up(),
            .fovDegrees = camera_.fovDegrees(),
            .projectionMode = camera_.projectionMode(),
        });

        objects_.forEach([this](int objectId, const Object3D& object) {
            if (!object.visible) {
                return;
            }

            backend_->drawObject3D(Object3DDrawCommand{
                .objectId = objectId,
                .primitiveType = object.primitiveType,
                .dimensions = object.dimensions,
                .radius = object.radius,
                .position = object.position,
                .rotation = object.rotation,
                .scale = object.scale,
            });
        });

        backend_->end3D();
    }

    sprites_.forEach([this](int spriteId, const SpriteState& sprite) {
        if (!sprite.visible || !images_.exists(sprite.imageId)) {
            return;
        }

        backend_->drawSprite(SpriteDrawCommand{
            .spriteId = spriteId,
            .imageId = sprite.imageId,
            .x = sprite.x,
            .y = sprite.y,
            .rotation = sprite.rotationDegrees,
            .scale = sprite.scale,
            .tint = sprite.tint,
        });
    });

    for (const auto& command : text_.queuedCommands()) {
        backend_->drawText(command);
    }

    backend_->updateAudio();
    backend_->endFrame();
    text_.clearQueuedCommands();
}

AppRuntime& runtime() {
    static AppRuntime instance;
    return instance;
}
}  // namespace litegdk
