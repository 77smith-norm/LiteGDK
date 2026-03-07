# LiteGDK Design Specification

**Status:** Draft 1  
**Project Type:** Open-source educational compatibility SDK  
**Primary Language:** C++20  
**Rendering / Runtime Backend:** `raylib`  
**Build System:** CMake  
**Primary Platforms:** macOS, Windows, Linux  
**Editor / Tooling Target:** Visual Studio Code  
**Testing Requirement:** Catch2-based TDD  

---

## 1. Purpose

LiteGDK is a **DarkGDK-inspired, source-friendly compatibility SDK** for modern C++ development. Its goal is to let learners, hobbyists, and preservation-minded developers compile and run old textbook-style C++ samples with a familiar API shape on modern platforms and toolchains.

LiteGDK is **not** intended to be a perfect historical recreation of DarkGDK, DarkBASIC Professional internals, DirectX 9 behavior, or old Visual Studio project systems. Instead, LiteGDK aims to preserve the **surface programming model** that made DarkGDK educationally valuable:

- global-style procedural functions
- integer-based asset IDs / slots
- an easy “initialize → loop → render/sync” mental model
- simple 2D and basic 3D commands
- low friction for learning and experimentation

The project should optimize for:

1. **Source familiarity first**
2. **Educational usefulness second**
3. **Practical implementation simplicity third**
4. **Broad but honest compatibility over exact emulation**

---

## 2. Vision

### 2.1 Vision Statement

Provide a lightweight, open-source SDK that enables classic DarkGDK-style C++ learning materials to be used on modern systems with modern tooling, while keeping the API approachable, procedural, and fun.

### 2.2 Project Motto

> Old textbook style, modern toolchain.

### 2.3 Design Philosophy

LiteGDK should feel like a **small SDK**, not a full engine framework. Even though it will be implemented on top of `raylib`, users should experience LiteGDK as its own procedural API layer.

This means the public API should:

- look simple and flat
- prefer function calls over object-heavy user code
- preserve integer handles where practical
- minimize required setup
- reduce modern C++ ceremony in the beginner path

Internally, however, the implementation should be modern, modular, and testable.

---

## 3. Scope

## 3.1 In Scope for Initial Design

The initial design targets a **LiteGDK Core** suitable for:

- beginner graphics programming
- old sample preservation
- 2D examples
- simple sprite demos
- text and HUD examples
- keyboard and mouse input
- simple audio playback
- simple camera and basic 3D object examples
- educational “game programming 101” samples

## 3.2 Out of Scope for Initial Implementation

The following areas may be considered later, but are explicitly out of scope for first implementation:

- exact DarkGDK binary or ABI compatibility
- DirectX 9-specific behavior
- old Visual Studio wizard integration
- advanced terrain / matrix systems
- advanced physics
- advanced shader compatibility layers
- multiplayer / networking stacks
- memblock-level full emulation
- industrial game shipping concerns
- editor tooling
- source-to-source conversion tools

## 3.3 Compatibility Stance

LiteGDK is **source-friendly**, not exact. Where feasible, commands should keep the same names and very similar signatures. Where exact compatibility would create unnecessary complexity, LiteGDK may approximate or omit features, provided this is clearly documented.

---

## 4. Product Goals

1. **Compile common textbook-style examples with minimal changes**
2. **Run on macOS in VS Code without legacy IDE requirements**
3. **Be understandable to learners reading the source**
4. **Maintain a clean internal architecture despite legacy-style public APIs**
5. **Support incremental expansion command-family by command-family**
6. **Be test-driven from the beginning using Catch2**

---

## 5. Non-Goals

LiteGDK will not initially try to:

- reproduce every obscure DarkGDK feature
- preserve undocumented edge cases
- emulate old rendering bugs or frame pacing quirks
- maximize raw performance at the expense of clarity
- expose `raylib` directly as the user-facing programming model
- become a production-grade commercial engine

---

## 6. Architectural Overview

LiteGDK will be organized into four layers:

1. **Public Compatibility API Layer**  
   Headers and function declarations exposed to users, centered around `DarkGDK.h` and related compatibility headers.

2. **Facade / Command Layer**  
   Thin translation functions implementing DarkGDK-style commands and delegating to internal services.

