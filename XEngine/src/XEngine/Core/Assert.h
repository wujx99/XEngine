#pragma once

#include "XEngine/Core/Base.h"
#include "XEngine/Core/Log.h"
#include <filesystem>

#ifdef XE_ENABLE_ASSERTS
	

	// Alteratively we could use the same "default" message for both "WITH_MSG" and "NO_MSG" and
	// provide support for custom formatting by concatenating the formatting string instead of having the format inside the default message
	#define XE_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { XE##type##ERROR(msg, __VA_ARGS__); XE_DEBUGBREAK(); } }
	#define XE_INTERNAL_ASSERT_WITH_MSG(type, check, ...) XE_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define XE_INTERNAL_ASSERT_NO_MSG(type, check) XE_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", XE_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
		
	#define XE_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define XE_INTERNAL_ASSERT_GET_MACRO(...) XE_EXPAND_MACRO( XE_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, XE_INTERNAL_ASSERT_WITH_MSG, XE_INTERNAL_ASSERT_NO_MSG) )

	// Currently accepts at least the condition and one additional parameter (the message) being optional
	#define XE_CLIENT_ASSERT(...) XE_EXPAND_MACRO( XE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CLIENT_, __VA_ARGS__) )
	#define XE_CORE_ASSERT(...) XE_EXPAND_MACRO( XE_INTERNAL_ASSERT_GET_MACRO(__VA_ARGS__)(_CORE_, __VA_ARGS__) )
#else	
	#define XE_CLIENT_ASSERT(...)
	#define XE_CORE_ASSERT(...)
#endif
