cmake_minimum_required (VERSION 3.8)
project ("PointProcessor")

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Include sub-projects
#add_subdirectory ("PointProcessor")
add_subdirectory ("PointProcessorLib")
add_subdirectory ("PointProcessorTest")
