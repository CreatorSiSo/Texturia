#pragma once

#include "txpch.hpp"

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace Texturia {

class Log {
public:
  static void Init();

  inline static std::shared_ptr<spdlog::logger> &GetCoreLogger() {
    return s_Logger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_Logger;
};

} // namespace Texturia

// Log macros
#define TX_TRACE(...) ::Texturia::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define TX_INFO(...) ::Texturia::Log::GetCoreLogger()->info(__VA_ARGS__)
#define TX_WARN(...) ::Texturia::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define TX_ERROR(...) ::Texturia::Log::GetCoreLogger()->error(__VA_ARGS__)
#define TX_FATAL(...) ::Texturia::Log::GetCoreLogger()->fatal(__VA_ARGS__)
