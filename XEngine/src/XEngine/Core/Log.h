#pragma once

#include "XEngine/Core/Base.h"

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"
// this ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace XEg
{
	class Log
	{
	public:
		static void Init();

		inline static Ref<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}
		inline static Ref<spdlog::logger>& GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_ClientLogger;
	};
}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
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
