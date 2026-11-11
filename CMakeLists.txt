cmake_minimum_required(VERSION 3.20)

project(imagehl2
    VERSION 1.0.0
    DESCRIPTION "imagehl2.dll proxy for dbghelp.dll"
    LANGUAGES CXX
)

option(IMAGEHL2_BUILD_TESTS "Build test suite" ON)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS
    "src/*.cpp"
    "src/*.def"
    "src/*.rc"
)

# Shared library target: imagehl2.dll
add_library(imagehl2 SHARED ${SRC})

# Ensure the Module Definition file is passed to the linker
if(MSVC)
    target_link_options(imagehl2 PRIVATE "/DEF:${CMAKE_CURRENT_SOURCE_DIR}/src/imagehl2.def")
endif()

# Installation rules
install(TARGETS imagehl2
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)

if(IMAGEHL2_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
