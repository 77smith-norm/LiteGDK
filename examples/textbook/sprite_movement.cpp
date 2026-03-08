#include <algorithm>
#include <string>

#include "DarkGDK.h"
#include "ExampleAssets.h"

namespace {
constexpr int kImageId = 1;
constexpr int kSpriteId = 1;
constexpr int kSpriteSize = 12;
constexpr int kStep = 4;
}

void DarkGDK() {
    dbSetDisplayMode(800, 600, 32);
    dbSyncOn();
    dbSyncRate(60);

    const std::string imagePath = textbookAssetPath("player.ppm").string();
    dbLoadImage(imagePath.c_str(), kImageId);

    int x = dbScreenWidth() / 2;
    int y = dbScreenHeight() / 2;
    dbSprite(kSpriteId, x, y, kImageId);

    while (LoopGDK()) {
        if (dbLeftKey()) {
            x -= kStep;
        }
        if (dbRightKey()) {
            x += kStep;
        }
        if (dbUpKey()) {
            y -= kStep;
        }
        if (dbDownKey()) {
            y += kStep;
        }

        x = std::clamp(x, 0, dbScreenWidth() - kSpriteSize);
        y = std::clamp(y, 0, dbScreenHeight() - kSpriteSize);

        dbXSprite(kSpriteId, x);
        dbYSprite(kSpriteId, y);

        dbCLS();
        dbText(20, 20, "Use the arrow keys to move the sprite.");
        dbText(20, 50, "Close the window to exit.");
        dbSync();
    }
}
