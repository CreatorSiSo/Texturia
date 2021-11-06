if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  if(NOT DEFINED WITH_IN_SOURCE_BUILD)
    message(
      FATAL_ERROR
        "CMake generation for Texturia is not allowed within the source directory!"
        "\n Remove \"${CMAKE_SOURCE_DIR}/CMakeCache.txt\" and try again from another folder, e.g.:"
        "\n "
        "\n rm -rf CMakeCache.txt CMakeFiles"
        "\n mkdir build"
        "\n cmake -S . -B build"
        "\n "
        "\n ⚠ Alternately define WITH_IN_SOURCE_BUILD to force this option (not recommended!!!) ⚠"
    )
  endif()
endif()

# Project Setup
cmake_minimum_required(VERSION 3.16)

project(
  Texturia
  VERSION 0.1.0
  DESCRIPTION "Procedural texture generator with noodles and stuff."
  LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin/${CMAKE_BUILD_TYPE})

# Source Files
set(SOURCES
    ./src/CoreApp.cpp
    ./src/Layer.cpp
    ./src/LayerStack.cpp
    ./src/Log.cpp
    ./src/Main.cpp
    ./src/ImGui/ImGuiBuild.cpp
    ./src/ImGui/ImGuiLayer.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  set(PLATFORM_SOURCES ./src/Platforms/Windows/WindowsInput.cpp
                       ./src/Platforms/Windows/WindowsWindow.cpp)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(PLATFORM_SOURCES ./src/Platforms/Linux/LinuxInput.cpp
                       ./src/Platforms/Linux/LinuxWindow.cpp)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  set(PLATFORM_SOURCES ./src/Platforms/MacOS/MacOSInput.cpp
                       ./src/Platforms/MacOS/MacOSWindow.cpp)
endif()

# Targets
add_executable(${PROJECT_NAME} ${SOURCES} ${PLATFORM_SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)

# Crossplatform Compiler Defines/Options
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  add_compile_definitions(TX_PLATFORM_WINDOWS)
  # target_compile_options(${PROJECT_NAME} PRIVATE /W4)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  add_compile_definitions(TX_PLATFORM_LINUX)
  # target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
  add_compile_definitions(TX_PLATFORM_MACOS)
endif()

# Pre Build
add_custom_command(
  TARGET ${PROJECT_NAME}
  PRE_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/assets
          ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)

# Includes
target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ./libs/debugbreak
  PRIVATE ./libs/glad/include
  PRIVATE ./libs/glfw/include
  PRIVATE ./libs/glm
  PRIVATE ./libs/imgui
  PRIVATE ./libs/spdlog/include
  PRIVATE ./src)

# External Libraries
add_subdirectory(./libs/glad)
add_subdirectory(./libs/glfw)
add_subdirectory(./libs/glm)
add_subdirectory(./libs/imgui)
add_subdirectory(./libs/spdlog)

# Linking
target_link_libraries(${PROJECT_NAME} glad glfw glm imgui spdlog)

# Precompiled Headers
target_precompile_headers(${PROJECT_NAME} PRIVATE ./src/txpch.hpp)
