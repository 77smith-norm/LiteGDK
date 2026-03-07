# Contributing to LiteGDK

LiteGDK is built incrementally, with small stories, deterministic runtime
state, and tests added alongside behavior changes.

## Workflow

1. Configure the project with `cmake --preset debug`.
2. Build with `cmake --build --preset debug`.
3. Run tests with `ctest --preset debug`.
4. Keep one logical change per commit.

## Testing policy

Follow the testing strategy in `docs/testing/testing-strategy.md`.

The short version:

- Write failing unit tests first when the behavior is headlessly testable.
- Add regression tests for every bug fix.
- Use `tests/unit/` for pure state and command-translation logic.
- Use `tests/integration/` for smoke coverage that touches graphics, audio, or
  other backend seams.

## Tooling

- Formatting rules: `.editorconfig` and `.clang-format`
- VS Code tasks: `.vscode/tasks.json`
- CMake presets: `CMakePresets.json`

## Architecture guardrails

- Public API stays in `include/DarkGDK.h` and `include/LiteGDK/*.h`
- Runtime state and registries stay testable without raylib
- Backend-specific calls stay in `src/backend/`
