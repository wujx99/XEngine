#pragma once
#include "Core.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"

#include "Window.h"
namespace XEg {
	class Application
	{
	public:
		Application();
		virtual ~Application() {};

		void Run();
		void OnEvent(Event&);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;

	};

	// to be define by CLIENT!
	Application* CreateApplication();
}


