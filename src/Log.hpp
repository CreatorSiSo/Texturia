#pragma once

#include <memory.h>

#include <spdlog/fmt/ostr.h>
#include <spdlog/spdlog.h>

namespace Texturia {

class Log {
public:
  static void Init();
  inline static std::shared_ptr<spdlog::logger> &GetLogger() {
    return s_Logger;
  }

private:
  static std::shared_ptr<spdlog::logger> s_Logger;
};

} // namespace Texturia

// Log Macros
#define TX_TRACE(...) Texturia::Log::GetLogger()->trace(__VA_ARGS__)
#define TX_INFO(...) Texturia::Log::GetLogger()->info(__VA_ARGS__)
#define TX_WARN(...) Texturia::Log::GetLogger()->warn(__VA_ARGS__)
#define TX_ERROR(...) Texturia::Log::GetLogger()->error(__VA_ARGS__)
#define TX_FATAL(...) Texturia::Log::GetLogger()->fatal(__VA_ARGS__)