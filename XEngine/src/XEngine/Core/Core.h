#pragma once

#include <memory>

// Platform detetion using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define XE_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>
	/* TARGET_OS_MAC exists on all the platforms
	 * so we must check all of them (in this order)
	 * to ensure that we're running on MAC
	 * and not some other Apple platform */
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define XE_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define XE_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
	 /* We also have to check __ANDROID__ before __linux__
	  * since android is based on the linux kernel
	  * it has __linux__ defined */
#elif defined(__ANDROID__)
	#define XE_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__linux__)
	#define XE_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	/* Unknown compiler/platform */
	#error "Unknown platform!"
#endif // !_WIN32


// DLL support
#ifdef XE_PLATFORM_WINDOWS
	#if XE_DYNAMIC_LINK
		#ifdef XE_BUILD_DLL
			#define XEg_API __declspec(dllexport)
		#else
			#define XEg_API __declspec(dllimport)
		#endif
	#else
		#define XEg_API
	#endif
#else
	#error XEngine only supports Windows!
#endif // End of DLL support

#ifdef XE_DEBUG
	#define XE_CORE_ASSERT(x, ...) {if(!(x)) { XE_CORE_ERROR("Assert failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define XE_ASSERT(x, ...) {if(!(x)) { XE_CLIENT_ERROR("Assert failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define XE_CORE_ASSERT(x, ...)
	#define XE_CLIENT_ASSERT(x, ...)
#endif // DEBUG


#define BIT(x) (1<<x)

#define XE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace XEg
{
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}