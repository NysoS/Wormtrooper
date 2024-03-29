project(Wormtrooper)

set (PATH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# set(HEADERS

# )

# set(SOURCES
#	"${PATH_DIR}/GameApp.cpp"
# )

file(GLOB_RECURSE PROJECT_HEADER_FILES "*.h" "*.hxx")
file(GLOB_RECURSE PROJECT_SOURCE_FILES "*.cpp")

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

include_directories(JavaEngine)

add_executable(${PROJECT_NAME} ${PROJECT_HEADER_FILES} ${PROJECT_SOURCE_FILES})

set(VCPKG_INSTALLED ${CMAKE_SOURCE_DIR}/vendor/vcpkg_installed/x64-windows)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND $<$<CONFIG:Debug,Release>:${CMAKE_COMMAND}>  $<$<CONFIG:Debug,Release>:-E>  $<$<CONFIG:Debug,Release>:copy_directory> $<$<CONFIG:Debug>:"${VCPKG_INSTALLED}/debug/bin/"> $<$<CONFIG:Release>:"${VCPKG_INSTALLED}/bin/"> "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    COMMAND_EXPAND_LISTS
)

add_compile_definitions(
    JE_PLATFORM_WINDOWS
)

target_link_libraries(${PROJECT_NAME} PRIVATE JavaEngine)

if(CMAKE_VERSION VERSION_GREATER 3.8)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)