# Compatibility Matrix

This matrix describes the LiteGDK `preview-0.1` public surface as of
March 7, 2026.

See also: `docs/compatibility/smoke-samples.md`

## Tier definitions

- `A`: source-friendly and behaviorally aligned for intended educational use
- `B`: supported with small behavioral differences or limited edge-case coverage
- `C`: approximate or intentionally narrow support with documented limitations
- `X`: not implemented in `preview-0.1`

## Family summary

| Family | Tier | Notes |
| --- | --- | --- |
| Core | C | The explicit loop and `dbSync()` path works, but `dbSyncOn`, `dbSyncOff`, and `dbCLS` remain approximate compared to historical DarkGDK behavior |
| System | B | Screen size, timer, and random helpers are implemented and tested; timer semantics are modern monotonic milliseconds rather than historical exact-match behavior |
| Text | C | Queued text rendering works reliably, but the preview uses the backend default font at fixed size `20` and stores rather than draws background ink |
| Input | B | Directional keys, `Space`, `Escape`, `Return`, mouse position, and basic mouse-button state are supported; generic key queries remain intentionally narrow |
| Images | B | Image loading plus existence and dimension queries are implemented; broader image lifecycle and manipulation commands are not part of this preview |
| Sprites | B | Basic sprite creation, visibility, position helpers, and deterministic 2D ordering are implemented; rotation, scaling, and collision helpers are still absent |
| Sound | B | Sound and music loading, playback control, pause/resume, and volume are implemented; status queries, channels, and looping helpers are still absent |
| Basic3D | B | Simple camera targeting and cube submission work for educational samples; the preview does not yet cover the broader DarkGDK 3D object and camera surface |

## Command support

| Family | Command | Tier | Notes |
| --- | --- | --- | --- |
| Core | `dbSyncOn` | C | Stores the sync-enabled flag, but the current preview still relies on explicit `dbSync()` submission instead of a separate auto-present mode |
| Core | `dbSyncOff` | C | Updates runtime state, but does not currently switch the engine into a historical unsynchronized draw model |
| Core | `dbSyncRate` | B | Stores the requested frame rate and passes it to the backend when supported |
| Core | `dbSync` | B | Advances the deterministic frame lifecycle and submits implemented 2D, audio, and 3D work for the frame |
| Core | `LoopGDK` | B | Starts a frame and exits cleanly when the backend reports close or the runtime requests shutdown |
| Core | `dbSetDisplayMode` | B | Applies width and height, while the `depth` argument is accepted for compatibility but not used by the current backend |
| Core | `dbCLS` | C | Requests a clear, but the preview backend currently clears at frame begin regardless of whether `dbCLS()` was called |
| System | `dbScreenWidth` | A | Returns the current configured display width |
| System | `dbScreenHeight` | A | Returns the current configured display height |
| System | `dbTimer` | B | Returns monotonic milliseconds from the LiteGDK process lifetime |
| System | `dbRandomize` | A | Reseeds the deterministic random helper used by educational samples |
| System | `dbRnd` | A | Returns an inclusive random integer in the `0..max` range, or `0` for non-positive input |
| Text | `dbText` | B | Queues 2D text and renders it during `dbSync()` with the backend default font at fixed size `20` |
| Text | `dbInk` | C | Updates foreground and background text colors, but only the foreground color currently affects drawing |
| Input | `dbUpKey` | A | Returns whether the mapped Up key is down in the captured snapshot |
| Input | `dbDownKey` | A | Returns whether the mapped Down key is down in the captured snapshot |
| Input | `dbLeftKey` | A | Returns whether the mapped Left key is down in the captured snapshot |
| Input | `dbRightKey` | A | Returns whether the mapped Right key is down in the captured snapshot |
| Input | `dbSpaceKey` | A | Returns whether the mapped Space key is down in the captured snapshot |
| Input | `dbEscapeKey` | A | Returns whether the mapped Escape key is down in the captured snapshot |
| Input | `dbReturnKey` | A | Returns whether the mapped Return key is down in the captured snapshot |
| Input | `dbKeyState` | C | Supports the current educational key subset only: `Up`, `Down`, `Left`, `Right`, `Space`, `Escape`, and `Return` |
| Input | `dbMouseX` | A | Returns the captured mouse x-position |
| Input | `dbMouseY` | A | Returns the captured mouse y-position |
| Input | `dbMouseClick` | C | Reports only current button-down state as `1` for left, `2` for right, or `0` for neither |
| Images | `dbLoadImage` | B | Loads an image into an integer slot, records metadata, and emits diagnostics for invalid handles or missing files |
| Images | `dbImageExist` | A | Returns whether an image slot currently exists |
| Images | `dbGetImageWidth` | A | Returns the stored width for a loaded image, or `0` for missing slots |
| Images | `dbGetImageHeight` | A | Returns the stored height for a loaded image, or `0` for missing slots |
| Sprites | `dbSprite` | B | Creates or replaces a sprite bound to a loaded image slot and renders it during `dbSync()` |
| Sprites | `dbDeleteSprite` | A | Removes a sprite slot when it exists |
| Sprites | `dbHideSprite` | A | Marks a stored sprite invisible without deleting it |
| Sprites | `dbShowSprite` | A | Marks a stored sprite visible again |
| Sprites | `dbXSprite` | B | Updates a stored sprite's x-position for subsequent draws |
| Sprites | `dbYSprite` | B | Updates a stored sprite's y-position for subsequent draws |
| Sprites | `dbSpriteExist` | A | Returns whether a sprite slot currently exists |
| Sound | `dbLoadSound` | B | Loads a sound into an integer slot, replacing prior contents and emitting diagnostics for invalid handles or missing files |
| Sound | `dbDeleteSound` | A | Removes a loaded sound slot and unloads it from the backend when present |
| Sound | `dbPlaySound` | B | Starts playback for a loaded sound slot |
| Sound | `dbStopSound` | B | Stops playback for a loaded sound slot |
| Sound | `dbSetSoundVolume` | B | Clamps the public `0..100` range and forwards normalized volume to the backend |
| Sound | `dbLoadMusic` | B | Loads a music stream into an integer slot, replacing prior contents and emitting diagnostics for invalid handles or missing files |
| Sound | `dbDeleteMusic` | A | Removes a loaded music slot and unloads it from the backend when present |
| Sound | `dbPlayMusic` | B | Starts playback for a loaded music slot |
| Sound | `dbStopMusic` | B | Stops playback for a loaded music slot |
| Sound | `dbPauseMusic` | B | Pauses a loaded music slot |
| Sound | `dbResumeMusic` | B | Resumes a paused music slot |
| Sound | `dbSetMusicVolume` | B | Clamps the public `0..100` range and forwards normalized volume to the backend |
| Basic3D | `dbMakeObjectCube` | B | Creates or replaces a cube primitive in an integer object slot |
| Basic3D | `dbPositionObject` | B | Updates the stored x, y, and z position for an existing object slot |
| Basic3D | `dbRotateObject` | B | Updates the stored x, y, and z rotation for an existing object slot |
| Basic3D | `dbPositionCamera` | B | Updates the runtime camera position used during 3D submission |
| Basic3D | `dbPointCamera` | B | Updates the runtime camera target used during 3D submission |

## Render ordering guarantees

- Visible 3D objects are submitted first during `dbSync()`.
- Visible sprites are submitted next, ordered by ascending sprite slot ID.
- Queued text is submitted last, preserving the order in which `dbText()` was called during the frame.
