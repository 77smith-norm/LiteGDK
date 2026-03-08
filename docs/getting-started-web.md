# Getting Started on the Web

This guide is for learners who already have a native LiteGDK game building locally and want to run the same code in the browser with WebAssembly and GitHub Pages.

## 1. Prerequisites

Install these tools first:

- [emsdk 3.1.61](https://emscripten.org/docs/getting_started/downloads.html)
- CMake 3.20 or newer
- Ninja
- Git

One clean way to install Emscripten locally is:

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install 3.1.61
./emsdk activate 3.1.61
source ./emsdk_env.sh
```

Verify the active version:

```bash
emcc --version
```

You should see `3.1.61` in the output.

## 2. Building for the Web Locally

From the LiteGDK repo root:

```bash
source /path/to/emsdk/emsdk_env.sh
emcmake cmake --preset wasm
cmake --build build-wasm
```

The textbook example outputs land in:

```text
build-wasm/examples/textbook/
```

That folder contains the generated `.html`, `.js`, `.wasm`, and `.data` files for each example.

To preview locally with the Emscripten helper:

```bash
emrun build-wasm/examples/textbook/hello_text.html
```

## 3. Writing a WASM-Compatible LiteGDK Game

### The game loop

You can keep the normal LiteGDK loop:

```cpp
while (LoopGDK()) {
    // game code
    dbSync();
}
```

The current web build uses ASYNCIFY, so textbook-style `while (LoopGDK())` code works without rewriting your game into browser callbacks.

### Asset paths

`examples/textbook/ExampleAssets.h` already uses a `__EMSCRIPTEN__` guard. Native builds resolve files from the filesystem. Web builds resolve them from the browser's virtual filesystem under `/assets/`.

If your game needs its own assets, make sure they are packaged with Emscripten using `--preload-file`. For example:

```cmake
target_link_options(my_example PRIVATE
    "SHELL:--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/assets/@/assets"
)
```

Inside your game, the virtual path should begin with `/assets/`.

### Audio

Browsers block autoplay audio until the user interacts with the page. LiteGDK's web shell includes a built-in "Click to start" prompt so audio can unlock before the main loop begins.

## 4. Deploying to GitHub Pages

1. Fork or clone the repo.
2. Push your changes to the `main` branch.
3. In GitHub, open `Settings -> Pages`.
4. Set the source to the `gh-pages` branch.
5. Wait for `.github/workflows/web-deploy.yml` to run after a push to `main`.

That workflow builds and publishes:

- `hello_text`
- `sprite_movement`
- `simple_audio`
- `basic_3d`
- the gallery page from `web/index.html`

After deployment, the site URL is:

```text
https://<username>.github.io/LiteGDK/
```

## 5. Adding a New Web-Deployable Example

For a new textbook-style example:

1. Add a new source file under `examples/textbook/`, such as `my_example.cpp`.
2. If it needs packaged assets, place them in `examples/textbook/assets/` or add another `--preload-file` entry for that target.
3. Register the target in `examples/textbook/CMakeLists.txt` with:

```cmake
add_textbook_example(my_example)
```

The `add_textbook_example()` helper already applies the LiteGDK entrypoint and the WASM link flags through `configure_textbook_example_for_web()`.

If you create a brand new example folder instead of using `examples/textbook/`, add its subdirectory to `examples/CMakeLists.txt`.

Finally, add a card for the new page to `web/index.html` so it appears in the gallery.

## 6. Troubleshooting

### `emcmake: command not found`

Source `emsdk_env.sh` in the current shell before configuring.

### Blank canvas or no output

Open the browser dev tools and check the console for WebAssembly or asset-loading errors.

### Audio is silent

Click the canvas or the start button first. Browsers require a user gesture before audio playback starts.

### Assets are not loading

Check the `--preload-file` path in CMake and make sure the runtime path starts with `/assets/`.

### The first WASM build is slow

Emscripten, raylib, and other FetchContent downloads are cached under `build-wasm/_deps`. Avoid deleting `build-wasm` unless you really need a clean rebuild.
