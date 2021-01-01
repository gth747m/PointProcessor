
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

add_executable (PointProcessorTest
	"NamedMutexTest.cpp"
	"pch.cpp"
	"SharedMemoryTest.cpp")
