#pragma once
#include "XEngine/Core/Base.h"
#include "XEngine/Core/Window.h"
#include "XEngine/Core/LayerStack.h"

#include "XEngine/Event/Event.h"
#include "XEngine/Event/ApplicationEvent.h"

#include "XEngine/ImGui/ImGuiLayer.h"

int main(int argc, char** argv);

namespace XEg {
	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;
		const char* operator[](int index)const
		{
			XE_CORE_ASSERT(index < Count);
			return Args[index];
		}
	};
	class Application
	{
	public:
		Application(const std::string& name = "XEngine APP", ApplicationCommandLineArgs args = ApplicationCommandLineArgs());
		virtual ~Application();

		void OnEvent(Event&);

		void PushLayer(Layer* layer);
		void PushOverLay(Layer* overlay);

		Window& GetWindow() { return *m_Window;}
		void Close();
		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }
		static Application& Get() { return *s_Instance; }

		ApplicationCommandLineArgs GetCommandLineArgs() const { return m_CommandLineArgs; }
	private:
		void Run();

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		ApplicationCommandLineArgs m_CommandLineArgs;
		Scope<Window> m_Window;
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
	Application* CreateApplication(ApplicationCommandLineArgs args);
}


