#include "CameraState.h"

namespace {
constexpr litegdk::Vector3 kDefaultCameraPosition{0.0f, 0.0f, -10.0f};
constexpr litegdk::Vector3 kDefaultCameraTarget{0.0f, 0.0f, 0.0f};
constexpr litegdk::Vector3 kDefaultCameraUp{0.0f, 1.0f, 0.0f};
constexpr litegdk::Vector3 kDefaultCameraRotation{0.0f, 0.0f, 0.0f};
constexpr float kDefaultFovDegrees = 45.0f;
constexpr auto kDefaultProjectionMode = litegdk::ProjectionMode::perspective;
}  // namespace

namespace litegdk {
CameraState::CameraState() {
    reset();
}

void CameraState::reset() {
    position_ = kDefaultCameraPosition;
    target_ = kDefaultCameraTarget;
    up_ = kDefaultCameraUp;
    rotation_ = kDefaultCameraRotation;
    fovDegrees_ = kDefaultFovDegrees;
    projectionMode_ = kDefaultProjectionMode;
}

const Vector3& CameraState::position() const {
    return position_;
}

void CameraState::setPosition(Vector3 position) {
    position_ = position;
}

const Vector3& CameraState::target() const {
    return target_;
}

void CameraState::setTarget(Vector3 target) {
    target_ = target;
}

const Vector3& CameraState::up() const {
    return up_;
}

void CameraState::setUp(Vector3 up) {
    up_ = up;
}

const Vector3& CameraState::rotation() const {
    return rotation_;
}

void CameraState::setRotation(Vector3 rotation) {
    rotation_ = rotation;
}

float CameraState::fovDegrees() const {
    return fovDegrees_;
}

void CameraState::setFovDegrees(float fovDegrees) {
    fovDegrees_ = fovDegrees;
}

ProjectionMode CameraState::projectionMode() const {
    return projectionMode_;
}

void CameraState::setProjectionMode(ProjectionMode projectionMode) {
    projectionMode_ = projectionMode;
}
}  // namespace litegdk
