#pragma once
#include "XEngine/Core/Base.h"
#include "XEngine/Core/Window.h"
#include "XEngine/Core/LayerStack.h"

#include "XEngine/Event/Event.h"
#include "XEngine/Event/ApplicationEvent.h"

#include "XEngine/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace XEg {
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);

		Window& GetWindow() { return *m_Window;}
		void Close();
		static Application& Get() { return *s_Instance; }
	private:
		void Run();

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
		friend int ::main(int argc, char** argv);
	};

	// to be define by CLIENT!
	Application* CreateApplication();
}


