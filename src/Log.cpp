#include <spdlog/sinks/stdout_color_sinks.h>

#include "Log.hpp"

namespace Texturia {

std::shared_ptr<spdlog::logger> Log::s_Logger;

void Log::Init() {
  spdlog::set_pattern("[%H:%M:%S] [Thread %t] %n: %v");
  s_Logger = spdlog::stdout_color_mt("TEXTURIA");
  s_Logger->set_level(spdlog::level::trace);
}

} // namespace Texturia