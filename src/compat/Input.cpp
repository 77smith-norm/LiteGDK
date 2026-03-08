#include "DarkGDK.h"
#include "input/InputCommands.h"

int dbUpKey() {
    return litegdk::upKey() ? TRUE : FALSE;
}

int dbDownKey() {
    return litegdk::downKey() ? TRUE : FALSE;
}

int dbLeftKey() {
    return litegdk::leftKey() ? TRUE : FALSE;
}

int dbRightKey() {
    return litegdk::rightKey() ? TRUE : FALSE;
}

int dbSpaceKey() {
    return litegdk::spaceKey() ? TRUE : FALSE;
}

int dbEscapeKey() {
    return litegdk::escapeKey() ? TRUE : FALSE;
}

int dbReturnKey() {
    return litegdk::returnKey() ? TRUE : FALSE;
}

int dbKeyState(int key) {
    return litegdk::keyState(key) ? TRUE : FALSE;
}

int dbMouseX() {
    return litegdk::mouseX();
}

int dbMouseY() {
    return litegdk::mouseY();
}

int dbMouseClick() {
    return litegdk::mouseClick();
}
