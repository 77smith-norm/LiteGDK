#pragma once

#include "Types.h"

namespace litegdk {
enum class ProjectionMode {
    perspective,
    orthographic,
};

class CameraState {
public:
    CameraState();

    void reset();

    const Vector3& position() const;
    void setPosition(Vector3 position);

    const Vector3& target() const;
    void setTarget(Vector3 target);

    const Vector3& up() const;
    void setUp(Vector3 up);

    const Vector3& rotation() const;
    void setRotation(Vector3 rotation);

    float fovDegrees() const;
    void setFovDegrees(float fovDegrees);

    ProjectionMode projectionMode() const;
    void setProjectionMode(ProjectionMode projectionMode);

private:
    Vector3 position_{};
    Vector3 target_{};
    Vector3 up_{};
    Vector3 rotation_{};
    float fovDegrees_{45.0f};
    ProjectionMode projectionMode_{ProjectionMode::perspective};
};
}  // namespace litegdk
