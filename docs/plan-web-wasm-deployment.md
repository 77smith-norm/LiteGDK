# Plan: Web / WebAssembly Deployment via Emscripten

**Status:** In Progress  
**Author:** Norm  
**Date:** 2026-03-08  

---

## Summary

Add the web browser as a first-class deployment target for LiteGDK games. The plan uses [Emscripten](https://emscripten.org/) to compile the C++/raylib stack to WebAssembly (WASM), builds the output via GitHub Actions, and deploys it as a GitHub Pages site.

**Verdict: This is feasible.** The stack lines up well — raylib has official `PLATFORM_WEB` support via Emscripten, CMake integrates cleanly with the Emscripten toolchain file, and GitHub Actions can install the emsdk in one step. The one non-trivial change is the game loop, addressed in detail below.

---

## Why It Works

| Layer | Notes |
|-------|-------|
| **raylib** | Official `PLATFORM_WEB` target. Ships its own Emscripten CMake support. Handles OpenGL → WebGL, keyboard/mouse input, and audio out of the box. |
| **Emscripten** | Drop-in `emcc`/`em++` replaces the native C++ compiler. Acts on the same CMakeLists.txt via a toolchain file — no parallel build system needed. |
| **CMake** | `emcmake cmake` / `-DCMAKE_TOOLCHAIN_FILE=<emsdk>/Emscripten.cmake` route the entire build through Emscripten. `FetchContent` for raylib and Catch2 works unchanged. |
| **GitHub Actions** | The `mymindstorm/setup-emsdk` action installs a pinned emsdk version in under 30 seconds on `ubuntu-latest`. |
| **GitHub Pages** | Build output is three static files (`.html`, `.js`, `.wasm`) — perfect for Pages. Browsers require `SharedArrayBuffer` headers for threaded WASM, but single-threaded LiteGDK builds sidestep that entirely. |

---

## The One Hard Part: The Game Loop

LiteGDK games use a blocking `while (LoopGDK())` loop. Browsers cannot block the main thread — the tab would freeze. This is the only fundamental incompatibility.

### Option A — ASYNCIFY (Recommended for LiteGDK)

Emscripten's [`ASYNCIFY`](https://emscripten.org/docs/porting/asyncify.html) flag instruments the compiled code to transparently yield to the browser event loop between iterations. **The `DarkGDK()` source code stays completely unchanged.**

```cmake
# wasm/CMakeLists.txt (or as target_link_options on a per-example basis)
target_link_options(my_game PRIVATE
    -sASYNCIFY=1
    -sASYNCIFY_STACK_SIZE=65536
)
```

- **Pros:** Zero source changes; existing examples compile as-is.  
- **Cons:** ASYNCIFY adds ~20–30% code size overhead and a small runtime cost. Fine for educational games.

### Option B — Emscripten Main Loop (Leaner, More Invasive)

Replace `while (LoopGDK())` with `emscripten_set_main_loop(frame_callback, 0, 1)`. Requires restructuring user code into a frame callback function.

- **Pros:** Smaller, faster output.  
- **Cons:** Changes the DarkGDK-compatible API contract. Not recommended until the WASM target matures.

### Option C — Hybrid via `FrameRunner` Platform Layer

Add a `PLATFORM_WEB` path to `FrameRunner.cpp` and `Lifecycle.cpp` that registers the frame callback internally. Users still write `while (LoopGDK())`, but the internals rewire the loop on web. This is the long-term clean solution.

**For the initial implementation: use Option A (ASYNCIFY).** Revisit Option C later if binary size becomes a concern.

---

## Changes Required

### 1. CMake — Emscripten Preset and Link Flags

Add a `CMakePresets.json` entry for `wasm`:

```json
{
  "name": "wasm",
  "displayName": "WASM (Emscripten)",
  "generator": "Ninja",
  "binaryDir": "${sourceDir}/build-wasm",
  "toolchainFile": "$env{EMSDK}/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake",
  "cacheVariables": {
    "CMAKE_BUILD_TYPE": "Release",
    "PLATFORM": "Web",
    "BUILD_EXAMPLES": "OFF",
    "EMSCRIPTEN": "ON"
  }
}
```

Per-example link options (in `examples/CMakeLists.txt`):

```cmake
if(EMSCRIPTEN)
    set_target_properties(hello_text PROPERTIES SUFFIX ".html")
    target_link_options(hello_text PRIVATE
        -sASYNCIFY=1
        -sASYNCIFY_STACK_SIZE=65536
        -sALLOW_MEMORY_GROWTH=1
        -sUSE_GLFW=3
        -sWASM=1
        --shell-file ${CMAKE_SOURCE_DIR}/web/shell.html
        --preload-file ${CMAKE_SOURCE_DIR}/examples/textbook/assets/@/assets
    )
endif()
```

### 2. HTML Shell

Create `web/shell.html` — a minimal page wrapping the Emscripten canvas. Emscripten's default shell works, but a custom shell allows LiteGDK branding, a loading spinner, and a "Click to start" button (needed for browser audio autoplay policy).

### 3. `src/sound/` — Audio Context Unlock

Browsers block audio until the first user gesture. Emscripten's SDL2/OpenAL audio backend handles this automatically via raylib's `InitAudioDevice()`, but it must be called after a user interaction. For `PLATFORM_WEB`, `InitAudioDevice()` should be deferred to the first `LoopGDK()` iteration or triggered by a click in the shell. This is a small platform guard, not a rewrite.

### 4. Asset Packaging

Emscripten's `--preload-file` bundles assets into the `.data` file alongside `.wasm` and `.js`. The `ExampleAssets.h` path resolution needs a `#ifdef __EMSCRIPTEN__` guard pointing to the virtual FS root (`/assets/...`).

### 5. `Catch2` Tests — Skip on WASM

Unit tests don't run in the WASM build (no headless browser runner in CI). Gate with:

```cmake
if(NOT EMSCRIPTEN)
    add_subdirectory(tests)
endif()
```

---

## GitHub Actions Workflow

New file: `.github/workflows/web-deploy.yml`

```yaml
name: Web Deploy

on:
  push:
    branches: [ main ]

jobs:
  build-wasm:
    runs-on: ubuntu-latest

    steps:
      - uses: actions/checkout@v4

      - name: Setup emsdk
        uses: mymindstorm/setup-emsdk@v14
        with:
          version: 3.1.61   # pin for reproducibility

      - name: Install Ninja
        run: sudo apt-get install -y ninja-build

      - name: Configure (WASM)
        run: emcmake cmake --preset wasm

      - name: Build
        run: cmake --build build-wasm --config Release

      - name: Collect output
        run: |
          mkdir -p gh-pages
          cp build-wasm/examples/textbook/*.html gh-pages/
          cp build-wasm/examples/textbook/*.js   gh-pages/
          cp build-wasm/examples/textbook/*.wasm gh-pages/
          cp build-wasm/examples/textbook/*.data gh-pages/ 2>/dev/null || true
          cp web/index.html gh-pages/index.html

      - name: Deploy to GitHub Pages
        uses: peaceiris/actions-gh-pages@v4
        with:
          github_token: ${{ secrets.GITHUB_TOKEN }}
          publish_dir: ./gh-pages
```

**Note:** GitHub Pages requires the repo to have Pages enabled (Settings → Pages → Source: `gh-pages` branch).

---

## What `COOP/COEP` Headers Are (and Why They Don't Apply Here)

Multi-threaded WASM requires `SharedArrayBuffer`, which in turn requires `Cross-Origin-Opener-Policy` and `Cross-Origin-Embedder-Policy` headers — GitHub Pages does not set these by default and they are hard to configure. Single-threaded LiteGDK builds do **not** need `SharedArrayBuffer` at all, so this is a non-issue for the initial implementation.

---

## Milestone Plan

| Milestone | Deliverable |
|-----------|-------------|
| **M1 — Proof of concept** | `hello_text` example builds and runs in browser locally via `emrun`. ASYNCIFY working. No CI yet. |
| **M2 — Asset pipeline** | `sprite_movement` builds with image preloading. `shell.html` with loading bar. Audio unlock guard. |
| **M3 — GitHub Actions** | `web-deploy.yml` workflow green. All textbook examples deploy to Pages automatically on push to `main`. |
| **M4 — Polish** | Custom HTML gallery page (`web/index.html`) listing all examples. Per-example canvas sizing. Mobile-friendly layout. |
| **M5 — Documentation** | `docs/getting-started-web.md`. WASM tier added to compatibility matrix. |

---

## Risks and Mitigations

| Risk | Likelihood | Mitigation |
|------|-----------|-----------|
| ASYNCIFY binary size too large for some games | Low | Profile; switch to Option C (FrameRunner platform layer) if needed |
| raylib audio autoplay blocked | Medium | Shell `onclick` wrapper; defer `InitAudioDevice()` |
| `FetchContent` network fetch fails in CI | Low | `FETCHCONTENT_UPDATES_DISCONNECTED=ON` already set; cache with `actions/cache` |
| GitHub Pages 100MB repo size limit | Very low | WASM builds are typically 2–8 MB per example |
| 3D (raylib OpenGL 3.3) → WebGL 2 gaps | Low | raylib handles this; minor shader differences may appear |

---

## References

- [Emscripten Tutorial](https://emscripten.org/docs/getting_started/Tutorial.html)
- [Building to WebAssembly](https://emscripten.org/docs/compiling/WebAssembly.html)
- [Emscripten CI/CD patterns (GitLab)](https://emscripten.org/docs/compiling/GitLab.html) — same concept applies to GitHub Actions
- [raylib PLATFORM_WEB](https://github.com/raysan5/raylib/wiki/Working-for-Web-(HTML5))
- [`mymindstorm/setup-emsdk`](https://github.com/mymindstorm/setup-emsdk) — GitHub Action for emsdk
- [`peaceiris/actions-gh-pages`](https://github.com/peaceiris/actions-gh-pages) — Pages deploy action
