#pragma once

#include "Draug.h"
#include <spdlog/logger.h>

namespace spdlog {
class logger;
namespace level {
enum level_enum;
}
}

namespace Draug {
class DRAUG_API Log {
public:
	static void init();
	static void set_pattern(std::string pattern);

	static void add_logger(std::shared_ptr<spdlog::logger> logger);
	static std::shared_ptr<spdlog::logger> get_logger(const std::string& name);
	static int get_logger_count();

	static std::shared_ptr<spdlog::logger> create_logger(const std::string& name, spdlog::level::level_enum log_level);

private:
	static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> s_loggers;
};
}

#define DRAUG_LOG_CORE_TRACE(...) Draug::Log::get_logger("Draug")->trace(__VA_ARGS__)
#define DRAUG_LOG_CORE_DEBUG(...) Draug::Log::get_logger("Draug")->debug(__VA_ARGS__)
#define DRAUG_LOG_CORE_INFO(...) Draug::Log::get_logger("Draug")->info(__VA_ARGS__)
#define DRAUG_LOG_CORE_WARN(...) Draug::Log::get_logger("Draug")->warn(__VA_ARGS__)
#define DRAUG_LOG_CORE_ERROR(...) Draug::Log::get_logger("Draug")->error(__VA_ARGS__)
#define DRAUG_LOG_CORE_CRITICAL(...) Draug::Log::get_logger("Draug")->critical(__VA_ARGS__)

#define DRAUG_LOG_TRACE(...) Draug::Log::get_logger("App")->trace(__VA_ARGS__)
#define DRAUG_LOG_DEBUG(...) Draug::Log::get_logger("App")->debug(__VA_ARGS__)
#define DRAUG_LOG_INFO(...) Draug::Log::get_logger("App")->info(__VA_ARGS__)
#define DRAUG_LOG_WARN(...) Draug::Log::get_logger("App")->warn(__VA_ARGS__)
#define DRAUG_LOG_ERROR(...) Draug::Log::get_logger("App")->error(__VA_ARGS__)
#define DRAUG_LOG_CRITICAL(...) Draug::Log::get_logger("App")->critical(__VA_ARGS__)
