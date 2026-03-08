# Getting Started with LiteGDK in VS Code

This guide walks you from a fresh clone to a running example program in Visual Studio Code. It takes about 10 minutes.

---

## 1. Install prerequisites

### macOS

```bash
# Install CMake via Homebrew
brew install cmake

# Clang ships with Xcode Command Line Tools
xcode-select --install
```

### Windows

1. Install [CMake](https://cmake.org/download/) — check **"Add CMake to PATH"** during setup
2. Install [Visual Studio 2022](https://visualstudio.microsoft.com/) with the **"Desktop development with C++"** workload (MSVC + Windows SDK)
3. Install [Git for Windows](https://git-scm.com/download/win)

### Linux (Ubuntu / Debian)

```bash
sudo apt update
sudo apt install cmake build-essential git
```

---

## 2. Install VS Code extensions

Open VS Code and install these extensions:

| Extension | ID | Why |
|-----------|-----|-----|
| C/C++ | `ms-vscode.cpptools` | IntelliSense, debugging |
| CMake Tools | `ms-vscode.cmake-tools` | CMake integration |
| C/C++ Extension Pack | `ms-vscode.cpptools-extension-pack` | Bundles both above |

Install via the Extensions panel (`Ctrl+Shift+X` / `Cmd+Shift+X`) or:

```bash
code --install-extension ms-vscode.cpptools-extension-pack
```

---

## 3. Clone and open

```bash
git clone https://github.com/77smith-norm/LiteGDK.git
cd LiteGDK
code .
```

VS Code will open the folder. If prompted **"Do you trust the authors?"** — click **Yes**.

---

## 4. Configure the build

### Option A — VS Code tasks (recommended)

Open the Command Palette (`Ctrl+Shift+P` / `Cmd+Shift+P`) → **Tasks: Run Task** → **LiteGDK: Configure**

This runs `cmake --preset debug` and downloads raylib and Catch2 automatically. It takes 1–3 minutes on the first run (dependency download). Subsequent runs are instant.

### Option B — Terminal

```bash
cmake --preset debug
```

---

## 5. Build

**Tasks: Run Task** → **LiteGDK: Build**

Or in the terminal:

```bash
cmake --build --preset debug
```

A successful build produces:
- `build/liblitegdk.a` (or `.lib` on Windows) — the SDK library
- `build/litegdk_tests` — the test runner
- `build/examples/textbook/hello_text` (and other examples)

---

## 6. Run the tests

**Tasks: Run Task** → **LiteGDK: Test**

Or:

```bash
ctest --preset debug --output-on-failure
```

All tests should pass. If any fail, open an issue.

---

## 7. Run an example

After building, run a textbook example directly from the terminal:

```bash
# macOS / Linux
./build/examples/textbook/hello_text

# Windows
.\build\examples\textbook\Debug\hello_text.exe
```

| Example | What you'll see |
|---------|----------------|
| `hello_text` | A window with "Hello LiteGDK" drawn each frame |
| `sprite_movement` | A sprite you can move with arrow keys |
| `simple_audio` | A sound plays on launch |
| `basic_3d` | A rotating 3D cube |

---

## 8. Write your first program

Create a new file `examples/textbook/my_first/main.cpp`:

```cpp
#include "DarkGDK.h"

void DarkGDK() {
    dbSyncOn();
    dbSyncRate(60);

    while (LoopGDK()) {
        dbCLS();
        dbText(10, 10, "Hello from my first LiteGDK program!");
        dbSync();
    }
}
```

Add it to `CMakeLists.txt` by following the pattern used for `hello_text` in the examples section. Then configure and build again.

---

## 9. IntelliSense setup

CMake Tools should pick up `build/compile_commands.json` automatically. If IntelliSense shows red squiggles on `#include "DarkGDK.h"`:

1. Open Command Palette → **C/C++: Edit Configurations (JSON)**
2. Add to `includePath`:
   ```json
   "${workspaceFolder}/include",
   "${workspaceFolder}/build/_deps/raylib-src/src"
   ```

---

## 10. Debugging an example

1. Open `examples/textbook/hello_text/main.cpp`
2. Set a breakpoint on the `dbText` line
3. Open the **Run and Debug** panel (`Ctrl+Shift+D` / `Cmd+Shift+D`)
4. Click **"create a launch.json file"** → select **C++ (GDB/LLDB)**
5. Set `"program"` to `"${workspaceFolder}/build/examples/textbook/hello_text/hello_text"`
6. Press `F5` to launch

---

## Troubleshooting

| Problem | Fix |
|---------|-----|
| `cmake: command not found` | Add CMake to PATH; restart VS Code |
| FetchContent fails (network error) | Check internet connection; corporate proxies may block GitHub |
| raylib build fails on Linux | `sudo apt install libx11-dev libgl1-mesa-dev` |
| `DarkGDK.h` not found | Run Configure first; IntelliSense needs `compile_commands.json` |
| Example window flashes and closes | Normal on CI/headless; run from a desktop session |

---

## Next steps

- Read the [compatibility matrix](compatibility/commands.md) to see what `db*` functions are available
- Look at `examples/textbook/` for working code patterns
- Read [CONTRIBUTING.md](../CONTRIBUTING.md) if you want to add a command family
- Check [preview-0.1.md](releases/preview-0.1.md) for known limitations