3. **Runtime / Service Layer**  
   Centralized systems for asset registries, application state, frame timing, scene state, input snapshots, text rendering, sprite drawing, audio playback, and simple 3D management.

4. **Backend Layer**  
   `raylib` for windowing, rendering, input, textures, sounds, music, camera math, models, and basic collision helpers.

### 6.1 High-Level Flow

```text
User Code
  -> DarkGDK.h commands
  -> LiteGDK command wrappers
  -> LiteGDK runtime services
  -> raylib
  -> OS / GPU / audio
```

### 6.2 Core Principle

Public API functions should be as thin as possible, but not thinner. Logic should move into runtime services so behavior can be unit tested in isolation without requiring a real GPU or window where possible.

---

## 7. Public Header Strategy

## 7.1 Main Public Header

The primary include should be:

```cpp
#include "DarkGDK.h"
```

This header should expose the most important user-facing commands and include subordinate command family headers as needed.

## 7.2 Header Layout Goals

The public headers should:

- preserve familiar command naming
- remain small and readable
- avoid exposing implementation internals
- be easy for old tutorial code to include
- support future splitting by command families

## 7.3 Proposed Public Header Layout

```text
include/
  DarkGDK.h
  LiteGDK/
    Config.h
    Types.h
    Compat.h
    Core.h
    Text.h
    Input.h
    Image.h
    Sprite.h
    Audio.h
    Camera.h
    Basic3D.h
    File.h
    Math.h
```

## 7.4 Public API Style Rules

1. Prefer free functions over user-visible classes
2. Preserve `db` command prefixes where practical
3. Prefer integer resource IDs over handles in the public API
4. Keep argument order source-friendly
5. Avoid templates in the public beginner path
6. Avoid exceptions crossing the public compatibility boundary
7. Use simple scalar return values (`int`, `bool`, `float`, `char*` only if necessary)

## 7.5 Namespace Strategy

There are two viable strategies:

### Option A: Global Function Compatibility

Expose functions exactly as global symbols:

```cpp
void dbSync();
void dbText(int x, int y, const char* text);
```

### Option B: Internal Namespace + Compatibility Forwarding

Define internally under a namespace and export compatibility wrappers:

```cpp
namespace litegdk::compat {
  void dbSync();
}
```

**Recommendation:** use **internal namespaces** in implementation, but expose **global free functions** in public compatibility headers.

That preserves the user experience while keeping internal code organized.

---

## 8. Runtime Model

## 8.1 Central Runtime Object

Internally, LiteGDK should maintain a single process-wide runtime object:

```cpp
namespace litegdk {
  class Runtime;
  Runtime& runtime();
}
```

This runtime owns all mutable state required by the compatibility layer.

## 8.2 Responsibilities of Runtime

The runtime should manage:

- application initialization state
- window configuration
- frame lifecycle state
- global rendering state
- active font/text state
- active drawing colors
- asset registries
- sprite table
- image/texture slots
- sound/music slots
- simple object/model tables
- camera state
- input snapshot state
- timing state
- error / diagnostic state
- configuration flags

## 8.3 Runtime Subsystems

Recommended internal subsystem breakdown:

```text
Runtime
  ├── AppState
  ├── FrameService
  ├── InputService
  ├── TextService
  ├── ImageService
  ├── SpriteService
  ├── AudioService
  ├── CameraService
  ├── Basic3DService
  ├── FileService
  ├── MathService
  ├── DiagnosticsService
  └── ConfigService
```

Each service should expose focused interfaces and avoid directly depending on unrelated systems.

## 8.4 Lifetime Model

LiteGDK should follow a single-runtime process model:

- initialize runtime lazily or explicitly
- create window once
- run user loop
- shut down gracefully
- release all assets on exit

Since textbook-style code often assumes “global SDK state,” this process-global model is appropriate.

## 8.5 Initialization Modes

Two compatible initialization patterns should be supported.

### Explicit Initialization

```cpp
int main() {
  dbSyncOn();
  dbSetDisplayMode(800, 600, 32);
  while (LoopGDK()) {
    dbSync();
  }
}
```

### Lazy Initialization

Commands that require the runtime may initialize default state if not yet initialized. This must be carefully controlled to avoid surprising behavior.

