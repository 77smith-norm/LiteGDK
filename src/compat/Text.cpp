#include "DarkGDK.h"
#include "text/TextCommands.h"

void dbText(int x, int y, const char* text) {
    litegdk::drawText(x, y, text == nullptr ? "" : text);
}
