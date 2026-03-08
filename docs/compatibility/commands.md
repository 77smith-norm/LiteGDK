# Compatibility Matrix

LiteGDK tracks support at both the command-family and individual-command level during early milestones.

## Tier definitions

- `A`: source-friendly and behaviorally aligned for intended educational use
- `B`: supported with small behavioral differences or edge-case gaps
- `C`: approximate or stubbed support with documented limitations
- `X`: not yet implemented

## Command families

| Family | Tier | Notes |
| --- | --- | --- |
| Core | C | Entrypoint, lifecycle shell, and basic system helpers implemented; rendering and backend window behavior still incomplete |
| Text | C | `dbText` is implemented with queued 2D submission and the backend default font; alignment and style helpers are still pending |
| Input | C | Directional keys, selected action keys, generic mapped key-state queries, mouse position, and basic button-state queries are implemented |
| Images | C | Image loading, existence, and size queries are implemented; deletion and advanced image manipulation are still pending |
| Sprites | C | Basic sprite creation, visibility, position helpers, and existence queries are implemented; movement, rotation commands, and collision helpers are still pending |
| Sound | X | Not yet implemented |
| Basic3D | X | Not yet implemented |

## Commands

| Command | Family | Tier | Notes |
| --- | --- | --- | --- |
| `dbText` | Text | B | Draws queued 2D text during `dbSync()` using the backend default font at fixed size `20` |
| `dbInk` | Text | C | Updates foreground text color for subsequent draws; background color is stored but not yet rendered behind glyphs |
| `dbLoadImage` | Images | B | Loads an image into an integer slot, stores metadata, and emits diagnostics for invalid handles or missing files |
| `dbImageExist` | Images | A | Returns whether an image slot currently contains metadata |
| `dbGetImageWidth` | Images | A | Returns the stored width for a loaded image, or `0` for missing slots |
| `dbGetImageHeight` | Images | A | Returns the stored height for a loaded image, or `0` for missing slots |
| `dbSprite` | Sprites | B | Creates or replaces a sprite bound to a previously loaded image slot and renders it during `dbSync()` |
| `dbDeleteSprite` | Sprites | A | Removes a sprite slot when it exists |
| `dbHideSprite` | Sprites | A | Marks a stored sprite invisible without deleting it |
| `dbShowSprite` | Sprites | A | Marks a stored sprite visible again |
| `dbXSprite` | Sprites | B | Updates a stored sprite’s x-position |
| `dbYSprite` | Sprites | B | Updates a stored sprite’s y-position |
| `dbSpriteExist` | Sprites | A | Returns whether a sprite slot currently exists |
| `dbUpKey` | Input | A | Returns whether the mapped Up key is currently down in the captured snapshot |
| `dbDownKey` | Input | A | Returns whether the mapped Down key is currently down in the captured snapshot |
| `dbLeftKey` | Input | A | Returns whether the mapped Left key is currently down in the captured snapshot |
| `dbRightKey` | Input | A | Returns whether the mapped Right key is currently down in the captured snapshot |
| `dbSpaceKey` | Input | A | Returns whether the mapped Space key is currently down in the captured snapshot |
| `dbEscapeKey` | Input | A | Returns whether the mapped Escape key is currently down in the captured snapshot |
| `dbReturnKey` | Input | A | Returns whether the mapped Return key is currently down in the captured snapshot |
| `dbKeyState` | Input | C | Returns key state for the currently mapped educational key subset (`Up`, `Down`, `Left`, `Right`, `Space`, `Escape`, `Return`) |
| `dbMouseX` | Input | A | Returns the captured mouse x-position |
| `dbMouseY` | Input | A | Returns the captured mouse y-position |
| `dbMouseClick` | Input | C | Returns `1` for left-button down, `2` for right-button down, or `0` for no current button down |
