#pragma once

#include "Core/Core.h"
#include <spdlog/spdlog.h>
#include <memory>

namespace Pixie
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

		// Core logging macros
	#define PX_CORE_TRACE(...)    ::Pixie::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define PX_CORE_INFO(...)     ::Pixie::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define PX_CORE_WARN(...)     ::Pixie::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define PX_CORE_ERROR(...)    ::Pixie::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define PX_CORE_CRITICAL(...) ::Pixie::Log::GetCoreLogger()->critical(__VA_ARGS__)

		// Client logging macros
	#define PX_TRACE(...)    ::Pixie::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define PX_INFO(...)     ::Pixie::Log::GetClientLogger()->info(__VA_ARGS__)
	#define PX_WARN(...)     ::Pixie::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define PX_ERROR(...)    ::Pixie::Log::GetClientLogger()->error(__VA_ARGS__)
	#define PX_CRITICAL(...) ::Pixie::Log::GetClientLogger()->critical(__VA_ARGS__)
}
