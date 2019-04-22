#pragma once

#include "Draug.h"
#include "Core/Types.h"
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
	static void initialize();
	static void setPattern(std::string pattern);

	static void addLogger(std::shared_ptr<spdlog::logger> logger);
	static std::shared_ptr<spdlog::logger> getLogger(const std::string& name);
	static uint32 getLoggerCount();

	static std::shared_ptr<spdlog::logger> createLogger(const std::string& name, spdlog::level::level_enum log_level);

private:
	static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> s_loggers;
};
}

#define DRAUG_CORE_TRACE(...) Draug::Log::getLogger("Draug")->trace(__VA_ARGS__)
#define DRAUG_CORE_DEBUG(...) Draug::Log::getLogger("Draug")->debug(__VA_ARGS__)
#define DRAUG_CORE_INFO(...) Draug::Log::getLogger("Draug")->info(__VA_ARGS__)
#define DRAUG_CORE_WARN(...) Draug::Log::getLogger("Draug")->warn(__VA_ARGS__)
#define DRAUG_CORE_ERROR(...) Draug::Log::getLogger("Draug")->error(__VA_ARGS__)
#define DRAUG_CORE_CRITICAL(...) Draug::Log::getLogger("Draug")->critical(__VA_ARGS__)

#define DRAUG_TRACE(...) Draug::Log::getLogger("App")->trace(__VA_ARGS__)
#define DRAUG_DEBUG(...) Draug::Log::getLogger("App")->debug(__VA_ARGS__)
#define DRAUG_INFO(...) Draug::Log::getLogger("App")->info(__VA_ARGS__)
#define DRAUG_WARN(...) Draug::Log::getLogger("App")->warn(__VA_ARGS__)
#define DRAUG_ERROR(...) Draug::Log::getLogger("App")->error(__VA_ARGS__)
#define DRAUG_CRITICAL(...) Draug::Log::getLogger("App")->critical(__VA_ARGS__)
