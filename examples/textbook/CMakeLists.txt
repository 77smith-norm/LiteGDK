set(TEXTBOOK_ASSET_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets")
set(TEXTBOOK_RUNTIME_DIR "${CMAKE_BINARY_DIR}/examples/textbook")
set(TEXTBOOK_WEB_SHELL "${CMAKE_SOURCE_DIR}/web/shell.html")

function(configure_textbook_example_for_web target_name)
    if(NOT EMSCRIPTEN)
        return()
    endif()

    set_target_properties(${target_name} PROPERTIES SUFFIX ".html")
    target_link_options(${target_name} PRIVATE
        -sASYNCIFY=1
        -sASYNCIFY_STACK_SIZE=65536
        -sALLOW_MEMORY_GROWTH=1
        -sUSE_GLFW=3
        -sWASM=1
        "SHELL:--shell-file ${TEXTBOOK_WEB_SHELL}"
        "SHELL:--preload-file ${TEXTBOOK_ASSET_DIR}/@/assets"
    )
    set_property(TARGET ${target_name} APPEND PROPERTY LINK_DEPENDS
        "${TEXTBOOK_WEB_SHELL}"
    )
endfunction()

function(add_textbook_example target_name)
    add_executable(${target_name} "${target_name}.cpp")
    target_link_libraries(${target_name} PRIVATE litegdk_entrypoint)
    set_target_properties(${target_name} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${TEXTBOOK_RUNTIME_DIR}"
    )

    if(EMSCRIPTEN)
        configure_textbook_example_for_web(${target_name})
    else()
        add_custom_command(TARGET ${target_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
                    "${TEXTBOOK_ASSET_DIR}"
                    "$<TARGET_FILE_DIR:${target_name}>/assets"
        )
    endif()
endfunction()

add_textbook_example(hello_text)
add_textbook_example(sprite_movement)
add_textbook_example(simple_audio)
add_textbook_example(basic_3d)
