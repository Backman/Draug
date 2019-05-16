#include "Log.h"
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace Draug {
std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> Log::s_loggers;

void Log::init() {
	Log::set_pattern("%^[%T](%n): %v%$");
	spdlog::set_error_handler([](const std::string & msg)
		{
			std::cerr << "Logger error: " << msg << std::endl;
		});
	Draug::Log::add_logger(Draug::Log::create_logger("Draug", spdlog::level::trace));
	Draug::Log::add_logger(Draug::Log::create_logger("App", spdlog::level::trace));
}

void Log::set_pattern(std::string pattern) {
	spdlog::set_pattern(pattern);
}

void Log::add_logger(std::shared_ptr<spdlog::logger> logger) {
	s_loggers[logger->name()] = logger;
}

std::shared_ptr<spdlog::logger> Log::get_logger(const std::string& name) {
	return s_loggers[name];
}

int Log::get_logger_count() {
	return s_loggers.size();
}

std::shared_ptr<spdlog::logger> Log::create_logger(const std::string& name, spdlog::level::level_enum log_level) {
	auto logger = spdlog::stdout_color_mt(name);
	logger->set_level(log_level);
	return logger;
}
}

