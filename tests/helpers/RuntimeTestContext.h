#pragma once

#include "TestBackend.h"
#include "runtime/AppRuntime.h"

namespace litegdk::tests {
class RuntimeTestContext {
public:
    RuntimeTestContext()
        : app_(runtime()),
          backend_(installTestBackend(app_)) {}

    ~RuntimeTestContext() {
        app_.reset();
    }

    AppRuntime& app() {
        return app_;
    }

    TestBackend& backend() {
        return *backend_;
    }

private:
    AppRuntime& app_;
    TestBackend* backend_;
};
}  // namespace litegdk::tests
