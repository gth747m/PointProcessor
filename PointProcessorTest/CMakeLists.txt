
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	# Using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	# Using GCC
	set(GCC_COMPILE_FLAGS "-Wall -Wextra -Wpedantic")
	set (CMAKE_CXX_FLAGS ${GCC_COMPILE_FLAGS})
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	# Using MSVC
	set(MSVC_COMPILE_FLAGS "/W4 /EHsc")
	set (CMAKE_CXX_FLAGS ${MSVC_COMPILE_FLAGS})
endif()

# Download and unpack googletest at configure time
configure_file(GTestCMakeLists.txt googletest/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest"
)
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest"
)

# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This adds the following targets:
# gtest, gtest_main, gmock and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
                 "${CMAKE_BINARY_DIR}/googletest-build"
)

add_executable (PointProcessorTest
	"NamedMutexTest.cpp"
	"pch.cpp"
	"SharedMemoryTest.cpp")

add_dependencies (PointProcessorTest googletest)