**Recommendation:** support limited lazy initialization internally, but document explicit initialization as the preferred model.

---

## 9. Frame and Sync Model

## 9.1 Background

DarkGDK-style code commonly uses a central loop and a sync/update rhythm. LiteGDK must preserve this structure even though the underlying backend is `raylib`.

## 9.2 Proposed Loop Contract

```cpp
while (LoopGDK()) {
  // update / draw commands
  dbSync();
}
```

## 9.3 Responsibilities of `LoopGDK()`

`LoopGDK()` should:

- ensure runtime is initialized
- check if the window remains open
- prepare per-frame state
- return `true` while the application should continue
- return `false` when shutdown is requested

## 9.4 Responsibilities of `dbSync()`

`dbSync()` should:

- flush queued draw operations for the frame
- finalize frame rendering
- update input snapshots
- advance timing/frame counters
- maintain frame pacing if sync rate is configured

## 9.5 Immediate vs Deferred Rendering

LiteGDK should adopt a **hybrid frame model**:

- commands may update persistent scene/sprite state immediately
- actual draw submission occurs during the frame render phase
- text and immediate draw commands may be queued or applied to a draw list

This gives LiteGDK a stable place to validate ordering while keeping user code simple.

## 9.6 Draw List

The frame service should maintain a draw list for the current frame, containing:

- text draw calls
- sprite draw calls
- simple shapes
- debug overlays
- 3D draw commands where appropriate

Persistent entities like sprites or basic 3D objects may also be stored as live runtime objects and rendered each frame according to visibility flags.

---

## 10. Resource and Slot Model

## 10.1 Design Goal

Old DarkGDK-style code relies heavily on integer IDs. LiteGDK should preserve this because it is central to source compatibility and the educational feel.

## 10.2 Resource Registries

Each command family should maintain its own typed registry.

### Proposed Registries

- Image registry: `imageId -> ImageAsset`
- Texture registry: `imageId -> TextureAsset` or image-backed texture asset
- Sprite registry: `spriteId -> SpriteEntity`
- Sound registry: `soundId -> SoundAsset`
- Music registry: `musicId -> MusicAsset`
- Font registry: `fontId -> FontAsset` (optional in first phase)
- Model registry: `objectId -> ModelEntity`
- Camera registry: usually one active camera for Core, expandable later

## 10.3 Registry Behavior

Registries should support:

- create / load into ID
- replace existing slot
- existence checks
- clear / delete slot
- iterate visible objects for rendering
- deterministic invalid-ID behavior

## 10.4 Slot Semantics

Slots are user-owned integer identifiers. LiteGDK should not auto-renumber them. If code loads image `1`, then image `1` should remain the identity used throughout the program.

## 10.5 Invalid Slot Policy

Commands given invalid IDs should:

- fail safely
- not crash
- optionally record diagnostics in debug builds
- return simple failure values where the API allows it

This is important for educational robustness.

---

## 11. Command Families

The public API will be grouped into command families. Each family should have its own internal service, public header, tests, and compatibility matrix.

## 11.1 Core Commands

### Purpose
Application lifecycle, frame pacing, window management, timing, and global settings.

### Example Commands

- `dbSyncOn()`
- `dbSyncRate(int rate)`
- `dbSync()`
- `LoopGDK()`
- `dbSetDisplayMode(int width, int height, int depth)`
- `dbCLS()`
- `dbInk(int foreground, int background)`
- `dbRGB(int r, int g, int b)`
- `dbScreenWidth()`
- `dbScreenHeight()`
- `dbTimer()`
- `dbWait(int ms)`

### Notes
This family is foundational and should be implemented first.

## 11.2 Text Commands

### Purpose
Draw basic text and support simple screen-based educational examples.

### Example Commands

- `dbText(int x, int y, const char* text)`
- `dbCenterText(int x, int y, const char* text)`
- `dbSetTextSize(int size)`
- `dbSetTextFont(const char* name)`
- `dbTextWidth(const char* text)`
- `dbTextHeight(const char* text)`

### Notes
Text rendering behavior can be approximate. Pixel-perfect compatibility is not required.

## 11.3 Input Commands

### Purpose
Expose keyboard and mouse input with simple polling functions.

### Example Commands

