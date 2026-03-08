# LiteGDK

LiteGDK is a DarkGDK-inspired educational compatibility SDK built on raylib.
The public surface stays beginner-friendly with `db*` free functions and a
single `#include "DarkGDK.h"` entry point, while the implementation stays
modular and testable.

## Current status

Milestones M0 through M3 are complete. LiteGDK now ships a usable educational
subset across core loop, text, input, images, sprites, sound, and basic 3D,
with the remaining preview work focused on examples, CI, and release docs.

## Prerequisites

- CMake 3.20 or newer
- A C++20 compiler
- Git

raylib and Catch2 are fetched automatically by CMake during configure.

## Build

Configure the default debug build:

```bash
cmake --preset debug
```

Build the project:

```bash
cmake --build --preset debug
```

## Test

Run the unit test suite:

```bash
ctest --preset debug
```

## VS Code

The repository includes `.vscode/tasks.json` for the standard workflow:

- `LiteGDK: Configure`
- `LiteGDK: Build`
- `LiteGDK: Test`

These tasks use the same commands as the presets above.

## Minimal example

The long-term goal is DarkGDK-style source compatibility through a single
header:

```cpp
#include "DarkGDK.h"

void DarkGDK() {
    dbSyncOn();
    dbSyncRate(60);

    while (LoopGDK()) {
        dbCLS();
        dbSync();
    }
}
```

Targets that use `void DarkGDK()` should link against `litegdk_entrypoint`,
which supplies the bootstrap `main()` wrapper for textbook-style programs.

## Textbook examples

Canonical quick-start samples now live under `examples/textbook/`:

- `hello_text`
- `sprite_movement`
- `simple_audio`
- `basic_3d`

After building, the example executables are emitted under
`build/examples/textbook/`.

## Documentation

- Roadmap: `docs/prd.json`
- Product requirements: `docs/design/LiteGDK_PRD.md`
- Design specification: `docs/design/LiteGDK_Design_Specification.md`
- Tooling notes: `docs/contributing/tooling.md`
