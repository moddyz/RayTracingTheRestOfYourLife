cmake_minimum_required(VERSION 3.17)

# Project Name
project(
    RayTracingTheRestOfYourLife
    VERSION 0.0
    DESCRIPTION "Implementation of the Ray Tracing: The Rest of Your Life."
    LANGUAGES CXX
)

# Options
option(BUILD_DOCUMENTATION "Build doxygen documentation." ON)

# Debug flags.
set(CMAKE_CXX_FLAGS_DEBUG "-DGM_DEBUG")

# Cross-platform compatibility.
if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()

# Discover macros.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
                      ${CMAKE_SOURCE_DIR}/cmake/macros)
include(Public)

# Testing.
if(BUILD_TESTING)
    enable_testing()
    list(APPEND CMAKE_CTEST_ARGUMENTS "--output-on-failure")
endif()

if(BUILD_DOCUMENTATION)
    file(
        COPY ${CMAKE_SOURCE_DIR}/README.md
        DESTINATION ${CMAKE_BINARY_DIR}
    )

    doxygen_documentation(
        doxygen_docs
        GENERATE_TAGFILE
            TRUE
        DOXYFILE
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in
        INPUTS
            ${CMAKE_CURRENT_SOURCE_DIR}/src/
            ${CMAKE_CURRENT_SOURCE_DIR}/src/raytrace
        TAGFILES
            ${CMAKE_CURRENT_SOURCE_DIR}/docs/gm.tag=https://moddyz.github.io/GraphicsMath/
    )
endif()

# Build targets.
add_subdirectory(thirdparty)
add_subdirectory(src)

# Install exported targets.
#export_project(${CMAKE_SOURCE_DIR}/cmake/Config.cmake.in)
