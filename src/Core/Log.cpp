#include "draugpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace Draug;

std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> Log::s_loggers;

void Log::initialize() {
	Log::setPattern("%^[%T](%n): %v%$");
	Draug::Log::addLogger(Draug::Log::createLogger("Draug", spdlog::level::trace));
}

void Log::setPattern(std::string pattern) {
	spdlog::set_pattern(pattern);
}

void Log::addLogger(std::shared_ptr<spdlog::logger> logger) {
	s_loggers[logger->name()] = logger;
}

std::shared_ptr<spdlog::logger> Log::getLogger(const std::string& name) {
	return s_loggers[name];
}

uint32 Log::getLoggerCount() {
	return s_loggers.size();
}

std::shared_ptr<spdlog::logger> Log::createLogger(const std::string& name, spdlog::level::level_enum log_level) {
	auto logger = spdlog::stdout_color_mt(name);
	logger->set_level(log_level);
	return logger;
}

