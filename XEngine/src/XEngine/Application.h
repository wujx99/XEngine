#pragma once
#include "Core.h"

#include "Window.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "LayerStack.h"

#include "ImGui/ImGuiLayer.h"

namespace XEg {
	class Application
	{
	public:
		Application();
		virtual ~Application() {};

		void Run();
		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window;}
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		
		LayerStack m_LayerStack;
		float m_LastFrameTime{ 0.0f };
	private:
		static Application* s_Instance;

	};

	// to be define by CLIENT!
	Application* CreateApplication();
}


