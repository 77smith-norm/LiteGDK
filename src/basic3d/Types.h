#pragma once

namespace litegdk {
struct Vector3 {
    float x{0.0f};
    float y{0.0f};
    float z{0.0f};
};

enum class ProjectionMode {
    perspective,
    orthographic,
};

enum class PrimitiveType {
    cube,
    sphere,
};
}  // namespace litegdk
