#pragma once

#include <array>
#include <filesystem>
#include <string>
#include <string_view>

inline std::filesystem::path textbookAssetPath(std::string_view filename) {
    namespace fs = std::filesystem;

    const fs::path cwd = fs::current_path();
    const fs::path name{std::string(filename)};
    const std::array<fs::path, 5> candidates{
        cwd / "assets" / name,
        cwd / "examples" / "textbook" / "assets" / name,
        cwd.parent_path() / "assets" / name,
        cwd.parent_path() / "examples" / "textbook" / "assets" / name,
        cwd.parent_path().parent_path() / "examples" / "textbook" / "assets" / name,
    };

    for (const auto& candidate : candidates) {
        if (fs::exists(candidate)) {
            return fs::weakly_canonical(candidate);
        }
    }

    return cwd / "examples" / "textbook" / "assets" / name;
}
