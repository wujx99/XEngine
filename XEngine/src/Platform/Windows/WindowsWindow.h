#pragma once
#include "XEngine/Core/Window.h"
#include "XEngine/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace XEg
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& prop);
		virtual ~WindowsWindow();

		virtual void OnUpdate() override;
		inline virtual unsigned int GetWidth() const {return m_Data.Width;}
		inline virtual unsigned int GetHeight() const { return m_Data.Height; }

		// window attributes
		inline virtual void SetEventCallBack(const EventCallBackFn& callback) { m_Data.EventCallBack = callback; }
		virtual void setVSync(bool enabled) ;
		virtual bool IsVSync() const;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window; // the actual window
		GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallBackFn EventCallBack;
		};
		WindowData m_Data;
	};
}