#include "DarkGDK.h"

void DarkGDK() {
    dbSetDisplayMode(800, 600, 32);
    dbSyncOn();
    dbSyncRate(60);

    while (LoopGDK()) {
        dbCLS();

        dbInk(0xF4E7A1, 0x000000);
        dbText(40, 40, "LiteGDK textbook example");

        dbInk(0x9BE7FF, 0x000000);
        dbText(40, 80, "Hello text from DarkGDK.h");

        dbInk(0xFFFFFF, 0x000000);
        dbText(40, 140, "Close the window to end the sample.");

        dbSync();
    }
}
