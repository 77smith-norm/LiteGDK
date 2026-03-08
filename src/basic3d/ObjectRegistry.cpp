#include "ObjectRegistry.h"

namespace litegdk {
bool ObjectRegistry::store(int objectId, Object3D object) {
    return objects_.insertOrAssign(objectId, std::move(object));
}

Object3D* ObjectRegistry::find(int objectId) {
    return objects_.find(objectId);
}

const Object3D* ObjectRegistry::find(int objectId) const {
    return objects_.find(objectId);
}

bool ObjectRegistry::exists(int objectId) const {
    return objects_.contains(objectId);
}

bool ObjectRegistry::remove(int objectId) {
    return objects_.remove(objectId);
}

std::size_t ObjectRegistry::activeCount() const {
    return objects_.activeCount();
}

void ObjectRegistry::reset() {
    objects_ = {};
}
}  // namespace litegdk
