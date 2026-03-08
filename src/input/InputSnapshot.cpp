#include "InputSnapshot.h"

namespace {
std::unordered_set<int> toKeySet(const std::vector<int>& keys) {
    return std::unordered_set<int>(keys.begin(), keys.end());
}
}

namespace litegdk {
void InputSnapshot::reset() {
    currentKeys_.clear();
    previousKeys_.clear();
    mouseX_ = 0;
    mouseY_ = 0;
    previousMouseX_ = 0;
    previousMouseY_ = 0;
    leftButtonDown_ = false;
    previousLeftButtonDown_ = false;
    rightButtonDown_ = false;
    previousRightButtonDown_ = false;
}

void InputSnapshot::capture(const BackendInputState& state) {
    previousKeys_ = currentKeys_;
    currentKeys_ = toKeySet(state.downKeys);

    previousMouseX_ = mouseX_;
    previousMouseY_ = mouseY_;
    mouseX_ = state.mouseX;
    mouseY_ = state.mouseY;

    previousLeftButtonDown_ = leftButtonDown_;
    leftButtonDown_ = state.leftButtonDown;
    previousRightButtonDown_ = rightButtonDown_;
    rightButtonDown_ = state.rightButtonDown;
}

bool InputSnapshot::isKeyDown(int key) const {
    return currentKeys_.contains(key);
}

bool InputSnapshot::wasKeyPressed(int key) const {
    return currentKeys_.contains(key) && !previousKeys_.contains(key);
}

bool InputSnapshot::wasKeyReleased(int key) const {
    return !currentKeys_.contains(key) && previousKeys_.contains(key);
}

int InputSnapshot::mouseX() const {
    return mouseX_;
}

int InputSnapshot::mouseY() const {
    return mouseY_;
}

bool InputSnapshot::isLeftButtonDown() const {
    return leftButtonDown_;
}

bool InputSnapshot::wasLeftButtonPressed() const {
    return leftButtonDown_ && !previousLeftButtonDown_;
}

bool InputSnapshot::wasLeftButtonReleased() const {
    return !leftButtonDown_ && previousLeftButtonDown_;
}

bool InputSnapshot::isRightButtonDown() const {
    return rightButtonDown_;
}

bool InputSnapshot::wasRightButtonPressed() const {
    return rightButtonDown_ && !previousRightButtonDown_;
}

bool InputSnapshot::wasRightButtonReleased() const {
    return !rightButtonDown_ && previousRightButtonDown_;
}
}  // namespace litegdk
