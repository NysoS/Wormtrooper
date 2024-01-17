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
	"${PATH_DIR}/JavaEngine/Core/Application.h"
	"${PATH_DIR}/JavaEngine/Core/Core.h"
	"${PATH_DIR}/JavaEngine/Core/EntryPoint.h"
	"${PATH_DIR}/JavaEngine/Core/Log.h"
	"${PATH_DIR}/JavaEngine/Core/Layer.h"
	"${PATH_DIR}/JavaEngine/Core/LayerStack.h"
	"${PATH_DIR}/JavaEngine.h"
	"${PATH_DIR}/jepch.h"
    "${PATH_DIR}/JavaEngine/Events/Event.h"
    "${PATH_DIR}/JavaEngine/Events/ApplicationEvent.h"
    "${PATH_DIR}/JavaEngine/Events/KeyEvent.h"
    "${PATH_DIR}/JavaEngine/Events/MouseEvent.h"
    "${PATH_DIR}/JavaEngine/Core/Window.h"
    "${PATH_DIR}/JavaEngine/Renderer/SFML/SFMLWindow.h"
    "${PATH_DIR}/JavaEngine/ImGui/ImGuiLayer.h"
    "${PATH_DIR}/JavaEngine/LevelRenderer/Scene.h"
    "${PATH_DIR}/JavaEngine/Gameplay/JObject.h"
)

set(SOURCES
	"${PATH_DIR}/JavaEngine/Core/Application.cpp"
	"${PATH_DIR}/JavaEngine/Core/Log.cpp"
    "${PATH_DIR}/JavaEngine/Core/Layer.cpp"
	"${PATH_DIR}/JavaEngine/Core/LayerStack.cpp"
	"${PATH_DIR}/jepch.cpp"
    "${PATH_DIR}/JavaEngine/Renderer/SFML/SFMLWindow.cpp"
    "${PATH_DIR}/JavaEngine/ImGui/ImGuiLayer.cpp"
    "${PATH_DIR}/JavaEngine/LevelRenderer/Scene.cpp"
    "${PATH_DIR}/JavaEngine/Gameplay/JObject.cpp"
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

target_link_libraries(${PROJECT_NAME}
    PUBLIC
    sfml-system sfml-graphics sfml-window sfml-audio
    spdlog::spdlog
    ImGui-SFML::ImGui-SFML
)

if(CMAKE_VERSION VERSION_GREATER 3.8)
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20)
else()
    set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD_REQUIRED ON)