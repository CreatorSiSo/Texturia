#pragma once

// #ifdef TX_ENABLE_ASSERTS
#define TX_ASSERT(x, ...)                                                      \
  {                                                                            \
    if (!(x)) {                                                                \
      TX_ERROR("Assertion Failed: {0]", __VA_ARGS__);                          \
      __debugbreak();                                                          \
    }                                                                          \
  }
// #else
// #define TX_ASSERT(x, ...)
// #endif

#define BIT(x) (1 << x)