# AGENTS.md — LiteGDK Coding Agent Guide

**Project:** LiteGDK — DarkGDK-inspired educational compatibility SDK  
**Language:** C++20 | **Backend:** raylib | **Build:** CMake | **Tests:** Catch2  
**Repo:** `~/Developer/LiteGDK` | **GitHub:** `77smith-norm/LiteGDK`

---

## What This Project Is

LiteGDK lets learners run classic DarkGDK-style procedural C++ game samples on modern systems.  
Public API: `#include "DarkGDK.h"`, `db`-prefixed free functions, integer asset IDs, simple loop/sync model.  
Internally: modern, namespaced, modular, testable.

---

## Authoritative Files — Read These First

| File | Purpose |
|------|---------|
| `docs/prd.json` | Full roadmap: milestones, epics, stories, dependencies, acceptance criteria |
| `docs/design/LiteGDK_Design_Specification.md` | Architecture, layer boundaries, naming conventions |
| `docs/design/LiteGDK_PRD.md` | Human-readable PRD (narrative version of prd.json) |

**Before writing any code:** read `docs/prd.json` to understand the story you are implementing, its `depends_on`, and its acceptance criteria.

---

## Architecture — Non-Negotiable

Four layers (never skip or collapse):

1. **Public API** — `include/DarkGDK.h` + `include/LiteGDK/*.h` — free functions only, no internal types exposed
2. **Command/Facade** — thin `db*` implementations in `src/compat/` — translates public calls to runtime
3. **Runtime/Service** — `src/runtime/`, `src/core/`, etc. — all state, registries, frame logic
4. **Backend** — `src/backend/` — raylib calls only live here

**Key rule:** raylib calls never appear above the backend layer. Registries and state must be unit-testable without a live graphics context.

---

## TCR — Mandatory Workflow

```
write ONE failing test → run suite → GREEN → commit → next
                                    → RED   → revert ALL → decompose → retry
```

- Write/update a failing Catch2 test BEFORE implementing logic (where headlessly testable)
- One logical change per commit
- Never commit red tests
- `cmake --build build && cd build && ctest --output-on-failure`

---

## Compaction Recovery

**If context compacts, immediately:**
1. `cat docs/prd.json | python3 -c "import json,sys; d=json.load(sys.stdin); [print(s['id'], s['title']) for m in d['milestones'] for e in m['epics'] for s in e['stories']]"`
2. `git log --oneline -20`
3. `cmake --build build && cd build && ctest` — confirm green
4. Find the next incomplete story from `prd.json` whose `depends_on` are all committed
5. Resume. Do not re-implement committed work.

---

## Build Commands

```bash
# Configure (first time or after CMakeLists changes)
cmake -B build -DCMAKE_BUILD_TYPE=Debug

# Build
cmake --build build

# Test
cd build && ctest --output-on-failure

# Or combined
cmake --build build && cd build && ctest --output-on-failure
```

---

## Directory Structure

```
LiteGDK/
  CMakeLists.txt
  AGENTS.md                    ← this file
  docs/
    prd.json                   ← roadmap (authoritative)
    design/
    architecture/
    compatibility/
    testing/
    contributing/
  include/
    DarkGDK.h
    LiteGDK/                   ← one header per command family
  src/
    runtime/                   ← AppRuntime, FrameState, Registry, Diagnostics
    core/                      ← LoopGDK, dbSync, dbCLS, dbSyncOn/Off/Rate
    system/                    ← timer, screen size, random helpers
    text/                      ← dbText, ink/color state
    input/                     ← InputSnapshot, keyboard/mouse commands
    images/                    ← ImageRegistry, dbLoadImage
    sprites/                   ← SpriteRegistry, dbSprite
    sound/                     ← SoundRegistry, MusicRegistry, audio commands
    basic3d/                   ← CameraState, ObjectRegistry, 3D commands
    platform/                  ← platform-specific shims
    compat/                    ← DarkGDK.cpp entrypoint bootstrap
    backend/                   ← ALL raylib calls live here only
  tests/
    unit/                      ← headless, no raylib
    integration/               ← may need graphics context; mark clearly
    fixtures/                  ← test assets (images, sounds)
    helpers/                   ← shared test utilities
  examples/
    textbook/
    demos/
  .github/workflows/
    ci.yml
```

---

## Quality Gates (Definition of Done per Story)

1. Catch2 tests added first / alongside implementation
2. `cmake --build build` succeeds cleanly (no warnings treated as errors)
3. `ctest --output-on-failure` passes (all green)
4. Public headers compile cleanly (`#include "DarkGDK.h"` only for user code)
5. Compatibility tier declared (A/B/C/X) for every new public command
6. Docs updated (compatibility matrix, example if public behavior changed)
7. No obvious resource leaks in modified area

---

## Story Selection Algorithm

From `prd.json > next_task_selector`:
1. Stories not yet completed whose `depends_on` are all done
2. Lowest milestone → highest priority (P0 > P1) → smallest complexity (S > M > L)
3. Prefer the story that unblocks the most dependents

---

## Notes

- `samples/` directory exists in repo — treat as `examples/` for now (legacy name from initial scaffold)
- One commit per story minimum; use `feat:`, `test:`, `docs:`, `chore:` prefixes
- GitHub: push to `main` directly (no PR required unless story is L complexity)
