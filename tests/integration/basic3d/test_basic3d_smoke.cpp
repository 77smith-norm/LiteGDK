#include <iostream>

#include "DarkGDK.h"
#include "helpers/TestBackend.h"
#include "runtime/AppRuntime.h"

int main() {
    auto& app = litegdk::runtime();
    auto* backend = litegdk::tests::installTestBackend(app);

    dbMakeObjectCube(7, 12.0f);
    dbPositionObject(7, 3.0f, 4.0f, 5.0f);
    dbRotateObject(7, 0.0f, 45.0f, 0.0f);
    dbPositionCamera(0.0f, 2.0f, -20.0f);
    dbPointCamera(0.0f, 0.0f, 0.0f);
    dbSync();

    const auto& draw = backend->objectDraws.front();
    const auto& camera = backend->lastCamera3D.value();
    std::cout << "3D begin=" << backend->begin3DCount
              << " draws=" << backend->objectDraws.size()
              << " object=" << draw.objectId
              << " pos=" << static_cast<int>(draw.position.x)
              << "," << static_cast<int>(draw.position.y)
              << "," << static_cast<int>(draw.position.z)
              << " camera=" << static_cast<int>(camera.position.x)
              << "," << static_cast<int>(camera.position.y)
              << "," << static_cast<int>(camera.position.z) << "\n";
    return 0;
}
