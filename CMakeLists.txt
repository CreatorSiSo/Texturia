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
    ./src/Log.cpp
    ./src/Main.cpp
)

# Targets
add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES UNITY_BUILD ON)

# Includes
target_include_directories(${PROJECT_NAME}
    PUBLIC ./libs/spdlog/include
    PRIVATE ./src
)

# External Libraries
add_subdirectory(./libs/spdlog)

# Precompiled Headers
target_precompile_headers(${PROJECT_NAME}
  PRIVATE ./src/txpch.hpp
)

# Linking
target_link_libraries(${PROJECT_NAME}
    spdlog
)