- `dbUpKey()`
- `dbDownKey()`
- `dbLeftKey()`
- `dbRightKey()`
- `dbSpaceKey()`
- `dbEscapeKey()`
- `dbReturnKey()`
- `dbMouseX()`
- `dbMouseY()`
- `dbMouseClick()`

### Notes
The input service should snapshot state once per frame so commands have deterministic values within a frame.

## 11.4 Image Commands

### Purpose
Load and manage 2D bitmap assets.

### Example Commands

- `dbLoadImage(const char* filename, int imageId)`
- `dbDeleteImage(int imageId)`
- `dbImageExist(int imageId)`
- `dbGetImageWidth(int imageId)`
- `dbGetImageHeight(int imageId)`

### Notes
Images should typically load into textures usable by sprites.

## 11.5 Sprite Commands

### Purpose
Manage 2D sprite entities as positioned objects tied to image IDs.

### Example Commands

- `dbSprite(int spriteId, int x, int y, int imageId)`
- `dbDeleteSprite(int spriteId)`
- `dbHideSprite(int spriteId)`
- `dbShowSprite(int spriteId)`
- `dbMoveSprite(int spriteId, float step)`
- `dbXSprite(int spriteId, int x)`
- `dbYSprite(int spriteId, int y)`
- `dbRotateSprite(int spriteId, float angle)`
- `dbScaleSprite(int spriteId, float scale)`
- `dbSpriteExist(int spriteId)`
- `dbSpriteCollision(int a, int b)`

### Notes
Sprite commands are a top educational priority and should be part of the first shippable milestone.

## 11.6 Audio Commands

### Purpose
Play simple sound effects and music.

### Example Commands

- `dbLoadSound(const char* filename, int soundId)`
- `dbPlaySound(int soundId)`
- `dbStopSound(int soundId)`
- `dbDeleteSound(int soundId)`
- `dbLoadMusic(const char* filename, int musicId)`
- `dbPlayMusic(int musicId)`
- `dbStopMusic(int musicId)`

### Notes
Music streaming may need a per-frame update hook integrated into `dbSync()`.

## 11.7 Camera Commands

### Purpose
Provide a simple camera abstraction for basic 3D educational examples.

### Example Commands

- `dbPositionCamera(float x, float y, float z)`
- `dbPointCamera(float x, float y, float z)`
- `dbMoveCamera(float step)`
- `dbTurnCameraLeft(float angle)`
- `dbTurnCameraRight(float angle)`
- `dbPitchCameraUp(float angle)`
- `dbPitchCameraDown(float angle)`

### Notes
Initially, a single active camera is sufficient.

## 11.8 Basic 3D Object Commands

### Purpose
Support simple object placement and rendering for early 3D learning material.

### Example Commands

- `dbMakeObjectCube(int objectId, float size)`
- `dbMakeObjectSphere(int objectId, float radius)`
- `dbPositionObject(int objectId, float x, float y, float z)`
- `dbRotateObject(int objectId, float x, float y, float z)`
- `dbScaleObject(int objectId, float x, float y, float z)`
- `dbColorObject(int objectId, int rgb)`
- `dbHideObject(int objectId)`
- `dbShowObject(int objectId)`
- `dbDeleteObject(int objectId)`
- `dbObjectExist(int objectId)`

### Notes
The initial implementation can focus on primitive objects and defer complex mesh loading.

## 11.9 File / Utility Commands

### Purpose
Support basic file existence checks and educational utility workflows.

### Example Commands

- `dbFileExist(const char* filename)`
- `dbPathExist(const char* path)`
- `dbDeleteFile(const char* filename)`
- `dbCurrentDir()`

### Notes
This family should remain small initially.

## 11.10 Math / Utility Commands

### Purpose
Preserve helpful procedural helpers common in older APIs.

### Example Commands

- `dbRnd(int max)`
- `dbSqrt(float value)`
- `dbSin(float degrees)`
- `dbCos(float degrees)`
- `dbWrapValue(float value)`

### Notes
These functions are simple and useful in beginner materials.

---

## 12. Compatibility Tiers

LiteGDK should explicitly classify every command by compatibility tier.

## 12.1 Tier Definitions

### Tier 1 — Exact-ish Surface Compatibility

- same or nearly same name
- same general parameters
- same basic behavior
- expected to work for common textbook usage

