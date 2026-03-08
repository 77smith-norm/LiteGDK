# Textbook Smoke Samples

LiteGDK keeps a small set of preserved DarkGDK-style sample ports under
`tests/integration/samples/` as regression artifacts for the public preview.

## Preserved samples

| Sample | Purpose | Coverage |
| --- | --- | --- |
| `test_arcade_sample.cpp` | Old-style 2D sample with globals, sprite setup, keyboard movement, and text prompts | Core, Text, Input, Images, Sprites |
| `test_multimedia_sample.cpp` | Old-style multimedia sample that triggers sound while rotating a cube in a simple 3D scene | Core, Text, Sound, Basic3D |

## How they run

- Both samples compile as standalone executables linked against `litegdk_entrypoint`.
- A small test harness installs the existing headless `TestBackend` before
  `DarkGDK()` runs, so the samples stay source-authentic while remaining CI-safe.
- The CI integration smoke job picks them up through the `darkgdk_*_smoke`
  naming pattern in CTest.
