#include "Draug.h"
#include "Log.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Draug {
std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> Log::s_loggers;

void Log::initialize() {
	Log::setPattern("%^[%T](%n): %v%$");
	spdlog::set_error_handler([](const std::string & msg)
		{
			std::cerr << "Logger error: " << msg << std::endl;
		});
	Draug::Log::addLogger(Draug::Log::createLogger("Draug", spdlog::level::trace));
	Draug::Log::addLogger(Draug::Log::createLogger("App", spdlog::level::trace));
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
}

