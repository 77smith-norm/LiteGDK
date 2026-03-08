#include "DarkGDK.h"

namespace {
constexpr int kCubeId = 1;
}

void DarkGDK() {
    dbSetDisplayMode(960, 540, 32);
    dbSyncOn();
    dbSyncRate(60);

    dbMakeObjectCube(kCubeId, 4.0f);
    dbPositionObject(kCubeId, 0.0f, 0.0f, 0.0f);
    dbPositionCamera(0.0f, 4.0f, -18.0f);
    dbPointCamera(0.0f, 0.0f, 0.0f);

    float angle = 0.0f;

    while (LoopGDK()) {
        angle += 1.0f;
        if (angle >= 360.0f) {
            angle -= 360.0f;
        }

        dbCLS();
        dbRotateObject(kCubeId, angle * 0.5f, angle, 0.0f);
        dbText(20, 20, "Rotating cube example");
        dbText(20, 50, "Close the window to exit.");
        dbSync();
    }
}
