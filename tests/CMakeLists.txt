add_executable(test_proxy test_proxy.cpp)

# test_proxy uses dynamic loading to verify imagehl2.dll
add_dependencies(test_proxy imagehl2)

# Copy imagehl2.dll into test executable directory for testing
add_custom_command(TARGET test_proxy POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:imagehl2>
        $<TARGET_FILE_DIR:test_proxy>
)

add_test(NAME test_imagehl2_proxy
    COMMAND test_proxy "$<TARGET_FILE:imagehl2>"
)
