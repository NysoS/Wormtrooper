project(JavaEngine)

set (PATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set (PATH_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/)

include_directories(src)

# not stolen at all
macro(GroupSources curdir)
    file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
    ${PROJECT_SOURCE_DIR}/${curdir}/* ${PROJECT_SOURCE_DIR}/${curdir}/${curdir}/*)

    foreach(child ${children})

        if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
            GroupSources(${curdir}/${child})
        else()
            string(REPLACE "/" "\\" groupname ${curdir})
            source_group(${groupname} FILES
            ${PROJECT_SOURCE_DIR}/${curdir}/${child})
        endif()
    endforeach()
endmacro()

GroupSources(src)

set(HEADERS
	"${PATH_DIR}/JavaEngine/Application.h"
	"${PATH_DIR}/JavaEngine/Core.h"
	"${PATH_DIR}/JavaEngine/EntryPoint.h"
	"${PATH_DIR}/JavaEngine/Log.h"
	"${PATH_DIR}/JavaEngine.h"
	"${PATH_DIR}/jepch.h"
    "${PATH_DIR}/JavaEngine/Events/Event.h"
    "${PATH_DIR}/JavaEngine/Events/ApplicationEvent.h"
    "${PATH_DIR}/JavaEngine/Events/KeyEvent.h"
    "${PATH_DIR}/JavaEngine/Events/MouseEvent.h"
)

set(SOURCES
	"${PATH_DIR}/JavaEngine/Application.cpp"
	"${PATH_DIR}/JavaEngine/Log.cpp"
	"${PATH_DIR}/jepch.cpp"
)

find_package(Threads REQUIRED)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

add_compile_definitions(
    JE_PLATFORM_WINDOWS
    JE_BUILD_DLL
)

target_precompile_headers(${PROJECT_NAME} PRIVATE "${PATH_DIR}/jepch.h")

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${PATH_DIR}
)

include_directories(${PATH_VENDOR_DIR}spdlog)
add_subdirectory(${PATH_VENDOR_DIR}spdlog)

target_link_libraries(${PROJECT_NAME} PRIVATE spdlog)
target_link_libraries(${PROJECT_NAME} PRIVATE Threads::Threads)

if(CMAKE_VERSION VERSION_GREATER 3.8)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)