### Tier 2 — Compatible Approximation

- same public command name
- behavior close enough for educational usage
- implementation details differ significantly
- non-critical quirks may differ

### Tier 3 — Partial / Constrained Support

- command exists
- only a subset of behavior is implemented
- edge cases or advanced modes unsupported

### Tier 4 — Stub / Planned

- command declared or documented
- may compile, but not provide real behavior yet
- primarily a roadmap marker

### Tier 5 — Unsupported

- intentionally omitted from current scope
- documented as unsupported

## 12.2 Compatibility Matrix Requirement

Every command family should have a generated or maintained compatibility matrix documenting:

- command name
- status tier
- notes
- known deviations
- tests present
- examples covered

Example:

```text
Command             Tier   Notes
---------------------------------------------
dbLoadImage         1      Core behavior supported
dbSprite            1      Basic behavior supported
dbRotateSprite      2      Rotation pivot differs slightly
dbText              2      Font metrics approximate
dbMakeMatrix        5      Not in LiteGDK Core
```

---

## 13. Error Handling and Diagnostics

## 13.1 Public Error Strategy

Public commands should not throw exceptions across the compatibility boundary. Instead, they should:

- succeed silently where legacy behavior tolerated it
- return `0` / `false` where the API already supports status
- no-op safely on invalid resource IDs where appropriate

## 13.2 Internal Error Strategy

Internally, the codebase may use exceptions sparingly or prefer explicit result types. The key requirement is that the public compatibility layer remain simple and robust.

## 13.3 Diagnostics System

A diagnostics service should capture:

- invalid slot usage
- file load failures
- unsupported command usage
- failed preconditions
- initialization warnings

In debug builds, diagnostics may be routed to:

- stderr
- a simple in-memory log
- optional debug overlay

---

## 14. Rendering Model

## 14.1 2D Rendering

2D rendering should be driven by sprite and text services with support for:

- clear screen
- text draw order
- sprite draw order
- optional z/order field for sprites
- color tinting where practical

## 14.2 3D Rendering

Basic 3D should support:

- single active camera
- drawing primitive models
- object transforms
- simple colors/material defaults
- optional grid or debug rendering in development builds

## 14.3 Ordering Rules

At minimum, rendering should follow:

1. frame clear
2. 3D scene rendering if active
3. 2D sprite rendering
4. text / HUD rendering
5. diagnostics overlay if enabled

## 14.4 Color Model

A shared utility should convert old integer RGB-style values into backend colors. This is needed for commands like `dbInk()` and `dbColorObject()`.

---

## 15. Input Model

## 15.1 Snapshot Semantics

Input should be sampled once per frame and exposed consistently during that frame. This prevents odd inconsistencies when multiple polling commands are used.

## 15.2 Keyboard Mapping

A compatibility mapping table should translate DarkGDK-style key commands into backend key constants.

## 15.3 Mouse Support

Mouse commands should expose:

- current x/y position
- button pressed state
- click / edge-trigger semantics if needed later

---

## 16. Audio Model

## 16.1 Sound Effects

Sound assets should be short loaded clips mapped by integer ID.

## 16.2 Music

Music assets may require streaming lifecycle management. The audio service should expose an update method called each frame by the frame service.

## 16.3 Simplicity Rule

Audio implementation should favor obvious, robust behavior over exact historical semantics.

---

## 17. State Model for Sprites and Objects

## 17.1 Sprite Entity

A sprite entity should minimally store:

- sprite ID
- image ID / texture reference
- position
- visibility
- rotation
- scale
- tint/color
- optional velocity / direction fields
- collision bounds
- layer/order

## 17.2 Basic 3D Object Entity

A 3D object entity should minimally store:

- object ID
- primitive/model type
- transform
- visibility
- base color
- optional texture/material reference

## 17.3 Separation of Concerns

Entities should be plain runtime state objects. Rendering logic belongs in render-oriented services, not in entity structs themselves.

---

## 18. Testing Strategy

## 18.1 Testing Requirement

LiteGDK must be implemented with **Catch2 TDD as a first-class project rule**.

Every new command family should begin with tests for:

- happy path behavior
- invalid ID behavior
- replacement / delete semantics
- frame lifecycle expectations
- compatibility deviations where documented

