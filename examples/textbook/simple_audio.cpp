#include <string>

#include "DarkGDK.h"
#include "ExampleAssets.h"

namespace {
constexpr int kSoundId = 1;
}

void DarkGDK() {
    dbSetDisplayMode(800, 600, 32);
    dbSyncOn();
    dbSyncRate(60);

    const std::string soundPath = textbookAssetPath("blip.wav").string();
    dbLoadSound(soundPath.c_str(), kSoundId);
    dbPlaySound(kSoundId);

    bool wasSpaceDown = false;

    while (LoopGDK()) {
        const bool spaceDown = dbSpaceKey() != 0;
        if (spaceDown && !wasSpaceDown) {
            dbPlaySound(kSoundId);
        }
        wasSpaceDown = spaceDown;

        dbCLS();
        dbText(20, 20, "Press SPACE to replay the sound.");
        dbText(20, 50, "The sample also plays it once on startup.");
        dbSync();
    }
}
