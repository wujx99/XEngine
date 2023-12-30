#pragma once

#include <memory>

#include "XEngine/Core/PlatformDetection.h"



#ifdef XE_DEBUG
	#if defined(XE_PLATFORM_WINDOWS)
		#define XE_DEBUGBREAK() __debugbreak()
	#elif defined(XE_PLATFORM_LINUX)
		#include <signal.h>
		#define XE_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
		#define XE_ENABLE_ASSERTS
	#else
		#define XE_DEBUGBREAK()
#endif // XE_DEBUG



#ifdef XE_ENABLE_ASSERTS
	#define XE_CORE_ASSERT(x, ...) {if(!(x)) { XE_CORE_ERROR("Assert failed: {0}", __VA_ARGS__); XE_DEBUGBREAK();}}
	#define XE_ASSERT(x, ...) {if(!(x)) { XE_CLIENT_ERROR("Assert failed: {0}", __VA_ARGS__); XE_DEBUGBREAK();}}
#else
	#define XE_CORE_ASSERT(x, ...)
	#define XE_CLIENT_ASSERT(x, ...)
#endif 


#define BIT(x) (1<<x)

#define XE_BIND_EVENT_FN(fn) [this](auto&&... args)->decltype(auto) {return this->fn(std::forward<decltype(args)>(args)...);}

namespace XEg
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	// the correspond make_unique<>()
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	//
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}