## 18.2 Test Pyramid

### Unit Tests

High priority. These should cover:

- registries
- services
- ID lifecycle behavior
- command argument handling
- state transitions
- math utilities
- diagnostics behavior

### Integration Tests

Moderate priority. These should cover:

- loading and using images with sprites
- input polling lifecycle
- frame update and sync behavior
- camera + object rendering setup

### Smoke / Example Tests

High priority for educational value. These should compile or run representative samples derived from textbook-style programs.

## 18.3 Testability Requirements

To support TDD, runtime services should be separated from direct backend calls where practical. For example:

- registry logic should be pure C++
- validation logic should be pure C++
- file path normalization should be pure C++
- draw planning can be tested without requiring a real window

A thin adapter layer should isolate direct `raylib` calls.

## 18.4 Rendering Test Strategy

Since graphical assertions are harder, the initial approach should emphasize:

- state verification before draw
- command sequencing correctness
- entity visibility and transforms
- backend call contracts through abstractions / adapters

Pixel-perfect screenshot tests can be considered later but are not required initially.

---

## 19. Build and Tooling Architecture

## 19.1 Build System

Use CMake with clear targets for:

- library
- tests
- examples
- docs generation helpers if needed

## 19.2 Proposed CMake Targets

```text
ltegdk              # main library
ltegdk_tests        # Catch2 test binary
ltegdk_examples     # sample programs (optional grouped target)
```

## 19.3 Dependency Strategy

Primary dependencies:

- `raylib`
- `Catch2`

Optional later:

- formatting / linting tools
- doc generation tools

## 19.4 Platform Goals

The first-class developer experience should be:

- buildable on macOS
- runnable from VS Code
- cross-platform by design

---

## 20. First-Pass Repository Layout

```text
LiteGDK/
  README.md
  LICENSE
  CMakeLists.txt
  cmake/
    Dependencies.cmake
    Warnings.cmake
    Sanitizers.cmake
  docs/
    design/
      LiteGDK_Design_Specification.md
    compatibility/
      core.md
      text.md
      image.md
      sprite.md
      audio.md
      camera.md
      basic3d.md
  include/
    DarkGDK.h
    LiteGDK/
      Config.h
      Types.h
      Compat.h
      Core.h
      Text.h
      Input.h
      Image.h
      Sprite.h
      Audio.h
      Camera.h
      Basic3D.h
      File.h
      Math.h
  src/
    compat/
      DarkGDK.cpp
      CoreCommands.cpp
      TextCommands.cpp
      InputCommands.cpp
      ImageCommands.cpp
      SpriteCommands.cpp
      AudioCommands.cpp
      CameraCommands.cpp
      Basic3DCommands.cpp
      FileCommands.cpp
      MathCommands.cpp
    runtime/
      Runtime.cpp
      AppState.cpp
      FrameService.cpp
      InputService.cpp
      TextService.cpp
      ImageService.cpp
      SpriteService.cpp
      AudioService.cpp
      CameraService.cpp
      Basic3DService.cpp
      FileService.cpp
      MathService.cpp
      DiagnosticsService.cpp
    backend/
      RaylibApp.cpp
      RaylibRender.cpp
      RaylibInput.cpp
      RaylibAudio.cpp
      RaylibAssets.cpp
    util/
      Color.cpp
      Paths.cpp
      Strings.cpp
      IdRegistry.cpp
  tests/
    unit/
      runtime/
      services/
      util/
      compat/
    integration/
      core/
      sprite/
      audio/
      camera/
      basic3d/
    fixtures/
      assets/
      samples/
  examples/
    textbook/
      sprites/
      input/
      simple3d/
    minimal/
      hello_window/
      hello_sprite/
      hello_text/
  .github/
    workflows/
      ci.yml
  .vscode/
    tasks.json
    launch.json
    settings.json
```

---

## 21. Internal Code Organization Rules

1. Public headers must not expose backend-specific details unnecessarily
2. Compatibility commands should remain thin
3. Runtime services should be testable independently
4. Backend adapter code should be isolated in one layer
5. New command families require tests before or alongside implementation
6. Each command family should have a compatibility notes document

---

## 22. Suggested Implementation Phases

## Phase 0 — Project Skeleton

Deliver:

