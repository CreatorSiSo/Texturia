if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  if(NOT DEFINED WITH_IN_SOURCE_BUILD)
    message(FATAL_ERROR
      "\n "
      "CMake generation for Texturia is not allowed within the source directory!"
      "\n Remove \"${CMAKE_SOURCE_DIR}/CMakeCache.txt\" and try again from another folder, e.g.:"
      "\n "
      "\n rm -rf CMakeCache.txt CMakeFiles"
      "\n mkdir bin"
      "\n cmake -S . -B bin"
      "\n "
      "\n Alternately define WITH_IN_SOURCE_BUILD to force this option (not recommended!)"
    )
  endif()
endif()

# Project Setup
cmake_minimum_required(VERSION 3.16)
project(Texturia VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Source Files
set(SOURCES
  ./src/CoreApp.cpp
  ./src/Layer.cpp
  ./src/LayerStack.cpp
  ./src/Log.cpp
  ./src/Main.cpp
  ./src/ImGui/ImGuiLayer.cpp
  ./src/Platforms/Linux/LinuxWindow.cpp
  ./src/Platforms/OpenGL/ImGuiOpenGL3Renderer.cpp
)

# Targets
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)

#Pre Build
add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets)


# Includes
target_include_directories(${PROJECT_NAME}
  PUBLIC ./libs/debugbreak
  PUBLIC ./libs/glad/include
  PUBLIC ./libs/glfw/include
  PUBLIC ./libs/imgui
  PUBLIC ./libs/spdlog/include
  PRIVATE ./src
)

# External Libraries
add_subdirectory(./libs/glad)
add_subdirectory(./libs/glfw)
add_subdirectory(./libs/imgui)
add_subdirectory(./libs/spdlog)

# Linking
target_link_libraries(${PROJECT_NAME}
  glad
  glfw
  imgui
  spdlog
)

# Precompiled Headers
target_precompile_headers(${PROJECT_NAME}
  PRIVATE ./src/txpch.hpp
)
