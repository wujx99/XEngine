#include "xepch.h"
#include "Application.h"

#include "XEngine/Core/Log.h"
#include "XEngine/Renderer/Renderer.h"
#include <GLFW/glfw3.h>


namespace XEg
{

	Application* Application::s_Instance = nullptr;

	Application::Application()
		
	{
		XE_PROFILE_FUNCTION();

		XE_CORE_ASSERT(!s_Instance, "Appliaction already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallBack(XE_BIND_EVENT_FN(Application::OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverLay(m_ImGuiLayer);

		
	}
	Application::~Application()
	{
		XE_PROFILE_FUNCTION();

		Renderer::Shutdown();
	}
	void Application::Run()
	{
		XE_PROFILE_FUNCTION();


		while (m_Running)
		{
			XE_PROFILE_SCOPE("Runloop");

			float time = (float)glfwGetTime();
			TimeStep ts = time - m_LastFrameTime;
			m_LastFrameTime = time;

			if (!m_Minimized)
			{
				{
					XE_PROFILE_SCOPE("LayerStack OnUpdate");

					for (Layer* layer : m_LayerStack)
						layer->OnUpdate(ts);
				}
				{
					XE_PROFILE_SCOPE("LayerStack OnImGuiUpdate");

					// ImGUi Layer
					m_ImGuiLayer->Begin();
					for (Layer* layer : m_LayerStack)
						layer->OnImGuiRender();
					m_ImGuiLayer->End();

					m_Window->OnUpdate();
				}
			}
			

			

			
		}
	}
	void Application::OnEvent(Event& e)
	{
		XE_PROFILE_FUNCTION();

		EventDispatcher dispatcher(e);
		// be careful! we must use BIND_EVENT_FN to dispatch the correspond func to Event!
		dispatcher.Dispatch<WindowCloseEvent>(XE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(XE_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto itr = m_LayerStack.rbegin(); itr != m_LayerStack.rend(); ++itr)
		{
			(*itr)->OnEvent(e);
			if (e.Handled) 
				break;  // be careful to this! blocked!
		}

	}
	void Application::PushLayer(Layer* layer)
	{
		XE_PROFILE_FUNCTION();

		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverLay(Layer* overlay)
	{
		XE_PROFILE_FUNCTION();

		m_LayerStack.PushOverLayer(overlay);
		overlay->OnAttach();
	}
	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		XE_PROFILE_FUNCTION();

		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());
		return false;
	}
}