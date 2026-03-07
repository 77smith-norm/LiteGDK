# LiteGDK Product Requirements Document (PRD)

**Status:** Draft 1  
**Project Name:** LiteGDK  
**Project Type:** Open-source educational compatibility SDK  
**Primary Language:** C++20  
**Primary Backend:** `raylib`  
**Build System:** CMake  
**Primary Editors / Tooling:** Visual Studio Code, CLI toolchains  
**Primary Platforms:** macOS, Windows, Linux  
**Testing Requirement:** Catch2-based TDD is mandatory

---

## 1. Executive Summary

LiteGDK is an education-first, open-source, DarkGDK-inspired compatibility SDK built on top of `raylib`. Its purpose is to let learners and hobbyists use classic textbook-style, procedural C++ game-programming samples on modern systems and toolchains without depending on legacy Windows-only IDE workflows, DirectX 9, or historical TheGameCreators runtimes.

LiteGDK will prioritize **source-friendly compatibility** for common learning material, not exact historical recreation. The public SDK should preserve the familiar DarkGDK-style mental model:

- `#include "DarkGDK.h"`
- `db`-prefixed procedural functions
- integer asset identifiers
- simple setup / loop / sync flow
- low-friction 2D and simple 3D programming

Internally, LiteGDK must be modern, modular, and testable. It should be implemented with explicit architectural boundaries and strict Catch2-driven TDD from the start.

---

## 2. Problem Statement

Old DarkGDK-era learning material is still useful because it teaches game programming with a direct, approachable procedural API. However, the original ecosystem is constrained by outdated assumptions:

- old Windows-first development workflows
- legacy Visual Studio integration
- DirectX 9-era rendering assumptions
- closed / abandoned / hard-to-maintain tooling expectations
- poor fit for macOS and modern cross-platform development

The result is that learners who want to study or preserve these materials cannot easily do so with modern open-source tools.

LiteGDK solves this by providing a modern compatibility SDK that keeps the programming model approachable while replacing the runtime foundation with a lightweight, cross-platform backend.

---

## 3. Product Vision

### 3.1 Vision Statement

Provide a lightweight, open-source SDK that enables classic DarkGDK-style C++ educational samples to run on modern systems with modern tools while preserving a clean, procedural, beginner-friendly experience.

### 3.2 Product Motto

> Old textbook style, modern toolchain.

### 3.3 Product Positioning

LiteGDK is **not** a full engine and **not** a production-shipping framework. It is a compatibility-oriented educational SDK optimized for:

- learning
- experimentation
- sample preservation
- small projects
- cross-platform classroom / hobby use

---

## 4. Goals

### 4.1 Primary Goals

1. Enable common DarkGDK-style educational C++ samples to compile with minimal or no source changes.
2. Make textbook-style game programming approachable on modern macOS, Windows, and Linux systems.
3. Preserve the simple procedural programming feel that made DarkGDK educationally effective.
4. Keep the implementation modular and testable despite the legacy-style public API.
5. Support incremental delivery by command family.
6. Require Catch2-based TDD for runtime services, command translation logic, and compatibility behavior.

### 4.2 Secondary Goals

1. Publish honest compatibility tiers so users know which commands are exact, approximate, or unsupported.
2. Make the codebase accessible to contributors through clear repo structure and architectural separation.
3. Favor deterministic, reproducible builds via CMake.
4. Allow the project to expand gradually into more advanced APIs without destabilizing Core.

---

## 5. Non-Goals

LiteGDK will not initially attempt to:

- achieve 100% DarkGDK compatibility
- recreate DirectX 9 rendering behavior
- preserve undocumented quirks or timing bugs
- emulate historical IDE integration or wizards
- provide production-grade performance tuning
- ship a scene editor or IDE
- replace modern full engines
- support all advanced terrain, matrix, memblock, or networking APIs in the first implementation
- guarantee binary compatibility with historical DarkGDK libraries

---

## 6. Target Users

### 6.1 Primary Users

