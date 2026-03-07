# LiteGDK — M0 Completion + M1 Start Plan
**Date:** 2026-03-07  
**Author:** Norm (harness engineer)

---

## Current State

One commit on `main` from Phase 0 scaffolding this morning:
- CMakeLists.txt with raylib + Catch2 via FetchContent ✅
- `.clang-format` ✅
- GitHub Actions CI skeleton ✅
- `include/LiteGDK/Runtime.h` + `src/runtime/Runtime.cpp` — partial skeleton
- `src/compat/DarkGDK.cpp` — stub
- `tests/unit/runtime/test_runtime.cpp` — one passing test
- `docs/prd.json` — full roadmap (authoritative)
- `docs/design/` — PRD + Design Spec

**Missing from M0:**
- Most `src/` subdirectories not created yet
- `include/LiteGDK/` only has `Runtime.h` — no family headers
- No `README.md`, `CONTRIBUTING.md`, `LICENSE`
- No `docs/architecture/`, `docs/compatibility/`, `docs/testing/`, `docs/contributing/`
- No `CMakePresets.json`, `.vscode/` tasks, `.editorconfig`
- No compatibility matrix stub

---

## Goal

Complete M0 fully, then begin M1 (runtime + app loop).

---

## Ordered Steps

### Phase A — M0 remaining stories (S0.1.3, S0.2.1, S0.2.2, S0.2.3)

1. **S0.1.3 — Code quality tooling**
   - Add `.editorconfig`
   - Add `CMakePresets.json` (configurePreset for debug, test preset)
   - Add `.vscode/tasks.json` (configure, build, test tasks)
   - Add `LICENSE` (MIT)
   - Acceptance: developer can build+test from VS Code tasks

2. **S0.2.1 — README and quick start**
   - `README.md` with: what it is, build steps, run tests, minimal example
   - Acceptance: new contributor can build from README alone

3. **S0.2.2 — Testing strategy doc**
   - `docs/testing/testing-strategy.md`
   - `CONTRIBUTING.md` (references testing strategy)
   - Acceptance: doc names where tests live and when to add them

4. **S0.2.3 — Compatibility matrix stub**
   - `docs/compatibility/commands.md`
   - Table with families: Core, Text, Input, Images, Sprites, Sound, Basic3D
   - Tier A/B/C/X definitions
   - All entries start as "X — not yet implemented"
   - Acceptance: all planned families appear

### Phase B — Directory and header scaffolding (prerequisite for M1)

5. Create all `src/` subdirectories with `.gitkeep` or stub files:
   `core/`, `system/`, `text/`, `input/`, `images/`, `sprites/`, `sound/`, `basic3d/`, `platform/`, `backend/`

6. Create all `include/LiteGDK/` family headers (stubs — declarations only):
   `Config.h`, `Types.h`, `Core.h`, `System.h`, `Text.h`, `Input.h`, `Images.h`, `Sprites.h`, `Sound.h`, `Basic3D.h`, `Compatibility.h`

7. Update `include/DarkGDK.h` to fan-out to all family headers

8. Update `CMakeLists.txt` to reflect new structure (add src dirs to library target as they get implementation files)

9. Commit: `chore: complete M0 scaffold — all directories, headers, and docs`

### Phase C — Begin M1: S1.2.1 (AppRuntime + FrameState)

10. Write failing Catch2 tests first for:
    - Runtime default state
    - FrameState mutation (frame counter, sync rate, clear color)
    - Runtime reset (deterministic)

11. Implement `AppRuntime` and `FrameState` in `src/runtime/`

12. Run suite green → commit: `feat: implement AppRuntime and FrameState (S1.2.1)`

### Phase D — S1.2.2 (Registry infrastructure)

13. Write failing tests for registry: insert, find, remove, replace, out-of-range

14. Implement `Registry` template or service in `src/runtime/`

15. Green → commit: `feat: implement integer-slot registry infrastructure (S1.2.2)`

---

## Compaction Recovery

If context compacts:
1. `cat docs/prd.json | python3 -c "import json,sys; d=json.load(sys.stdin); [print(s['id'], s['title']) for m in d['milestones'] for e in m['epics'] for s in e['stories']]"`
2. `git log --oneline -20`
3. `cmake --build build && cd build && ctest`
4. Re-read this plan: `cat docs/2026-03-07-m0-completion-plan.md`
5. Resume at next incomplete step.

---

## Risks

- CMakeLists.txt will need updating as new `.cpp` files are added to `src/` — keep it in sync
- Registry template: keep it headlessly testable (no raylib in registry logic)
- Don't start S1.3.x (window/loop commands) until S1.2.1 and S1.2.2 are green and committed
