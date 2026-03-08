#include <iostream>
#include <string>

#include "DarkGDK.h"
#include "SampleHarness.h"

namespace {
litegdk::tests::samples::EntryPointHarness gHarness;
DWORD gRotationY = 0;
int gFrames = 0;
}

void DarkGDK() {
    const std::string soundPath =
        litegdk::tests::samples::repoPath("examples/textbook/assets/blip.wav").string();

    gHarness.backend().configuredSounds.insert(soundPath);

    dbSetDisplayMode(800, 600, 32);
    dbSyncOn();
    dbSyncRate(60);
    dbLoadSound(soundPath.c_str(), 1);
    dbSetSoundVolume(1, 60);
    dbPlaySound(1);

    dbMakeObjectCube(7, 6.0f);
    dbPositionCamera(0.0f, 3.0f, -18.0f);
    dbPointCamera(0.0f, 0.0f, 0.0f);

    while (LoopGDK()) {
        gRotationY += 15;

        dbCLS();
        dbRotateObject(7, 0.0f, static_cast<float>(gRotationY), 0.0f);
        dbText(20, 20, "Sound and 3D sample.");
        dbSync();

        ++gFrames;
        if (gFrames == 2) {
            gHarness.backend().shouldCloseFlag = true;
        }
    }

    const auto& draw = gHarness.backend().objectDraws.back();
    const auto& camera = gHarness.backend().lastCamera3D.value();
    std::cout << "Sample=multimedia3d plays=" << gHarness.backend().playedSoundIds.size()
              << " draws=" << gHarness.backend().objectDraws.size()
              << " rotationY=" << static_cast<int>(draw.rotation.y)
              << " cameraZ=" << static_cast<int>(camera.position.z) << "\n";
}
