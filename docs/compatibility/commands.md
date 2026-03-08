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
| Images | X | Not yet implemented |
| Sprites | X | Not yet implemented |
| Sound | X | Not yet implemented |
| Basic3D | X | Not yet implemented |

## Commands

| Command | Family | Tier | Notes |
| --- | --- | --- | --- |
| `dbText` | Text | B | Draws queued 2D text during `dbSync()` using the backend default font at fixed size `20` |
