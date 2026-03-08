#pragma once

#include <cstddef>
#include <utility>

#include "Types.h"
#include "runtime/Registry.h"

namespace litegdk {
struct Object3D {
    PrimitiveType primitiveType{PrimitiveType::cube};
    Vector3 dimensions{1.0f, 1.0f, 1.0f};
    float radius{0.5f};
    Vector3 position{0.0f, 0.0f, 0.0f};
    Vector3 rotation{0.0f, 0.0f, 0.0f};
    Vector3 scale{1.0f, 1.0f, 1.0f};
    bool visible{true};
};

class ObjectRegistry {
public:
    bool store(int objectId, Object3D object);

    Object3D* find(int objectId);
    const Object3D* find(int objectId) const;

    bool exists(int objectId) const;
    bool remove(int objectId);
    std::size_t activeCount() const;
    void reset();

    template <typename Fn>
    void forEach(Fn&& fn) const {
        objects_.forEach(std::forward<Fn>(fn));
    }

private:
    Registry<Object3D> objects_{};
};
}  // namespace litegdk
