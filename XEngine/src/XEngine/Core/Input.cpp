#include "xepch.h"
#include "XEngine/Core/Input.h"

#ifdef XE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsInput.h"
#endif

namespace XEg {

	Scope<Input> Input::s_Instance = Input::Create();

	Scope<Input> Input::Create()
	{
#ifdef XE_PLATFORM_WINDOWS
		return CreateScope<WindowsInput>();
#else
		XE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}
}