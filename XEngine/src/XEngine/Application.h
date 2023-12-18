#pragma once
#include "Core.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "LayerStack.h"

#include "Window.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Shader.h"
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

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;

	};

	// to be define by CLIENT!
	Application* CreateApplication();
}


