#pragma once

namespace litegdk {
void syncOn();
void syncOff();
void setSyncRate(int rate);
void clearScreen();
bool loop();
void setDisplayMode(int width, int height, int depth);
void requestShutdown();
}  // namespace litegdk
