#pragma once

#include <unordered_set>

#include "runtime/Backend.h"

namespace litegdk {
class InputSnapshot {
public:
    void reset();
    void capture(const BackendInputState& state);

    bool isKeyDown(int key) const;
    bool wasKeyPressed(int key) const;
    bool wasKeyReleased(int key) const;

    int mouseX() const;
    int mouseY() const;
    bool isLeftButtonDown() const;
    bool wasLeftButtonPressed() const;
    bool wasLeftButtonReleased() const;
    bool isRightButtonDown() const;
    bool wasRightButtonPressed() const;
    bool wasRightButtonReleased() const;

private:
    std::unordered_set<int> currentKeys_{};
    std::unordered_set<int> previousKeys_{};
    int mouseX_{0};
    int mouseY_{0};
    int previousMouseX_{0};
    int previousMouseY_{0};
    bool leftButtonDown_{false};
    bool previousLeftButtonDown_{false};
    bool rightButtonDown_{false};
    bool previousRightButtonDown_{false};
};
}  // namespace litegdk
