#pragma once
#include "XEngine/Core/Core.h"
#include "XEngine/Core/Window.h"
#include "XEngine/Core/LayerStack.h"

#include "XEngine/Event/Event.h"
#include "XEngine/Event/ApplicationEvent.h"

#include "XEngine/ImGui/ImGuiLayer.h"

namespace XEg {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);

		inline Window& GetWindow() { return *m_Window;}
		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		
		LayerStack m_LayerStack;
		float m_LastFrameTime{ 0.0f };
	private:
		static Application* s_Instance;

	};

	// to be define by CLIENT!
	Application* CreateApplication();
}


