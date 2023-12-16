#include "xepch.h"
#include "Application.h"

#include "XEngine/Event/ApplicationEvent.h"
#include "Log.h"

namespace XEg
{
	
	void Application::Run()
	{
		WindowResizeEvent e(1280, 900);
		if (e.IsInCategory(EventCategory::EventCategoryApplication))
		{
			XE_CORE_INFO(e);

		}

		while (true)
		{
		}
	}
}