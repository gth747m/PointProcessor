cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    # Using Clang
    set (CLANG_COMPILE_FLAGS "-Wall -Wextra -Wpedantic")
    set (CMAKE_CXX_FLAGS ${CLANG_COMPILE_FLAGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # Using GCC
    set (GCC_COMPILE_FLAGS "-Wall -Wextra -Wpedantic")
    set (CMAKE_CXX_FLAGS ${GCC_COMPILE_FLAGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # Using MSVC
    set (MSVC_COMPILE_FLAGS "/W4 /EHsc")
    set (CMAKE_CXX_FLAGS ${MSVC_COMPILE_FLAGS})
endif ()

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${CMAKE_CURRENT_SOURCE_DIR}/gtest/src/gtest-build/lib/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
    "IMPORTED_LOCATION" "${CMAKE_CURRENT_SOURCE_DIR}/gtest/src/gtest-build/lib/libgmock.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

file (GLOB SRCS *.cpp)

add_executable (PointProcessorTest ${SRCS})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gtest/src/gtest/googletest/include/)

target_link_libraries (PointProcessorTest PointProcessorLib)
target_link_libraries (PointProcessorTest libgtest libgmock)
target_link_libraries (PointProcessorTest rt)
