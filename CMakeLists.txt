cmake_minimum_required(VERSION 3.8)

project(Wormtrooper)

set(VCPKG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg)
set(CMAKE_TOOLCHAIN_FILE ${VCPKG_DIR}/scripts/buildsystem/vcpkg.cmake CACHE STRING "Vcpkg toolchain file")

set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg_installed/x64-windows/share)
find_package(SFML COMPONENTS system window audio graphics CONFIG REQUIRED)
find_package(imgui-sfml CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set (FULL_OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/${PROJECT_NAME})
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${FULL_OUTPUT_DIR}/static_libs)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${FULL_OUTPUT_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FULL_OUTPUT_DIR})

add_subdirectory(JavaEngine)
add_subdirectory(Wormtrooper)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Wormtrooper)