- learners using old C++ game-programming books or tutorials
- hobbyists who want a simple procedural API
- preservation-minded developers reviving legacy educational samples
- developers teaching introductory graphics / game programming

### 6.2 Secondary Users

- contributors interested in educational SDKs
- developers who want a lightweight retro-style C++ API on modern platforms
- maintainers porting small DarkGDK-era examples

### 6.3 User Characteristics

Users are likely to value:

- simplicity over engine depth
- familiar command names over modern abstraction purity
- straightforward build instructions
- examples and documentation
- predictable behavior and honest limitations

---

## 7. Product Principles

1. **Source-friendly first**  
   Preserve function names, argument shapes, and old sample flow whenever reasonable.

2. **Education over completeness**  
   Prioritize commands actually used in beginner materials.

3. **Simple public API, disciplined internals**  
   Users should see a small SDK; maintainers should see a modular architecture.

4. **Compatibility honesty**  
   Unsupported or approximate behavior must be documented clearly.

5. **TDD as a hard requirement**  
   New behavior should be specified through tests first, especially command translation and runtime state transitions.

6. **Cross-platform by default**  
   macOS must be a first-class development target, not an afterthought.

---

## 8. Functional Scope

### 8.1 Core MVP Scope

The initial MVP should include the minimum features necessary to support educational samples in the following areas:

- application init / shutdown
- window lifecycle
- frame loop / sync model
- basic timing
- text drawing
- keyboard input
- mouse input
- image loading
- sprite creation and drawing
- basic sprite movement support
- sound and music playback basics
- random / math helpers needed by samples
- simple camera setup
- simple 3D object display and transform helpers

### 8.2 Post-MVP Expansion Scope

Potential later areas:

- additional shape drawing commands
- more 3D primitives and object controls
- camera refinement
- collision helpers
- file commands
- color / ink state commands
- animation helpers
- lightweight world / terrain approximations
- more compatibility aliases

### 8.3 Explicitly Deferred Areas

- advanced terrain / matrix emulation
- full memblock compatibility
- advanced networking / multiplayer APIs
- advanced shader APIs
- industrial packaging and deployment workflows
- advanced editor or asset pipeline tooling

---

## 9. User Experience Requirements

### 9.1 Public SDK Experience

The user should be able to write code like:

```cpp
#include "DarkGDK.h"

void DarkGDK() {
    dbSyncOn();
    dbLoadImage("player.png", 1);
    while (LoopGDK()) {
        dbCLS();
        dbSprite(1, 100, 100, 1);
        dbText(10, 10, "Hello LiteGDK");
        dbSync();
    }
}
```

The exact shape of support may vary, but the user experience must preserve:

- a single main compatibility header
- procedural `db`-style commands
- integer asset IDs
- loop-driven beginner code
- low required setup

### 9.2 Documentation Expectations

The project must include:

- a quick start
- platform build instructions
- example programs
- a compatibility matrix
- command-family documentation
- testing and contribution guidance

---

## 10. Architecture Requirements

### 10.1 Required Architectural Layers

LiteGDK must be organized into these layers:

1. **Public API Layer**  
   `DarkGDK.h` and related public compatibility headers.

2. **Command / Facade Layer**  
   Thin `db*` function implementations that translate public calls into runtime operations.

3. **Runtime / Service Layer**  
   Application state, registries, render orchestration, input state, timing, audio state, and 3D state.

4. **Backend Layer**  
   `raylib` integration for windowing, drawing, input, textures, models, audio, and camera primitives.

### 10.2 Runtime Requirements

The runtime must provide:

- a centralized runtime state object
- deterministic asset registries keyed by integer IDs
- clear ownership for textures, images, sounds, music, sprites, and models
- window and frame-loop state
- draw-state tracking where needed for compatibility
- minimal hidden coupling between command families

### 10.3 Public API Requirements

The public API should:

