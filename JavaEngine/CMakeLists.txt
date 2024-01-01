cmake_minimum_required(VERSION 3.28)
project(JavaEngine)

set (PATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

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
)
set(SOURCES
	"${PATH_DIR}/JavaEngine/Application.cpp"
	"${PATH_DIR}/JavaEngine/Log.cpp"
)
include_directories(
	"${PATH_DIR}"
	"${PATH_DIR}/JavaEngine"
)
add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})