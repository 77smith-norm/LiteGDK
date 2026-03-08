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
| Input | X | Not yet implemented |
| Images | C | Image loading, existence, and size queries are implemented; deletion and advanced image manipulation are still pending |
| Sprites | X | Not yet implemented |
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