- expose global free functions for compatibility
- avoid exposing internal runtime types
- avoid exceptions across public boundaries
- use stable, simple scalar-friendly signatures where practical
- preserve familiar names and argument ordering when feasible

### 10.4 Modularity Requirements

Command families must be implemented in separate modules so they can be developed, tested, and expanded independently.

---

## 11. Command Family Requirements

### 11.1 Core

Must include:

- startup / initialization behavior
- frame begin / end / sync behavior
- screen clear / present control
- exit / loop management
- timing basics

### 11.2 Text

Must include:

- drawing text at screen positions
- simple text formatting behavior where practical
- support for string literals and basic `const char*` inputs

### 11.3 Input

Must include:

- keyboard state queries
- mouse position and button queries
- polling semantics suitable for textbook loops

### 11.4 Images / Sprites

Must include:

- load image into integer slot
- create / draw sprite by slot and image ID
- set sprite position
- show / hide sprite behavior if included in scope
- simple sprite collision helpers as a stretch goal

### 11.5 Audio

Must include:

- load sound / music commands for common beginner cases
- play / stop commands
- a simple lifecycle model

### 11.6 Camera / Basic 3D

Must include:

- initialize basic 3D scene context
- simple camera positioning and targeting
- basic 3D object display using simple primitives or model-backed objects
- transform helpers sufficient for simple educational examples

### 11.7 Compatibility Aliases

The system may include aliases or overload sets where needed to improve compatibility with old samples, as long as maintainability remains acceptable.

---

## 12. Compatibility Model

LiteGDK must define and publish command compatibility using explicit tiers.

### 12.1 Tier Definitions

- **Tier A — Source-Compatible**  
  Same or nearly same function name and shape; expected beginner behavior preserved.

- **Tier B — Compatible Approximation**  
  Same or similar function, but behavior is simplified or internally reinterpreted.

- **Tier C — Partial / Limited**  
  Some parameters, edge cases, or related features are omitted.

- **Tier D — Unsupported**  
  Not implemented.

### 12.2 Compatibility Documentation Requirement

Every implemented command family must ship with:

- supported commands list
- tier classification
- known deviations
- sample programs demonstrating expected use

---

## 13. Testing Requirements

### 13.1 TDD Requirement

Catch2-based TDD is mandatory. New work should begin by specifying behavior through tests whenever practical.

### 13.2 Testing Scope

The test strategy must include:

- unit tests for runtime services
- unit tests for registries and state transitions
- unit tests for command translation logic
- compatibility-focused tests for representative textbook samples
- smoke tests for example applications
- CI-executed tests on supported platforms where feasible

### 13.3 Testing Priorities

Highest-priority test coverage should target:

1. asset ID registries
2. lifecycle and runtime state transitions
3. frame / sync behavior
4. sprite and image command mapping
5. keyboard / mouse query behavior
6. audio load / play / stop lifecycle
7. camera and simple 3D state behavior

### 13.4 Testability Requirements

The architecture must separate logic that can be unit tested without a live rendering context from backend-specific integration code.

### 13.5 Example / Golden Tests

The project should maintain a curated set of representative educational examples and use them as compatibility regression checks where practical.

---

## 14. Build, Tooling, and CI Requirements

### 14.1 Build System

The project must use CMake as the canonical build system.

### 14.2 Tooling

The project must support:

- command-line builds
- Visual Studio Code workflows
- straightforward dependency setup
- clear contributor onboarding

### 14.3 CI Requirements

CI should:

- build the project on key target platforms where feasible
- run Catch2 tests on every PR
- detect formatting and lint issues if such tooling is added
- fail fast on test regressions

### 14.4 Dependency Discipline

Dependencies should remain minimal. `raylib` and Catch2 are foundational; other dependencies must be justified explicitly.

---

## 15. Documentation Requirements

The repository must include:

- `README.md`
- architecture overview
- build instructions
- testing instructions
- compatibility matrix
- command-family docs
- examples directory
- contribution guide
- roadmap summary

Documentation should optimize for both learners and contributors.

---

