#pragma once


#ifdef XE_PLATFORM_WINDOWS

#else
	#error Hazel only support windows!
#endif

#ifdef XE_DEBUG
	#define XE_CORE_ASSERT(x, ...) {if(!(x)) { XE_CORE_ERROR("Assert failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define XE_ASSERT(x, ...) {if(!(x)) { XE_CLIENT_ERROR("Assert failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define XE_CORE_ASSERT(x, ...)
	#define XE_CLIENT_ASSERT(x, ...)
#endif // DEBUG


#define BIT(x) (1<<x)

#define XE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)