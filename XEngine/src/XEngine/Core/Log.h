#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/fmt/ostr.h"

namespace XEg
{
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger> GetCoreLogger()
		{
			return s_CoreLogger;
		}
		inline static std::shared_ptr<spdlog::logger> GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}
// Core log macros
#define XE_CORE_TRACE(...)		::XEg::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define XE_CORE_INFO(...)		::XEg::Log::GetCoreLogger()->info(__VA_ARGS__)
#define XE_CORE_WARN(...)		::XEg::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define XE_CORE_ERROR(...)		::XEg::Log::GetCoreLogger()->error(__VA_ARGS__)
#define XE_CORE_CRITICAL(...)	::XEg::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define XE_CLIENT_TRACE(...)	::XEg::Log::GetClientLogger()->trace(__VA_ARGS__)
#define XE_CLIENT_INFO(...)		::XEg::Log::GetClientLogger()->info(__VA_ARGS__)
#define XE_CLIENT_WARN(...)		::XEg::Log::GetClientLogger()->warn(__VA_ARGS__)
#define XE_CLIENT_ERROR(...)	::XEg::Log::GetClientLogger()->error(__VA_ARGS__)
#define XE_CLIENT_CRITICAL(...)	::XEg::Log::GetClientLogger()->critical(__VA_ARGS__)