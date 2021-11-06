#pragma once

#include "Input/KeyCodes.hpp"
#include "Input/MouseButtonCodes.hpp"

// #ifdef TX_ENABLE_ASSERTS
#define TX_ASSERT(x, ...)                                                      \
  {                                                                            \
    if (!(x)) {                                                                \
      TX_ERROR("[{1}:{2}] Assertion Failed: {0}", __VA_ARGS__, __FILE__,       \
               __LINE__);                                                      \
      debug_break();                                                           \
    }                                                                          \
  }
// #else
// #define TX_ASSERT(x, ...)
// #endif

#define TX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)

#define IMGUI_IMPL_OPENGL_LOADER_GLAD
#define GLFW_INCLUDE_NONE

#define TX_GLSL_VERSION "#version 410"