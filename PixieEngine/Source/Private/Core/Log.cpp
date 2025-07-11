#include "ppch.h"
#include "Core/Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

namespace Pixie
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init()
	{
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("%^[%T] %n: %v%$");

		auto fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("Pixie.log", true);

		// Engine Log
		s_CoreLogger = std::make_shared<spdlog::logger>("PIXIE", spdlog::sinks_init_list{ consoleSink, fileSink });
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		// App(Game) Log
		s_ClientLogger = std::make_shared<spdlog::logger>("APP", spdlog::sinks_init_list{ consoleSink, fileSink });
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}
}