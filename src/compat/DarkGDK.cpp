#include "DarkGDK.h"
#include "core/FrameRunner.h"
#include "core/Lifecycle.h"

void dbSyncOn() {
    litegdk::syncOn();
}

void dbSyncOff() {
    litegdk::syncOff();
}

void dbSyncRate(int rate) {
    litegdk::setSyncRate(rate);
}

void dbSync() {
    litegdk::syncFrame();
}

bool LoopGDK() {
    return litegdk::loop();
}

void dbSetDisplayMode(int width, int height, int depth) {
    litegdk::setDisplayMode(width, height, depth);
}

void dbCLS() {
    litegdk::clearScreen();
}
