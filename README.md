# LiteGDK

**Old textbook style, modern toolchain.**

LiteGDK is an open-source educational compatibility SDK inspired by DarkGDK. It lets learners and hobbyists write classic procedural C++ game programs using familiar `db*` functions and run them on modern macOS, Windows, and Linux — without legacy IDE workflows, DirectX 9, or abandoned runtimes.

```cpp
#include "DarkGDK.h"

void DarkGDK() {
    dbSyncOn();
    dbSyncRate(60);

    dbLoadImage("player.png", 1);
    dbSprite(1, 100, 100, 1);

    while (LoopGDK()) {
        dbCLS();
        dbText(10, 10, "Hello LiteGDK");
        dbSync();
    }
}
```

> **Preview 0.1** — Core, Text, Input, Images, Sprites, Sound, and Basic 3D are implemented. See the [compatibility matrix](docs/compatibility/commands.md) for what's supported.

---

## Quick start (VS Code)

See **[docs/getting-started-vscode.md](docs/getting-started-vscode.md)** for a complete step-by-step walkthrough.

---

## Prerequisites

| Tool | Version | Notes |
|------|---------|-------|
| CMake | 3.20+ | [cmake.org](https://cmake.org/download/) |
| C++20 compiler | — | Clang 14+ / GCC 11+ / MSVC 2022 |
| Git | any | For cloning and FetchContent dependencies |
| VS Code (optional) | any | Recommended; tasks included |

raylib and Catch2 are fetched automatically — no manual installs needed.

---

## Build

```bash
# Clone
git clone https://github.com/77smith-norm/LiteGDK.git
cd LiteGDK

# Configure
cmake --preset debug

# Build
cmake --build --preset debug

# Run tests
ctest --preset debug --output-on-failure
```

---

## VS Code tasks

Open the folder in VS Code. The included `.vscode/tasks.json` provides:

| Task | What it does |
|------|-------------|
| `LiteGDK: Configure` | `cmake --preset debug` |
| `LiteGDK: Build` | `cmake --build --preset debug` |
| `LiteGDK: Test` | `ctest --preset debug --output-on-failure` |

Run them via **Terminal → Run Task** or bind to a keyboard shortcut.

---

## Examples

Canonical samples live in `examples/textbook/`. After building, executables appear under `build/examples/textbook/`.

| Example | Demonstrates |
|---------|-------------|
| `hello_text` | Window loop, dbText, dbSync |
| `sprite_movement` | Load image, create sprite, move with keyboard |
| `simple_audio` | Load and play a sound |
| `basic_3d` | Camera setup, 3D cube, rotation |

---

## Project structure

```
LiteGDK/
  include/DarkGDK.h        ← the only header users need
  include/LiteGDK/         ← internal family headers
  src/                     ← implementation (runtime, core, text, input, …)
  examples/textbook/       ← quick-start samples
  tests/                   ← Catch2 unit + integration tests
  docs/                    ← architecture, compatibility, contributing
```

---

## Documentation

| Doc | Description |
|-----|-------------|
| [Getting started (VS Code)](docs/getting-started-vscode.md) | Step-by-step setup guide |
| [Compatibility matrix](docs/compatibility/commands.md) | Which commands are supported and at what tier |
| [Architecture](docs/design/LiteGDK_Design_Specification.md) | Layer design and internals |
| [Contributing](CONTRIBUTING.md) | How to add a command family or fix a bug |
| [Preview release notes](docs/releases/preview-0.1.md) | What's in preview 0.1 |

---

## Compatibility tiers

| Tier | Meaning |
|------|---------|
| **A** | Source-compatible; behaves as expected for educational use |
| **B** | Supported with minor behavioral differences |
| **C** | Approximate/stubbed; compiles, limitations documented |
| **X** | Not implemented |

---

## License

MIT
