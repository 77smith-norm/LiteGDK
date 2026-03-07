# Testing Strategy

LiteGDK uses Catch2 for both unit and integration coverage.

## Test layout

- `tests/unit/`: headless tests for runtime state, registries, translation
  logic, and any service that should not need a live graphics context
- `tests/integration/`: smoke tests that exercise the public API and backend
  seams where a graphics or audio context may be involved
- `tests/fixtures/`: stable input assets used by automated tests
- `tests/helpers/`: shared test utilities and fixtures

## When to add tests

- Add or update a failing test before implementing behavior that can be tested
  headlessly.
- Every bug fix adds a regression test.
- New public commands should add unit coverage for state/translation behavior.
- New command families should add at least one integration smoke test once the
  backend path exists.

## TCR workflow

LiteGDK uses a strict `test && commit || revert` workflow:

1. Write one failing test.
2. Implement the smallest change that makes the suite green.
3. Run the build and test commands.
4. Commit one logical story once the suite is green.

If the suite stays red, revert the change, reduce scope, and retry.

## Local commands

```bash
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

## Design constraints

- Keep raylib calls in the backend layer.
- Keep registries and runtime state deterministic and resettable.
- Prefer unit tests for pure state transitions and integration tests for backend
  orchestration.
