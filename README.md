# LiteGDK

LiteGDK is a DarkGDK-inspired educational compatibility SDK built on raylib.
The public surface stays beginner-friendly with `db*` free functions and a
single `#include "DarkGDK.h"` entry point, while the implementation stays
modular and testable.

## Current status

The repository currently contains the foundation scaffold and the first runtime
tests. The classic app loop and command families are still being implemented,
so the public API is intentionally minimal for now.

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

At the current milestone the lifecycle shell is in place, but window/backend
behavior and `dbSync()` frame submission are still stubs. Targets that use
`void DarkGDK()` should link against `litegdk_entrypoint`, which supplies the
bootstrap `main()` wrapper.

## Documentation

- Roadmap: `docs/prd.json`
- Product requirements: `docs/design/LiteGDK_PRD.md`
- Design specification: `docs/design/LiteGDK_Design_Specification.md`
- Tooling notes: `docs/contributing/tooling.md`
