#include <iostream>

#include "DarkGDK.h"
#include "core/Lifecycle.h"
#include "helpers/TestBackend.h"
#include "runtime/AppRuntime.h"

void DarkGDK() {
    int iterations = 0;
    auto& app = litegdk::runtime();
    litegdk::tests::installTestBackend(app);

    dbSyncOn();
    dbSyncRate(30);

    while (LoopGDK()) {
        ++iterations;
        dbCLS();
        dbSync();
        litegdk::requestShutdown();
    }

    std::cout << "LoopGDK iterations=" << iterations
              << " frames=" << app.frameState().frameCount()
              << " clear=" << app.frameState().clearRequested() << "\n";
}
