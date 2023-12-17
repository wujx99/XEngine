#include "xepch.h"
#include "Application.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>


namespace XEg
{
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(BIND_EVENT_FN(OnEvent));
	}
	void Application::Run()
	{
		

		while (m_Running)
		{
			
			m_Window->OnUpdate();

		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		// be careful! we must use BIND_EVENT_FN to dispatch the correspond func to Event!
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		XE_CORE_TRACE("{0}", e);

	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}