#include "InputCommands.h"

#include "InputKeys.h"
#include "runtime/AppRuntime.h"

namespace {
int toMouseClickCode(const litegdk::InputSnapshot& snapshot) {
    if (snapshot.isLeftButtonDown()) {
        return 1;
    }

    if (snapshot.isRightButtonDown()) {
        return 2;
    }

    return 0;
}
}  // namespace

namespace litegdk {
bool keyState(int key) {
    return runtime().input().isKeyDown(key);
}

bool upKey() {
    return keyState(kInputKeyUp);
}

bool downKey() {
    return keyState(kInputKeyDown);
}

bool leftKey() {
    return keyState(kInputKeyLeft);
}

bool rightKey() {
    return keyState(kInputKeyRight);
}

bool spaceKey() {
    return keyState(kInputKeySpace);
}

bool escapeKey() {
    return keyState(kInputKeyEscape);
}

bool returnKey() {
    return keyState(kInputKeyReturn);
}

int mouseX() {
    return runtime().input().mouseX();
}

int mouseY() {
    return runtime().input().mouseY();
}

int mouseClick() {
    return toMouseClickCode(runtime().input());
}
}  // namespace litegdk
