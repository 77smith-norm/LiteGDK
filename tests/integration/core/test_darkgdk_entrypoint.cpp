#include <iostream>

#include "DarkGDK.h"

void (*g_entrypoint)() = &DarkGDK;

void DarkGDK() {
    if (g_entrypoint == &DarkGDK) {
        std::cout << "DarkGDK entrypoint invoked\n";
    }
}
