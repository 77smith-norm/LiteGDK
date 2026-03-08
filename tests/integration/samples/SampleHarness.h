#pragma once

#include <array>
#include <filesystem>
#include <string>
#include <string_view>

#include "helpers/TestBackend.h"
#include "runtime/AppRuntime.h"

namespace litegdk::tests::samples {
inline std::filesystem::path repoPath(std::string_view relativePath) {
    namespace fs = std::filesystem;

    const fs::path cwd = fs::current_path();
    const fs::path relative{std::string(relativePath)};
    const std::array<fs::path, 4> candidates{
        cwd / relative,
        cwd.parent_path() / relative,
        cwd.parent_path().parent_path() / relative,
        cwd.parent_path().parent_path().parent_path() / relative,
    };

    for (const auto& candidate : candidates) {
        if (fs::exists(candidate)) {
            return fs::weakly_canonical(candidate);
        }
    }

    return cwd / relative;
}

class EntryPointHarness {
public:
    EntryPointHarness()
        : app_(runtime()),
          backend_(installTestBackend(app_)) {}

    ~EntryPointHarness() {
        app_.reset();
    }

    TestBackend& backend() {
        return *backend_;
    }

private:
    AppRuntime& app_;
    TestBackend* backend_;
};
}  // namespace litegdk::tests::samples