- repository structure
- CMake baseline
- dependency wiring for `raylib` and Catch2
- empty runtime shell
- first CI pipeline
- formatting / warning baseline

## Phase 1 — Core Runtime

Deliver:

- runtime singleton
- frame service
- initialization and shutdown
- `LoopGDK()`
- `dbSync()`
- `dbSetDisplayMode()`
- `dbCLS()`
- screen size helpers
- timer utilities

## Phase 2 — Text and Input

Deliver:

- text draw commands
- text metrics basics
- keyboard polling
- mouse polling
- compatibility docs for Core + Text + Input

## Phase 3 — Images and Sprites

Deliver:

- image loading / deletion / existence
- sprite creation / movement / visibility / collision basics
- first textbook-style sample suite

## Phase 4 — Audio

Deliver:

- sound loading / playback
- music loading / playback / stop / update hooks
- smoke tests with fixture assets

## Phase 5 — Camera and Basic 3D

Deliver:

- active camera support
- primitive objects
- object transforms
- simple camera movement / pointing
- basic 3D sample programs

## Phase 6 — Expansion and Gaps

Deliver:

- more utility commands
- better compatibility coverage
- prioritized command backlog from old sample material

---

## 23. Example API Shape

The public API should remain simple:

```cpp
#include "DarkGDK.h"

int main() {
    dbSetDisplayMode(800, 600, 32);
    dbSyncOn();
    dbSyncRate(60);

    dbLoadImage("player.png", 1);
    dbSprite(1, 100, 100, 1);

    while (LoopGDK()) {
        if (dbRightKey()) {
            dbXSprite(1, dbSpriteX(1) + 2);
        }

        dbCLS();
        dbText(10, 10, "LiteGDK");
        dbSync();
    }
}
```

Internally, this should translate into controlled runtime operations and backend calls, not direct global chaos.

---

## 24. Risks

## 24.1 API Creep

Risk: attempting too many command families too early.  
Mitigation: prioritize educational Core and use compatibility tiers.

## 24.2 Hidden Legacy Semantics

Risk: some old samples may rely on undocumented behavior.  
Mitigation: treat representative sample programs as behavioral tests and document deviations.

## 24.3 Over-Coupling to raylib

Risk: public API leaks backend assumptions.  
Mitigation: isolate backend logic behind adapters and keep the public API compatibility-first.

## 24.4 Untestable Rendering Logic

Risk: too much behavior lands in direct draw code.  
Mitigation: keep registries, command interpretation, and draw planning testable without GPU dependency.

---

## 25. Open Questions

1. Should LiteGDK expose a tiny `LiteGDK.h` alongside `DarkGDK.h` for new code, or only `DarkGDK.h` initially?
2. Should unsupported commands compile as stubs early, or only be added once behavior exists?
3. How much of the old string-returning utility surface should be preserved versus modernized internally?
4. Should sample preservation include literal textbook rewrites as fixtures in the repo?
5. Should there be a debug command to print compatibility warnings at runtime?

---

## 26. Initial Recommendations

1. Start with **source-friendly global functions**
2. Keep the internal implementation **strictly layered**
3. Build the **runtime, registries, and tests first**
4. Focus early milestones on **Core + Text + Input + Images + Sprites**
5. Use **representative textbook examples** as integration criteria
6. Maintain a visible **compatibility matrix** from the first milestone
7. Require **Catch2 tests** for every command family added

---

## 27. Definition of Architectural Success

The architecture is successful if, by the end of the early milestones:

- old-style sample code feels natural to write
- the public API is simple and stable
- runtime internals remain modular and testable
- new command families can be added without rewriting the system
- the codebase stays understandable to contributors
- compatibility limitations are explicit, not surprising

---

## 28. Summary

LiteGDK should be built as a **modern internal runtime with a deliberately old-school procedural surface**. `raylib` is the right foundation because it aligns with the project’s educational goals, small-SDK feel, and simple 2D / basic 3D needs.

The core architectural idea is straightforward:

- keep the user-facing API familiar
- isolate legacy-style commands in a facade layer
- centralize state in a runtime object
- use typed registries behind integer IDs
- make each command family expandable
- enforce Catch2 TDD from the start

This design gives LiteGDK the best chance of being both approachable for learners and maintainable for contributors.
