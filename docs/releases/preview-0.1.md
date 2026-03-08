# LiteGDK Preview 0.1

Date: March 7, 2026

## Summary

`preview-0.1` is the first public LiteGDK preview: a DarkGDK-inspired,
education-first compatibility SDK built on raylib with a tested, source-friendly
subset of the classic textbook workflow.

## Included in this preview

- Core loop helpers built around `DarkGDK()`, `LoopGDK()`, and `dbSync()`
- Text rendering, mapped keyboard and mouse input, image loading and metadata queries
- Basic sprite creation and movement helpers
- Sound and music loading, playback, pause/resume, stop, and volume
- Simple 3D camera targeting plus cube creation, positioning, and rotation
- Four canonical quick-start examples in `examples/textbook/`
- Two preserved DarkGDK-style sample ports in `tests/integration/samples/`
- CI coverage for build, unit tests, and integration smoke checks

## Compatibility posture

- Most implemented commands in this preview are Tier `A` or `B` for educational use.
- The main Tier `C` areas are the historical sync model, `dbCLS()`, `dbInk()` background handling, `dbKeyState()`, and `dbMouseClick()`.
- The full command-by-command breakdown lives in `docs/compatibility/commands.md`.

## Known limitations

- LiteGDK does not aim for exact historical DarkGDK behavior; it aims for source-friendly educational compatibility.
- `dbSyncOn()` and `dbSyncOff()` currently store compatibility state, but the preview still depends on explicit `dbSync()` calls to submit frames.
- `dbCLS()` is approximate because the current backend clears at frame begin even when a sample does not call it.
- `dbText()` uses the backend default font at fixed size `20`, and `dbInk()` does not yet draw the background color behind glyphs.
- `dbKeyState()` only supports the currently mapped educational key subset: arrows, `Space`, `Escape`, and `Return`.
- `dbMouseClick()` reports only current left/right down state, not broader button event history.
- Image support is limited to loading and dimension/existence queries.
- Sprite support does not yet include rotation, scaling, animation helpers, or collision helpers.
- Sound and music support does not yet include status polling, channels, or looping helpers.
- Basic 3D support is intentionally narrow: a simple camera target plus cube primitives and transform updates.

## Recommended starting points

- `hello_text`
- `sprite_movement`
- `simple_audio`
- `basic_3d`

All four example targets are built with the main project and emitted under
`build/examples/textbook/`.
