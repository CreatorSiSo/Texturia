#pragma once

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

#define BIT(x) (1 << x)

#define TX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)
