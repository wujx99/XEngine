#include "xepch.h"
#include "XEngine/Core/Window.h"

#ifdef XE_PLATFORM_WINDOWS
#include "Platform/Windows/WindowsWindow.h"
#endif

namespace XEg
{

	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef XE_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		XE_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}