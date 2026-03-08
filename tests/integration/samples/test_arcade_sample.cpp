#include <iostream>
#include <string>

#include "DarkGDK.h"
#include "input/InputKeys.h"
#include "runtime/Backend.h"
#include "SampleHarness.h"

namespace {
litegdk::tests::samples::EntryPointHarness gHarness;
int gPlayerX = 320;
int gPlayerY = 240;
int gFrames = 0;
}

void DarkGDK() {
    const std::string imagePath =
        litegdk::tests::samples::repoPath("examples/textbook/assets/player.ppm").string();

    gHarness.backend().configuredImages.insert_or_assign(imagePath, litegdk::ImageLoadResult{
        .width = 12,
        .height = 12,
    });
    gHarness.backend().inputState.downKeys = {
        litegdk::kInputKeyRight,
        litegdk::kInputKeyDown,
    };

    dbSetDisplayMode(640, 480, 32);
    dbSyncOn();
    dbSyncRate(60);
    dbLoadImage(imagePath.c_str(), 1);
    dbSprite(1, gPlayerX, gPlayerY, 1);

    while (LoopGDK()) {
        if (dbRightKey()) {
            gPlayerX += 6;
        }
        if (dbDownKey()) {
            gPlayerY += 4;
        }

        dbXSprite(1, gPlayerX);
        dbYSprite(1, gPlayerY);

        dbCLS();
        dbText(20, 20, "Arrow keys move the player.");
        dbText(20, 45, "Preserved textbook arcade sample.");
        dbSync();

        ++gFrames;
        if (gFrames == 1) {
            gHarness.backend().inputState = {};
        }
        if (gFrames == 2) {
            gHarness.backend().shouldCloseFlag = true;
        }
    }

    const auto& sprite = gHarness.backend().spriteDraws.back();
    std::cout << "Sample=arcade sprite=" << sprite.spriteId
              << " x=" << static_cast<int>(sprite.x)
              << " y=" << static_cast<int>(sprite.y)
              << " text=" << gHarness.backend().textDraws.size() << "\n";
}
