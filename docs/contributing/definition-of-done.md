# Definition of Done

A LiteGDK change is done only when every applicable item below is true.

## Scope and architecture

- The story or bug fix is small enough to review as one logical change.
- Hard dependencies for the work are already complete.
- Public API changes stay in `include/DarkGDK.h` and `include/LiteGDK/*.h`.
- Runtime state, registries, and command translation stay testable without direct raylib calls.
- Backend-specific calls remain isolated to `src/backend/`.

## Tests and verification

- A failing test was added first when the behavior was headlessly testable.
- Every bug fix includes a regression test.
- New public behavior has unit and/or integration coverage in the appropriate `tests/` area.
- The project configures and builds cleanly.
- `ctest --output-on-failure` passes locally after the change.
- CI requirements stay green or are updated as part of the same work when the build matrix needs to change.

## Public API and documentation

- Public headers still compile cleanly through `#include "DarkGDK.h"` for user code.
- Every new or changed public command has a compatibility tier declared in `docs/compatibility/commands.md`.
- User-facing docs are updated when behavior, workflows, or limitations changed.
- An example or preserved regression artifact is added or updated when public behavior changed.
- Approximations and known limitations are documented honestly.

## Resource and runtime safety

- No obvious resource leaks were introduced in the modified area.
- Asset lifecycle changes unload or reset runtime-owned resources correctly.
- Runtime reset remains deterministic for tests and smoke samples.

## Commit and review readiness

- The final commit message matches the story or change scope.
- The diff does not include unrelated generated files or local-only artifacts.
- Reviewer-facing notes call out tradeoffs, approximations, and follow-up work where relevant.
