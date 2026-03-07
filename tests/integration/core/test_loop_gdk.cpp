#include <iostream>

#include "DarkGDK.h"
#include "core/Lifecycle.h"

void DarkGDK() {
    int iterations = 0;

    dbSyncOn();
    dbSyncRate(30);

    while (LoopGDK()) {
        ++iterations;
        dbCLS();
        litegdk::requestShutdown();
    }

    std::cout << "LoopGDK iterations=" << iterations << "\n";
}
