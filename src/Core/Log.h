#pragma once

#include "draugpch.h"
#include "Core/Types.h"
#include "Draug.h"

namespace spdlog {
class logger;
namespace level {
enum level_enum;
}
}

namespace Draug {
class DRAUG_API Log {
	static std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> s_loggers;
public:
	static void initialize();
	static void setPattern(std::string pattern);

	static void addLogger(std::shared_ptr<spdlog::logger> logger);
	static std::shared_ptr<spdlog::logger> getLogger(const std::string& name);
	static uint32 getLoggerCount();

	static std::shared_ptr<spdlog::logger> createLogger(const std::string& name, spdlog::level::level_enum log_level);
};
}

#define INTERNAL_DRAUG_TRACE(name, ...) ::Draug::Log::getLogger(name)->trace(__VA_ARGS__)
#define INTERNAL_DRAUG_DEBUG(name, ...) ::Draug::Log::getLogger(name)->debug(__VA_ARGS__)
#define INTERNAL_DRAUG_INFO(name, ...) ::Draug::Log::getLogger(name)->info(__VA_ARGS__)
#define INTERNAL_DRAUG_WARN(name, ...) ::Draug::Log::getLogger(name)->warn(__VA_ARGS__)
#define INTERNAL_DRAUG_ERROR(name, ...) ::Draug::Log::getLogger(name)->error(__VA_ARGS__)
#define INTERNAL_DRAUG_FATAL(name, ...) ::Draug::Log::getLogger(name)->fatal(__VA_ARGS__)

#define DRAUG_CORE_TRACE(...) INTERNAL_DRAUG_TRACE("Draug", __VA_ARGS__)
#define DRAUG_CORE_DEBUG(...) INTERNAL_DRAUG_DEBUG("Draug", __VA_ARGS__)
#define DRAUG_CORE_INFO(...) INTERNAL_DRAUG_INFO("Draug", __VA_ARGS__)
#define DRAUG_CORE_WARN(...) INTERNAL_DRAUG_WARN("Draug", __VA_ARGS__)
#define DRAUG_CORE_ERROR(...) INTERNAL_DRAUG_ERROR("Draug", __VA_ARGS__)
#define DRAUG_CORE_FATAL(...) INTERNAL_DRAUG_FATAL("Draug", __VA_ARGS__)

#define DRAUG_TRACE(...) INTERNAL_DRAUG_TRACE("App", __VA_ARGS__)
#define DRAUG_DEBUG(...) INTERNAL_DRAUG_DEBUG("App", __VA_ARGS__)
#define DRAUG_INFO(...) INTERNAL_DRAUG_INFO("App", __VA_ARGS__)
#define DRAUG_WARN(...) INTERNAL_DRAUG_WARN("App", __VA_ARGS__)
#define DRAUG_ERROR(...) INTERNAL_DRAUG_ERROR("App", __VA_ARGS__)
#define DRAUG_FATAL(...) INTERNAL_DRAUG_FATAL("App", __VA_ARGS__)
