cmake_minimum_required(VERSION 3.8)

project(Wormtrooper)

set (FULL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${PROJECT_NAME})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FULL_OUTPUT_DIR}/static_libs)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FULL_OUTPUT_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FULL_OUTPUT_DIR})

add_subdirectory(JavaEngine)
add_subdirectory(Wormtrooper)