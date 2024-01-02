project(Wormtrooper)

set (PATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# set(HEADERS

# )

set(SOURCES
	"${PATH_DIR}/GameApp.cpp"
)

include_directories(JavaEngine)

add_executable(${PROJECT_NAME} ${SOURCES})

add_compile_definitions(
    JE_PLATFORM_WINDOWS
)

target_link_libraries(${PROJECT_NAME} PRIVATE JavaEngine)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)

if(CMAKE_VERSION VERSION_GREATER 3.8)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)