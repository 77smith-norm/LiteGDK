#include <iostream>

#include "DarkGDK.h"
#include "core/Lifecycle.h"
#include "runtime/AppRuntime.h"

void DarkGDK() {
    int iterations = 0;

    dbSyncOn();
    dbSyncRate(30);

    while (LoopGDK()) {
        ++iterations;
        dbCLS();
        dbSync();
        litegdk::requestShutdown();
    }

    std::cout << "LoopGDK iterations=" << iterations
              << " frames=" << litegdk::runtime().frameState().frameCount()
              << " clear=" << litegdk::runtime().frameState().clearRequested() << "\n";
}
