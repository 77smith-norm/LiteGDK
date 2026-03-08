#include <iostream>

#include "DarkGDK.h"
#include "helpers/TestBackend.h"
#include "runtime/AppRuntime.h"

int main() {
    auto& app = litegdk::runtime();
    auto* backend = litegdk::tests::installTestBackend(app);

    dbText(24, 32, "LiteGDK");
    dbSync();

    std::cout << "Text draws=" << backend->textDraws.size()
              << " frames=" << backend->endFrameCount << "\n";
    return 0;
}
