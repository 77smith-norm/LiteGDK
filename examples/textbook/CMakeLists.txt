set(TEXTBOOK_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(TEXTBOOK_RUNTIME_DIR "${CMAKE_BINARY_DIR}/examples/textbook")

function(add_textbook_example target_name)
    add_executable(${target_name} "${target_name}.cpp")
    target_link_libraries(${target_name} PRIVATE litegdk_entrypoint)
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${TEXTBOOK_RUNTIME_DIR}"
    )
    add_custom_command(TARGET ${target_name} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                "${TEXTBOOK_ASSET_DIR}"
                "$<TARGET_FILE_DIR:${target_name}>/assets"
    )
endfunction()

add_textbook_example(hello_text)
add_textbook_example(sprite_movement)
add_textbook_example(simple_audio)
add_textbook_example(basic_3d)
