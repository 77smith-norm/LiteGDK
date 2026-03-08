#include "DarkGDK.h"
#include "text/TextCommands.h"

void dbText(int x, int y, const char* text) {
    litegdk::drawText(x, y, text == nullptr ? "" : text);
}

void dbInk(DWORD foreground, DWORD background) {
    litegdk::setTextInk(foreground, background);
}
