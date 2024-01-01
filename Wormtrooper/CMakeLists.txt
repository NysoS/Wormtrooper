cmake_minimum_required(VERSION 3.28)
project(Wormtrooper)

set (PATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

include_directories(
	"${PATH_DIR}"
)


add_executable(${PROJECT_NAME} "src/GameApp.cpp")
set(CMAKE_CXX_STANDARD 20)