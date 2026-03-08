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
| Sound | C | Basic sound/music loading, playback, stop/pause/resume, and volume control are implemented; channels, looping helpers, and status queries are still pending |
| Basic3D | C | Basic cube objects, object transform helpers, camera positioning/targeting, and frame-loop 3D submission are implemented; additional primitives and broader camera/object commands are still pending |

## Commands

| Command | Family | Tier | Notes |
| --- | --- | --- | --- |
| `dbText` | Text | B | Draws queued 2D text during `dbSync()` using the backend default font at fixed size `20` |
| `dbInk` | Text | C | Updates foreground text color for subsequent draws; background color is stored but not yet rendered behind glyphs |
| `dbLoadImage` | Images | B | Loads an image into an integer slot, stores metadata, and emits diagnostics for invalid handles or missing files |
| `dbImageExist` | Images | A | Returns whether an image slot currently contains metadata |
| `dbGetImageWidth` | Images | A | Returns the stored width for a loaded image, or `0` for missing slots |
| `dbGetImageHeight` | Images | A | Returns the stored height for a loaded image, or `0` for missing slots |
| `dbLoadSound` | Sound | B | Loads a sound into an integer slot, replacing prior contents and emitting diagnostics for invalid handles or missing files |
| `dbDeleteSound` | Sound | A | Removes a loaded sound slot when it exists |
| `dbPlaySound` | Sound | B | Plays a previously loaded sound slot immediately |
| `dbStopSound` | Sound | B | Stops a previously loaded sound slot |
| `dbSetSoundVolume` | Sound | B | Sets per-sound volume using a clamped `0` to `100` range |
| `dbLoadMusic` | Sound | B | Loads a music stream into an integer slot, replacing prior contents and emitting diagnostics for invalid handles or missing files |
| `dbDeleteMusic` | Sound | A | Removes a loaded music slot when it exists |
| `dbPlayMusic` | Sound | B | Starts playback for a previously loaded music slot |
| `dbStopMusic` | Sound | B | Stops playback for a previously loaded music slot |
| `dbPauseMusic` | Sound | B | Pauses playback for a previously loaded music slot |
| `dbResumeMusic` | Sound | B | Resumes playback for a previously loaded music slot |
| `dbSetMusicVolume` | Sound | B | Sets per-music volume using a clamped `0` to `100` range |
| `dbMakeObjectCube` | Basic3D | B | Creates or replaces a cube primitive using a uniform size and stores it in an integer object slot |
| `dbPositionObject` | Basic3D | B | Updates the stored x/y/z position for an existing 3D object slot |
| `dbRotateObject` | Basic3D | B | Updates the stored x/y/z rotation for an existing 3D object slot and applies it during 3D submission |
| `dbPositionCamera` | Basic3D | B | Updates the runtime camera position used for 3D submission |
| `dbPointCamera` | Basic3D | B | Updates the runtime camera target used for 3D submission |
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

## 2D Render Ordering

- Visible sprites are submitted first during `dbSync()`, ordered by ascending sprite slot ID.
- Queued text is submitted after sprites, preserving the order in which `dbText()` was called during the frame.

## 3D Render Ordering

- Visible 3D objects are submitted during `dbSync()` before 2D sprites and text.
- The current runtime camera state is snapshotted once per 3D pass and used for all object draws in that frame.