## 16. Repository and Code Organization Requirements

The repo should be organized so that:

- public headers are clearly separated from internals
- command-family modules are isolated
- runtime services are isolated from `raylib` bindings where possible
- tests mirror runtime and command-family organization
- examples are easy to build and run

A likely initial structure:

```text
LiteGDK/
  CMakeLists.txt
  README.md
  docs/
  include/
    DarkGDK.h
    LiteGDK/
  src/
    compat/
    runtime/
    backend/
  tests/
    unit/
    integration/
    golden/
  examples/
    textbook/
    demos/
  third_party/
```

---

## 17. Milestones

### Milestone 1 — Foundation

- repo scaffolding
- CMake configuration
- dependency integration
- Catch2 test harness
- runtime skeleton
- public header skeleton

### Milestone 2 — Core and Text

- init / loop / sync behavior
- timing basics
- clear / present
- text commands
- initial examples

### Milestone 3 — Input + Images + Sprites

- keyboard and mouse commands
- image registry
- sprite registry
- load / draw / position commands
- compatibility tests for common 2D samples

### Milestone 4 — Audio

- sound / music basics
- lifecycle commands
- tests and examples

### Milestone 5 — Camera + Basic 3D

- basic camera state
- primitive 3D rendering support
- simple transform commands
- sample preservation focus

### Milestone 6 — Compatibility Expansion

- selective additional commands
- compatibility matrix growth
- golden sample coverage expansion

---

## 18. Success Criteria

LiteGDK will be considered successful in its early phases if:

1. A curated set of representative textbook-style samples compile and run on modern systems.
2. The public SDK feels familiar to users expecting DarkGDK-style procedural code.
3. Contributors can navigate the codebase and add command families without architectural confusion.
4. Catch2 tests provide confidence against regressions.
5. The compatibility matrix truthfully reflects what works and what does not.

---

## 19. Risks and Mitigations

### Risk 1: Scope Creep

Trying to recreate too much of DarkGDK too early may stall the project.

**Mitigation:** strict milestone gating, command-family prioritization, compatibility tiers.

### Risk 2: Legacy API Shape Hurts Architecture

A flat procedural public API can lead to fragile internals.

**Mitigation:** keep the public API thin; centralize complexity in runtime services.

### Risk 3: Rendering-Context Coupling Hurts Testability

If all logic depends on a live graphics context, tests become brittle.

**Mitigation:** separate stateful logic from backend calls and test services independently.

### Risk 4: Compatibility Expectations Become Unrealistic

Users may assume full DarkGDK support.

**Mitigation:** explicitly market LiteGDK as educational and source-friendly, not exact.

### Risk 5: Cross-Platform Drift

Implementations may accidentally favor one OS too heavily.

**Mitigation:** maintain CI across target platforms where feasible and document platform limitations.

---

## 20. Definition of Done

A feature is done only when:

1. behavior is specified through tests where practical
2. Catch2 tests are passing
3. public API signature and documentation are updated
4. compatibility tier is assigned
5. examples or sample usage are added when appropriate
6. code adheres to repo architecture boundaries
7. CI passes

---

## 21. Open Questions

1. Which exact DarkGDK textbook sample set should be the initial compatibility baseline?
2. Which commands are required for the first public MVP versus deferred to later milestones?
3. How much aliasing / overload support should be allowed before maintainability suffers?
4. Should LiteGDK expose optional modern conveniences outside the core beginner path, or remain strictly legacy-shaped?
5. What is the minimal integration-test strategy for rendering-backed commands in CI?

---

## 22. Initial Recommendation

Proceed with LiteGDK as a `raylib`-backed, DarkGDK-inspired compatibility SDK focused on:

- source-friendly educational compatibility
- honest scope control
- strong internal architecture
- Catch2-driven TDD
- incremental milestone delivery

The first implementation should prioritize Core, Text, Input, Images, Sprites, Audio, Camera, and Basic 3D command families, along with a published compatibility matrix and a robust test-first development workflow.
