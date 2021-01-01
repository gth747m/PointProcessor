cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Using GCC
    set (GCC_COMPILE_FLAGS "-Wall -Wextra -Wpedantic")
    set (CMAKE_CXX_FLAGS ${GCC_COMPILE_FLAGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Using MSVC
    set (MSVC_COMPILE_FLAGS "/W4 /EHsc")
    set (CMAKE_CXX_FLAGS ${MSVC_COMPILE_FLAGS})
endif ()

# Download and unpack googletest at configure time
configure_file (GTestCMakeLists.txt googletest/CMakeLists.txt)
execute_process (
    COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
)
execute_process (
    COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/googletest"
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set (gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory (
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest-src"
    "${CMAKE_CURRENT_SOURCE_DIR}/googletest-build"
)
include_directories(
    "${gtest_SOURCE_DIR}/include"
    "${gmock_SOURCE_DIR}/include"
)

file (GLOB SRCS *.cpp)

add_executable (PointProcessorTest ${SRCS})

target_link_libraries (PointProcessorTest PointProcessorLib)
target_link_libraries (PointProcessorTest googletest)
