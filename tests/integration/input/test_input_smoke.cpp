#include <iostream>

#include "DarkGDK.h"
#include "helpers/TestBackend.h"
#include "input/InputKeys.h"
#include "runtime/AppRuntime.h"

int main() {
    auto& app = litegdk::runtime();
    auto* backend = litegdk::tests::installTestBackend(app);

    backend->inputState = {
        .downKeys = {litegdk::kInputKeyUp},
        .mouseX = 144,
        .mouseY = 233,
        .leftButtonDown = true,
    };

    dbSync();

    std::cout << "Up=" << dbUpKey()
              << " mouse=" << dbMouseX() << "," << dbMouseY()
              << " click=" << dbMouseClick() << "\n";
    return 0;
}
