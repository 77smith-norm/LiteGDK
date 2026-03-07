#include "LiteGDK/Runtime.h"

namespace litegdk {
    Runtime::Runtime() {}
    Runtime::~Runtime() {}

    void Runtime::initialize() {}
    void Runtime::shutdown() {}
    bool Runtime::isRunning() const { return false; }

    Runtime& runtime() {
        static Runtime instance;
        return instance;
    }
}
