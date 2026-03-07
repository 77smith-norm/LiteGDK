# Developer Tooling

LiteGDK uses `.editorconfig` for baseline whitespace and newline rules and
`.clang-format` for C++ formatting.

Use the repo presets and tasks for local workflows:

- Configure: `cmake --preset debug`
- Build: `cmake --build --preset debug`
- Test: `ctest --preset debug`

The committed VS Code task file mirrors those commands so contributors can
configure, build, and test without recreating local task definitions.
