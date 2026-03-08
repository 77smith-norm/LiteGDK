cmake_minimum_required(VERSION 3.20)
project(LiteGDK LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "" FORCE)

# raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        master
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Library target
add_library(litegdk
    src/compat/DarkGDK.cpp
    src/compat/Images.cpp
    src/compat/Input.cpp
    src/compat/Sound.cpp
    src/compat/Sprites.cpp
    src/compat/Text.cpp
    src/backend/RaylibBackend.cpp
    src/basic3d/CameraState.cpp
    src/basic3d/ObjectRegistry.cpp
    src/core/FrameRunner.cpp
    src/core/Lifecycle.cpp
    src/images/ImageCommands.cpp
    src/images/ImageRegistry.cpp
    src/input/InputCommands.cpp
    src/input/InputSnapshot.cpp
    src/runtime/AppRuntime.cpp
    src/runtime/Diagnostics.cpp
    src/runtime/FrameState.cpp
    src/sound/AudioCommands.cpp
    src/sound/MusicRegistry.cpp
    src/sound/SoundRegistry.cpp
    src/sprites/SpriteCommands.cpp
    src/sprites/SpriteRegistry.cpp
    src/system/SystemServices.cpp
    src/text/TextCommands.cpp
    src/text/TextService.cpp
)
target_include_directories(litegdk PUBLIC include)
target_include_directories(litegdk PRIVATE src)
target_link_libraries(litegdk PRIVATE raylib)

add_library(litegdk_entrypoint STATIC
    src/core/DarkGDKMain.cpp
)
target_include_directories(litegdk_entrypoint PUBLIC include)
target_link_libraries(litegdk_entrypoint PUBLIC litegdk)

# Tests target
enable_testing()
add_executable(litegdk_tests
    tests/unit/basic3d/test_camera_state.cpp
    tests/unit/basic3d/test_object_registry.cpp
    tests/unit/core/test_frame_runner.cpp
    tests/unit/core/test_lifecycle.cpp
    tests/unit/images/test_image_commands.cpp
    tests/unit/images/test_image_registry.cpp
    tests/unit/input/test_input_commands.cpp
    tests/unit/input/test_input_snapshot.cpp
    tests/unit/runtime/test_diagnostics.cpp
    tests/unit/runtime/test_render_order.cpp
    tests/unit/runtime/test_registry.cpp
    tests/unit/runtime/test_runtime.cpp
    tests/unit/sound/test_audio_commands.cpp
    tests/unit/sound/test_audio_registry.cpp
    tests/unit/sprites/test_sprite_commands.cpp
    tests/unit/sprites/test_sprite_registry.cpp
    tests/unit/text/test_text.cpp
    tests/unit/system/test_system.cpp
)
target_include_directories(litegdk_tests PRIVATE src)
target_include_directories(litegdk_tests PRIVATE tests)
target_link_libraries(litegdk_tests PRIVATE litegdk Catch2::Catch2WithMain)
include(Catch)
catch_discover_tests(litegdk_tests)

add_executable(darkgdk_header_smoke
    tests/compile/test_darkgdk_header_smoke.cpp
)
target_link_libraries(darkgdk_header_smoke PRIVATE litegdk)

add_executable(darkgdk_entrypoint_smoke
    tests/integration/core/test_darkgdk_entrypoint.cpp
)
target_link_libraries(darkgdk_entrypoint_smoke PRIVATE litegdk_entrypoint)
add_test(NAME darkgdk_entrypoint_smoke COMMAND darkgdk_entrypoint_smoke)
set_tests_properties(darkgdk_entrypoint_smoke PROPERTIES
    PASS_REGULAR_EXPRESSION "DarkGDK entrypoint invoked"
)

add_executable(darkgdk_loop_smoke
    tests/integration/core/test_loop_gdk.cpp
)
target_include_directories(darkgdk_loop_smoke PRIVATE src tests)
target_link_libraries(darkgdk_loop_smoke PRIVATE litegdk_entrypoint)
add_test(NAME darkgdk_loop_smoke COMMAND darkgdk_loop_smoke)
set_tests_properties(darkgdk_loop_smoke PROPERTIES
    PASS_REGULAR_EXPRESSION "LoopGDK iterations=1 frames=1 clear=0"
)

add_executable(darkgdk_text_smoke
    tests/integration/text/test_text_smoke.cpp
)
target_include_directories(darkgdk_text_smoke PRIVATE src tests)
target_link_libraries(darkgdk_text_smoke PRIVATE litegdk)
add_test(NAME darkgdk_text_smoke COMMAND darkgdk_text_smoke)
set_tests_properties(darkgdk_text_smoke PROPERTIES
    PASS_REGULAR_EXPRESSION "Text draws=1 frames=1"
)

add_executable(darkgdk_image_smoke
    tests/integration/images/test_image_smoke.cpp
)
target_include_directories(darkgdk_image_smoke PRIVATE src tests)
target_link_libraries(darkgdk_image_smoke PRIVATE litegdk)
add_test(NAME darkgdk_image_smoke COMMAND darkgdk_image_smoke)
set_tests_properties(darkgdk_image_smoke PROPERTIES
    PASS_REGULAR_EXPRESSION "Image exists=1 width=2 height=1"
)

add_executable(darkgdk_sprite_smoke
    tests/integration/sprites/test_sprite_smoke.cpp
)
target_include_directories(darkgdk_sprite_smoke PRIVATE src tests)
target_link_libraries(darkgdk_sprite_smoke PRIVATE litegdk)
add_test(NAME darkgdk_sprite_smoke COMMAND darkgdk_sprite_smoke)
set_tests_properties(darkgdk_sprite_smoke PROPERTIES
    PASS_REGULAR_EXPRESSION "Sprite draws=1 image=1 x=14 y=22"
)

add_executable(darkgdk_render_order_smoke
    tests/integration/sprites/test_render_order_smoke.cpp
)
target_include_directories(darkgdk_render_order_smoke PRIVATE src tests)
target_link_libraries(darkgdk_render_order_smoke PRIVATE litegdk)
add_test(NAME darkgdk_render_order_smoke COMMAND darkgdk_render_order_smoke)
set_tests_properties(darkgdk_render_order_smoke PROPERTIES
    PASS_REGULAR_EXPRESSION "Order=sprite:2,sprite:5,text:first,text:second"
)

add_executable(darkgdk_input_smoke
    tests/integration/input/test_input_smoke.cpp
)
target_include_directories(darkgdk_input_smoke PRIVATE src tests)
target_link_libraries(darkgdk_input_smoke PRIVATE litegdk)
add_test(NAME darkgdk_input_smoke COMMAND darkgdk_input_smoke)
set_tests_properties(darkgdk_input_smoke PROPERTIES
    PASS_REGULAR_EXPRESSION "Up=1 mouse=144,233 click=1"
)

add_executable(darkgdk_sound_smoke
    tests/integration/sound/test_sound_smoke.cpp
)
target_include_directories(darkgdk_sound_smoke PRIVATE src tests)
target_link_libraries(darkgdk_sound_smoke PRIVATE litegdk)
add_test(NAME darkgdk_sound_smoke COMMAND darkgdk_sound_smoke)
set_tests_properties(darkgdk_sound_smoke PROPERTIES
    PASS_REGULAR_EXPRESSION "Sound plays=1 volume=35 Music plays=1 paused=1 resumed=1"
)
